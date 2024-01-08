#include "../include/utility.h"

class Inventory {
private:
    std::list<std::string> inventory;

public:
    Inventory();
    ~Inventory();

    void add_item(std::string item);
    void rem_item(std::string item);
};