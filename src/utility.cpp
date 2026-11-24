/**
 * @file utility.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.2
 * @date 2023/10/27
 *
 * Contains implementations of functions in utility.h.
 *
 */


#include "../include/utility.h"

#include <chrono>
#include <cstring>
#include <stdexcept>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace {
bool webOutputEnabled = false;
std::streambuf* originalOutputBuffer = nullptr;

#ifdef _WIN32
using Socket = SOCKET;
const Socket invalidSocket = INVALID_SOCKET;
void closeSocket(Socket socket) { closesocket(socket); }
#else
using Socket = int;
const Socket invalidSocket = -1;
void closeSocket(Socket socket) { close(socket); }
#endif

struct HttpResponse {
	int status;
	std::string body;
};

std::string jsonEscape(const std::string& text) {
	std::string escaped;
	for (char character : text) {
		switch (character) {
			case '"': escaped += "\\\""; break;
			case '\\': escaped += "\\\\"; break;
			case '\b': escaped += "\\b"; break;
			case '\f': escaped += "\\f"; break;
			case '\n': escaped += "\\n"; break;
			case '\r': escaped += "\\r"; break;
			case '\t': escaped += "\\t"; break;
			default:
				if (static_cast<unsigned char>(character) < 0x20) {
					const char hex[] = "0123456789abcdef";
					escaped += "\\u00";
					escaped += hex[(static_cast<unsigned char>(character) >> 4) & 0x0f];
					escaped += hex[static_cast<unsigned char>(character) & 0x0f];
				} else {
					escaped += character;
				}
		}
	}
	return escaped;
}

HttpResponse sendHttpRequest(const std::string& method, const std::string& path, const std::string& body) {
	const char* hostValue = std::getenv("BEANZ_WEB_HOST");
	const char* portValue = std::getenv("BEANZ_WEB_PORT");
	const std::string host = hostValue ? hostValue : "127.0.0.1";
	const std::string port = portValue ? portValue : "4174";

#ifdef _WIN32
	static const bool winsockReady = []() {
		WSADATA data;
		return WSAStartup(MAKEWORD(2, 2), &data) == 0;
	}();
	if (!winsockReady) {
		throw std::runtime_error("Could not initialize Windows networking.");
	}
#endif

	addrinfo hints{};
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	addrinfo* addresses = nullptr;
	const int lookupResult = getaddrinfo(host.c_str(), port.c_str(), &hints, &addresses);
	if (lookupResult != 0) {
		throw std::runtime_error("Could not resolve the web bridge host.");
	}

	Socket socket = invalidSocket;
	for (addrinfo* address = addresses; address != nullptr; address = address->ai_next) {
		socket = ::socket(address->ai_family, address->ai_socktype, address->ai_protocol);
		if (socket == invalidSocket) {
			continue;
		}
		if (::connect(socket, address->ai_addr, static_cast<int>(address->ai_addrlen)) == 0) {
			break;
		}
		closeSocket(socket);
		socket = invalidSocket;
	}
	freeaddrinfo(addresses);
	if (socket == invalidSocket) {
		throw std::runtime_error("Could not connect to the web bridge at " + host + ":" + port + ".");
	}

	const std::string request = method + " " + path + " HTTP/1.1\r\n"
		+ "Host: " + host + ":" + port + "\r\n"
		+ (std::getenv("BEANZ_WEB_TOKEN") ? "X-Beanz-Bridge-Token: "
			+ std::string(std::getenv("BEANZ_WEB_TOKEN")) + "\r\n" : "")
		+ "Content-Type: application/json\r\n"
		+ "Content-Length: " + std::to_string(body.size()) + "\r\n"
		+ "Connection: close\r\n\r\n" + body;
	std::size_t sent = 0;
	while (sent < request.size()) {
#ifdef _WIN32
		const int result = ::send(socket, request.data() + sent, static_cast<int>(request.size() - sent), 0);
#else
		const ssize_t result = ::send(socket, request.data() + sent, request.size() - sent, 0);
#endif
		if (result <= 0) {
			closeSocket(socket);
			throw std::runtime_error("Could not send data to the web bridge.");
		}
		sent += static_cast<std::size_t>(result);
	}

	std::string response;
	char buffer[4096];
	while (true) {
#ifdef _WIN32
		const int result = ::recv(socket, buffer, sizeof(buffer), 0);
#else
		const ssize_t result = ::recv(socket, buffer, sizeof(buffer), 0);
#endif
		if (result == 0) {
			break;
		}
		if (result < 0) {
			closeSocket(socket);
			throw std::runtime_error("Could not read the web bridge response.");
		}
		response.append(buffer, static_cast<std::size_t>(result));
	}
	closeSocket(socket);

	const std::size_t headerEnd = response.find("\r\n\r\n");
	if (headerEnd == std::string::npos) {
		throw std::runtime_error("The web bridge returned an invalid HTTP response.");
	}
	std::istringstream headers(response.substr(0, headerEnd));
	std::string protocol;
	int status = 0;
	headers >> protocol >> status;
	if (status == 0) {
		throw std::runtime_error("The web bridge returned an invalid HTTP status.");
	}
	return {status, response.substr(headerEnd + 4)};
}

class RoutingOutputBuffer : public std::streambuf {
protected:
	int_type overflow(int_type character) override {
		if (traits_type::eq_int_type(character, traits_type::eof())) {
			return sync() == 0 ? traits_type::not_eof(character) : traits_type::eof();
		}
		const char value = traits_type::to_char_type(character);
		pending += value;
		if (value == '\n') {
			flushPending();
		}
		return character;
	}

	std::streamsize xsputn(const char* text, std::streamsize length) override {
		for (std::streamsize index = 0; index < length; ++index) {
			pending += text[index];
			if (text[index] == '\n') {
				flushPending();
			}
		}
		return length;
	}

	int sync() override {
		flushPending();
		return 0;
	}

private:
	std::string pending;

	void flushPending() {
		if (!pending.empty()) {
			outputText(pending);
			pending.clear();
		}
	}
};

class WebInputBuffer : public std::streambuf {
protected:
	int_type underflow() override {
		if (gptr() != nullptr && gptr() < egptr()) {
			return traits_type::to_int_type(*gptr());
		}

		while (true) {
			const HttpResponse response = sendHttpRequest("GET", "/api/input", "");
			if (response.status == 200) {
				input = response.body + '\n';
				setg(input.data(), input.data(), input.data() + input.size());
				return traits_type::to_int_type(*gptr());
			}
			if (response.status != 204) {
				throw std::runtime_error("The web bridge could not provide player input (HTTP "
					+ std::to_string(response.status) + ").");
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

private:
	std::string input;
};

RoutingOutputBuffer routingOutputBuffer;
WebInputBuffer webInputBuffer;
}

void configureOutput() {
	const char* mode = std::getenv("BEANZ_OUTPUT_MODE");
	webOutputEnabled = mode != nullptr && std::string(mode) == "web";
	if (webOutputEnabled) {
		originalOutputBuffer = std::cout.rdbuf(&routingOutputBuffer);
		std::cin.rdbuf(&webInputBuffer);
		std::cout.exceptions(std::ios::badbit);
		std::cin.exceptions(std::ios::badbit);
	}
}

bool isWebOutputEnabled() {
	return webOutputEnabled;
}

void outputText(const std::string& text) {
	if (!webOutputEnabled) {
		if (originalOutputBuffer != nullptr) {
			originalOutputBuffer->sputn(text.data(), static_cast<std::streamsize>(text.size()));
		} else {
			std::cout.write(text.data(), static_cast<std::streamsize>(text.size()));
		}
		return;
	}

	const HttpResponse response = sendHttpRequest("POST", "/api/output", "{\"text\":\"" + jsonEscape(text) + "\"}");
	if (response.status < 200 || response.status >= 300) {
		throw std::runtime_error("The web bridge rejected game output (HTTP " + std::to_string(response.status) + ").");
	}
}

std::string loadWebSaveData() {
	const HttpResponse response = sendHttpRequest("GET", "/api/save", "");
	if (response.status == 204) {
		return "";
	}
	if (response.status != 200) {
		throw std::runtime_error("The web bridge could not load the browser save (HTTP "
			+ std::to_string(response.status) + ").");
	}
	return response.body;
}

bool storeWebSaveData(const std::string& data) {
	const HttpResponse response = sendHttpRequest("POST", "/api/save", "{\"data\":\"" + jsonEscape(data) + "\"}");
	if (response.status == 413) {
		return false;
	}
	if (response.status != 202) {
		throw std::runtime_error("The web bridge could not store the browser save (HTTP "
			+ std::to_string(response.status) + ").");
	}
	return true;
}

void clearScreen() {
	if (webOutputEnabled) {
		outputText("\f");
		return;
	}
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/**	@brief
*
*	@return String.
*/
std::string getPlayerIn() {
	std::string playerIn;

	if (isWebOutputEnabled()) {
		std::getline(std::cin >> std::ws, playerIn);
		std::string normalizedInput;
		for (char character : playerIn) {
			if (character >= 'A' && character <= 'Z') {
				normalizedInput += static_cast<char>(character + ('a' - 'A'));
			} else {
				normalizedInput += character;
			}
		}
		std::cout << std::endl;
		return normalizedInput;
	}

	std::cin >> playerIn;

	int len = playerIn.length();

	std::string newPlayerIn;

	for (int i = 0; i < len; i++) 	{
		if (playerIn[i] < 'A' || playerIn[i] > 'z'){}        // do nothing
		else if (playerIn[i] > 'Z' && playerIn[i] < 'a'){}   // do nothing
		else if (playerIn[i] >= 'A' && playerIn[i] <= 'Z')
			{newPlayerIn += playerIn[i] + 32;}           // upper to lower
		else
			{newPlayerIn += playerIn[i];}                // no change
	}

	std::cout << std::endl;

	return newPlayerIn;
}


/**	@brief
*
*	@return Void.
*/
void nicePrint(std::string text, bool isOption /*false*/) {
	const int width = screenWidth - (isOption ? align : 0);
	int column = 0;
	std::istringstream words(text);
	std::string word;
	while (words >> word) {
		const int requiredWidth = static_cast<int>(word.length()) + (column > 0 ? 1 : 0);
		if (column > 0 && column + requiredWidth > width) {
			std::cout << std::endl;
			if (isOption) {
				std::cout << std::setw(align) << "";
			}
			column = 0;
		}
		if (column > 0) {
			std::cout << " ";
			++column;
		}
		std::cout << word;
		column += static_cast<int>(word.length());
	}
	std::cout << std::endl;
}

/*
@brief: Determnines if the inputted string is a help screen or not
@param: std::string screenID, The screen ID that you want to check if its a help screen.
@return: 1 if true, 0 if false
*/
bool isHelpScreen(std::string screenID){
	if(screenID.length() != 7){
		return 0;
	}
	if(screenID.substr(0, 6) == "LS0020"){
		return 1;
	}
	return 0;
}