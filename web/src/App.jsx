import { useEffect, useRef, useState } from 'react';
import {
  ArrowUp,
  Backpack,
  Bean,
  CircleHelp,
  LoaderCircle,
  RefreshCw,
  Save,
  Wifi,
  WifiOff,
  X
} from 'lucide-react';

const parseScreen = (output) => {
  const screenStart = output.lastIndexOf('HP:');
  const screen = screenStart >= 0 ? output.slice(screenStart) : output;
  const lines = screen.split(/\r?\n/);
  const health = lines[0]?.match(/^HP:\s*(.*)$/)?.[1] ?? '';
  const narrative = [];
  const choices = [];
  let activeChoice = null;

  for (const line of lines.slice(1)) {
    const option = line.match(/^\s*\[(.+?)\]\s*--\s*(.*)$/);
    if (option) {
      activeChoice = { text: option[1].trim(), description: option[2].trim() };
      choices.push(activeChoice);
    } else if (activeChoice && line.trim()) {
      activeChoice.description = `${activeChoice.description} ${line.trim()}`.trim();
    } else if (!activeChoice) {
      narrative.push(line);
    }
  }

  const narrativeText = narrative.join('\n').trim();
  return {
    health,
    narrative: narrativeText,
    choices,
    isHelpScreen: narrativeText.startsWith('The following commands can be used at any time during the game:')
      || choices.some((choice) => choice.text.toLowerCase() === 'close')
  };
};

const parseInventory = (output) => {
  const items = [];
  let activeItem = null;

  for (const line of output.split(/\r?\n/)) {
    const itemLine = line.match(/^(.+?):\s+(.+?) item\.(.*)$/);
    if (itemLine) {
      const uses = itemLine[3].match(/(\d+) uses? remaining/);
      const restore = itemLine[3].match(/Restores (\d+) HP/);
      activeItem = {
        name: itemLine[1].trim(),
        itemClass: itemLine[2].trim(),
        uses: uses ? Number(uses[1]) : null,
        restore: restore ? Number(restore[1]) : null,
        description: ''
      };
      items.push(activeItem);
    } else if (!line.trim()) {
      activeItem = null;
    } else if (activeItem) {
      activeItem.description = `${activeItem.description} ${line.trim()}`.trim();
    }
  }

  return items;
};

const responseError = async (response, fallback) => {
  try {
    const body = await response.json();
    return body.error || `${fallback} (HTTP ${response.status})`;
  } catch {
    return `${fallback} (HTTP ${response.status})`;
  }
};

function InventoryContents({ items, ready, busy, onUse, onRefresh, onClose }) {
  return (
    <div className="rounded-2xl border border-white/10 bg-black/20 p-4">
      <div className="mb-3 flex items-center justify-between gap-2">
        <h3 className="font-semibold text-white">Inventory</h3>
        <button
          type="button"
          onClick={onRefresh}
          disabled={busy}
          aria-label="Refresh inventory"
          title="Refresh inventory"
          className="rounded-lg border border-white/10 p-2 text-slate-300 transition hover:border-violet-400/50 hover:text-white disabled:opacity-50"
        >
          <RefreshCw size={16} />
        </button>
      </div>
      {!ready ? (
        <p className="py-4 text-sm text-slate-400">Loading inventory...</p>
      ) : items.length ? (
        <div className="max-h-[34vh] space-y-2 overflow-y-auto pr-1">
          {items.map((item) => (
            <button
              key={item.name}
              type="button"
              onClick={() => onUse(item)}
              disabled={busy}
              className="w-full rounded-xl border border-white/10 bg-white/[0.04] p-3 text-left transition hover:border-violet-400/50 hover:bg-violet-500/10 disabled:cursor-not-allowed disabled:opacity-50"
            >
              <span className="flex flex-wrap items-baseline justify-between gap-x-3 gap-y-1">
                <span className="break-words font-semibold text-violet-200">{item.name}</span>
                <span className="text-xs text-slate-500">
                  {item.uses === null ? item.itemClass : `${item.uses} ${item.uses === 1 ? 'use' : 'uses'}`}
                </span>
              </span>
              {item.restore !== null && <span className="mt-1 block text-xs text-emerald-300">Restores {item.restore} HP</span>}
              {item.description && <span className="mt-2 block break-words text-sm leading-5 text-slate-400">{item.description}</span>}
              <span className="mt-2 block text-xs font-medium text-violet-300">Use one</span>
            </button>
          ))}
        </div>
      ) : (
        <p className="py-4 text-sm text-slate-400">{ready ? 'No items to display.' : 'Loading inventory...'}</p>
      )}
      <button
        type="button"
        onClick={onClose}
        disabled={busy}
        className="mt-3 w-full rounded-xl border border-white/10 px-3 py-2 text-sm font-medium text-slate-300 transition hover:bg-white/10 disabled:opacity-50"
      >
        Back to scene
      </button>
    </div>
  );
}

export default function App() {
  const [output, setOutput] = useState('');
  const [inventoryScene, setInventoryScene] = useState('');
  const [input, setInput] = useState('');
  const [isSending, setIsSending] = useState(false);
  const [inventoryOpen, setInventoryOpen] = useState(false);
  const [inventoryActionPending, setInventoryActionPending] = useState(false);
  const [savePanelOpen, setSavePanelOpen] = useState(false);
  const [saveStatus, setSaveStatus] = useState('');
  const [isConnected, setIsConnected] = useState(true);
  const [gameDone, setGameDone] = useState(false);
  const [error, setError] = useState('');
  const cursor = useRef(0);
  const outputRef = useRef('');
  const lastNonHelpScene = useRef('');
  const inventoryOpenRef = useRef(inventoryOpen);
  const inputRef = useRef(null);
  const choicesRef = useRef(null);
  const [hasChoiceOverflow, setHasChoiceOverflow] = useState(false);
  const screen = parseScreen(output);
  const savedScreen = parseScreen(inventoryScene);
  const visibleScreen = inventoryOpen ? savedScreen : screen;
  const isHelpScreen = visibleScreen.isHelpScreen;
  const inventoryItems = parseInventory(output);
  const saveStatusClass = saveStatus.startsWith('Could not') ? 'text-red-300' : 'text-emerald-300';
  const inventoryReady = output.length > 0 && !output.includes('HP:');
  const inventoryBusy = isSending || inventoryActionPending;
  inventoryOpenRef.current = inventoryOpen;

  useEffect(() => {
    const choicesElement = choicesRef.current;
    if (!choicesElement) {
      setHasChoiceOverflow(false);
      return undefined;
    }

    const updateOverflow = () => {
      setHasChoiceOverflow(choicesElement.scrollWidth > choicesElement.clientWidth + 1);
    };
    const observer = new ResizeObserver(updateOverflow);
    observer.observe(choicesElement);
    updateOverflow();
    return () => observer.disconnect();
  }, [visibleScreen.choices.length, inventoryOpen]);

  useEffect(() => {
    if (inventoryOpen && inventoryReady) {
      setInventoryActionPending(false);
    }
  }, [inventoryOpen, inventoryReady]);

  useEffect(() => {
    let active = true;
    let timer;

    const poll = async () => {
      try {
        const response = await fetch(`/api/events?after=${cursor.current}`);
        if (!response.ok) {
          throw new Error(await responseError(response, 'Could not receive game output.'));
        }
        const data = await response.json();
        if (!active) return;

        if (data.saveCookieStatus === 'stored') {
          setSaveStatus('Saved in this browser.');
        } else if (data.saveCookieStatus === 'error') {
          setSaveStatus('Could not store save in browser cookies.');
        }
        if (data.events.length) {
          cursor.current = data.events[data.events.length - 1].id;
          let nextOutput = outputRef.current;
          for (const event of data.events) {
            const text = event.text || '';
            if (text.includes('Could not save your game.')) {
              setSaveStatus('Could not store save in browser cookies.');
            }
            if (text === '\f') {
              if (nextOutput.includes('HP:') && !parseScreen(nextOutput).isHelpScreen) {
                lastNonHelpScene.current = nextOutput;
              }
              nextOutput = '';
            } else {
              nextOutput += text;
            }
          }
          outputRef.current = nextOutput;
          if (
            inventoryOpenRef.current
            && !nextOutput.includes('HP:')
            && (
              nextOutput.includes('Type Help for a list of commands, or exit to go back to the game:')
              || nextOutput.includes('No Items to Display!')
              || parseInventory(nextOutput).length > 0
            )
          ) {
            setInventoryActionPending(false);
          }
          setOutput(nextOutput);
        }
        setGameDone(Boolean(data.done));
        setIsConnected(true);
        setError(data.error || '');
      } catch (pollError) {
        if (active) {
          setIsConnected(false);
          setError(pollError.message || 'Could not reach the game server.');
        }
      } finally {
        if (active) timer = window.setTimeout(poll, 500);
      }
    };

    void poll();
    return () => {
      active = false;
      window.clearTimeout(timer);
    };
  }, []);

  const submitCommands = async (commands, clearInput = false) => {
    if (!commands.length || isSending || gameDone) return false;

    setIsSending(true);
    setError('');
    try {
      const response = await fetch('/api/input', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ inputs: commands })
      });
      if (!response.ok) {
        throw new Error(await responseError(response, 'Could not submit that choice.'));
      }
      if (clearInput) setInput('');
      inputRef.current?.focus();
      return true;
    } catch (sendError) {
      setError(sendError.message || 'Could not submit that choice.');
      return false;
    } finally {
      setIsSending(false);
    }
  };

  const sendInput = async (value) => {
    const command = value.trim();
    if (!command) return false;

    const normalized = command.toLowerCase();
    let commands = [command];
    if (normalized === 'inventory') {
      setInventoryScene(screen.isHelpScreen ? lastNonHelpScene.current || output : output);
      setInventoryOpen(true);
      setInventoryActionPending(true);
      if (screen.isHelpScreen) commands = ['close', command];
    } else if (normalized === 'save') {
      setSavePanelOpen(true);
      setSaveStatus('Saving...');
      if (inventoryOpen) {
        commands = ['exit', command];
        setInventoryOpen(false);
        setInventoryActionPending(false);
      } else if (screen.isHelpScreen) {
        commands = ['close', command];
      }
    } else if (normalized === 'exit' && inventoryOpen) {
      setInventoryOpen(false);
      setInventoryActionPending(false);
    }

    return submitCommands(commands, true);
  };

  const toggleInventory = () => {
    if (inventoryOpen) {
      void submitCommands(['exit']).then((accepted) => {
        if (accepted) {
          setInventoryOpen(false);
          setInventoryActionPending(false);
        }
      });
      return;
    }
    void sendInput('inventory');
  };

  const refreshInventory = () => {
    setInventoryActionPending(true);
    void submitCommands(['exit', 'inventory']).then((accepted) => {
      if (!accepted) setInventoryActionPending(false);
    });
  };

  const useInventoryItem = (item) => {
    setInventoryActionPending(true);
    void submitCommands(['use', item.name, '1', 'exit', 'inventory']).then((accepted) => {
      if (!accepted) setInventoryActionPending(false);
    });
  };

  const closeInventory = () => {
    void submitCommands(['exit']).then((accepted) => {
      if (accepted) {
        setInventoryOpen(false);
        setInventoryActionPending(false);
      }
    });
  };

  const saveGame = () => {
    setSaveStatus('Saving...');
    void sendInput('save');
  };

  const toggleSavePanel = () => {
    if (savePanelOpen) {
      setSavePanelOpen(false);
    } else {
      setSavePanelOpen(true);
      saveGame();
    }
  };

  const toggleHelp = () => {
    const command = isHelpScreen ? 'close' : 'help';
    if (inventoryOpen) {
      void submitCommands(['exit', command]).then((accepted) => {
        if (accepted) {
          setInventoryOpen(false);
          setInventoryActionPending(false);
        }
      });
    } else {
      void sendInput(command);
    }
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    void sendInput(input);
  };

  const inventoryContents = (
    <InventoryContents
      items={inventoryItems}
      ready={inventoryReady}
      busy={inventoryBusy}
      onUse={useInventoryItem}
      onRefresh={refreshInventory}
      onClose={closeInventory}
    />
  );

  return (
    <div className="flex h-[100dvh] min-h-[30rem] flex-col overflow-hidden bg-[#09090b] font-sans text-slate-100">
      <header className="flex shrink-0 items-center justify-between border-b border-white/10 bg-[#09090b]/95 px-4 py-3 backdrop-blur sm:px-8">
        <button
          type="button"
          onClick={() => void sendInput('title')}
          disabled={isSending || inventoryActionPending || gameDone}
          aria-label="Return to title screen"
          className="flex items-center gap-3 rounded-xl text-left transition hover:opacity-80 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-violet-400 disabled:cursor-not-allowed disabled:opacity-50"
        >
          <span className="flex h-9 w-9 items-center justify-center rounded-xl bg-violet-500/15 text-violet-300">
            <Bean size={20} />
          </span>
          <div>
            <p className="text-sm font-semibold tracking-wide text-white sm:text-base">Beanz 2.0</p>
            <p className="hidden text-xs text-slate-500 min-[360px]:block">A text adventure</p>
          </div>
        </button>
        <div className="flex items-center gap-3">
          <button
            type="button"
            onClick={toggleHelp}
            disabled={isSending || inventoryActionPending || gameDone}
            aria-label={isHelpScreen ? 'Close help' : 'Help'}
            className="flex items-center gap-2 rounded-full border border-white/10 px-3 py-2 text-xs font-medium text-slate-300 transition hover:border-violet-400/50 hover:text-white disabled:opacity-50 xl:hidden"
          >
            {isHelpScreen ? <X size={15} /> : <CircleHelp size={15} />}
            <span className="hidden min-[360px]:inline">{isHelpScreen ? 'Close help' : 'Help'}</span>
          </button>
          <div className={`flex items-center gap-2 text-xs ${isConnected ? 'text-emerald-300' : 'text-amber-300'}`} role="status">
            {isConnected ? <Wifi size={15} /> : <WifiOff size={15} />}
            <span className="hidden sm:inline">
              {gameDone ? 'Game ended' : isConnected ? 'Connected' : 'Reconnecting'}
            </span>
          </div>
        </div>
      </header>

      <main className="mx-auto flex min-h-0 w-full max-w-[96rem] flex-1 flex-col gap-3 px-3 py-3 sm:px-6 sm:py-5 xl:flex-row xl:gap-4 xl:px-8 xl:py-6">
        <aside className={`hidden shrink-0 self-start xl:flex ${savePanelOpen ? 'w-64' : 'w-40'}`}>
          <div className="w-full rounded-2xl border border-white/10 bg-white/[0.03] p-3">
            <button
              type="button"
              onClick={toggleHelp}
              disabled={isSending || inventoryActionPending || gameDone}
              aria-expanded={isHelpScreen}
              className={`flex w-full items-center gap-3 rounded-xl border px-3 py-3 text-left text-sm font-semibold transition disabled:opacity-50 ${
                isHelpScreen
                  ? 'border-violet-400/50 bg-violet-500/15 text-violet-200'
                  : 'border-white/10 bg-white/[0.04] text-slate-200 hover:border-violet-400/50 hover:text-white'
              }`}
            >
              {isHelpScreen ? <X size={17} /> : <CircleHelp size={17} />}
              {isHelpScreen ? 'Close help' : 'Help'}
            </button>
            <button
              type="button"
              onClick={toggleSavePanel}
              disabled={isSending || inventoryActionPending || gameDone}
              aria-expanded={savePanelOpen}
              className="mt-3 flex w-full items-center gap-3 rounded-xl border border-white/10 bg-white/[0.04] px-3 py-3 text-left text-sm font-semibold text-slate-200 transition hover:border-violet-400/50 hover:text-white disabled:opacity-50"
            >
              <Save size={17} />
              Save
            </button>
            {savePanelOpen && (
              <div className="mt-3 rounded-xl border border-white/10 bg-black/20 p-4">
                <h2 className="font-semibold text-white">Save progress</h2>
                <p className="mt-2 text-sm leading-5 text-slate-400">Save your current position and inventory.</p>
                <p className={`mt-3 min-h-5 text-sm ${saveStatusClass}`} role="status">{saveStatus}</p>
                <button
                  type="button"
                  onClick={saveGame}
                  disabled={isSending || inventoryActionPending || gameDone}
                  className="mt-2 w-full rounded-xl bg-violet-500 px-3 py-2 text-sm font-semibold text-white transition hover:bg-violet-400 disabled:opacity-50"
                >
                  Save now
                </button>
              </div>
            )}
          </div>
        </aside>

        <section className="flex min-h-0 min-w-0 flex-1 flex-col overflow-hidden rounded-3xl border border-white/10 bg-white/[0.03] shadow-2xl shadow-black/30">
          <div className="grid shrink-0 grid-cols-[minmax(0,1fr)_auto_minmax(0,1fr)] items-center border-b border-white/10 px-3 py-3 sm:px-5 lg:px-7 xl:flex xl:justify-between">
            <p className="whitespace-nowrap text-[9px] font-semibold uppercase tracking-normal text-violet-300 sm:text-sm sm:tracking-[0.18em]">
              Current scene
            </p>
            <button
              type="button"
              onClick={toggleInventory}
              disabled={isSending || inventoryActionPending || gameDone}
              aria-expanded={inventoryOpen}
              aria-label={inventoryOpen ? 'Return from inventory' : 'Open inventory'}
              className={`flex items-center gap-1.5 rounded-full border px-2.5 py-1.5 text-xs font-medium transition disabled:opacity-50 xl:hidden ${
                inventoryOpen
                  ? 'border-violet-400/50 bg-violet-500/15 text-violet-200'
                  : 'border-white/10 text-slate-300 hover:border-violet-400/50 hover:text-white'
              }`}
            >
              <Backpack size={14} />
              <span className="hidden sm:inline">{inventoryOpen ? 'Back' : 'Inventory'}</span>
            </button>
            <div className="flex items-center justify-self-end gap-2 xl:ml-auto">
              {visibleScreen.health && (
                <p className="whitespace-nowrap rounded-full border border-white/10 bg-black/20 px-2.5 py-1 text-xs text-slate-300 sm:px-3 sm:text-sm">
                  HP {visibleScreen.health}
                </p>
              )}
            </div>
          </div>

          <div className="min-h-0 flex-1 overflow-y-auto px-4 py-4 sm:px-7 sm:py-6" aria-live="polite">
            {inventoryOpen ? (
              <>
                <div className="hidden xl:block">
                  {savedScreen.narrative
                    ? <p className="whitespace-pre-wrap text-base leading-8 text-slate-200 sm:text-lg sm:leading-9">{savedScreen.narrative}</p>
                    : <p className="text-slate-400">Your scene is ready when you close inventory.</p>}
                </div>
                <div className="xl:hidden">{inventoryContents}</div>
              </>
            ) : screen.narrative ? (
              <p className="whitespace-pre-wrap text-base leading-8 text-slate-200 sm:text-lg sm:leading-9">{screen.narrative}</p>
            ) : gameDone ? (
              <p className="text-slate-400">The game has ended.</p>
            ) : (
              <div className="flex items-center gap-3 py-4 text-slate-400">
                <LoaderCircle className="animate-spin text-violet-300" size={19} />
                <p>Loading the adventure...</p>
              </div>
            )}
          </div>

          {inventoryOpen ? (
            <div className="shrink-0 border-t border-white/10 px-4 py-4 sm:px-7">
              <div className="flex items-center justify-between gap-3">
                <div>
                  <p className="text-sm text-slate-400 xl:text-xs">Manage items in the inventory panel.</p>
                  {saveStatus && <p className={`mt-1 text-xs ${saveStatusClass} xl:hidden`} role="status">{saveStatus}</p>}
                </div>
                <button
                  type="button"
                  onClick={saveGame}
                  disabled={isSending || inventoryActionPending || gameDone}
                  aria-label="Save game"
                  title="Save game"
                  className="rounded-lg border border-white/10 p-2 text-slate-300 transition hover:border-violet-400/50 hover:text-white disabled:opacity-50 xl:hidden"
                >
                  <Save size={16} />
                </button>
              </div>
            </div>
          ) : (
            <section className="shrink-0 border-t border-white/10 px-4 py-4 sm:px-7" aria-label="Available choices">
              {saveStatus && <p className={`mb-2 text-xs ${saveStatusClass} xl:hidden`} role="status">{saveStatus}</p>}
              <div className="mb-3 flex items-center justify-between gap-3">
                <h2 className="text-xs font-semibold uppercase tracking-[0.2em] text-slate-400">Choose what to do</h2>
                <div className="flex items-center gap-3">
                  {hasChoiceOverflow && <span className="hidden text-xs text-slate-500 min-[400px]:inline">Scroll for more</span>}
                  <button
                    type="button"
                    onClick={saveGame}
                    disabled={isSending || inventoryActionPending || gameDone}
                    aria-label="Save game"
                    title="Save game"
                    className="rounded-lg border border-white/10 p-2 text-slate-300 transition hover:border-violet-400/50 hover:text-white disabled:opacity-50 xl:hidden"
                  >
                    <Save size={16} />
                  </button>
                </div>
              </div>
              {screen.choices.length ? (
                <div ref={choicesRef} className="flex gap-3 overflow-x-auto pb-2">
                  {screen.choices.map((choice, index) => (
                    <button
                      key={`${choice.text}-${index}`}
                      type="button"
                      disabled={isSending || inventoryActionPending || gameDone}
                      onClick={() => void sendInput(choice.text)}
                      className="min-w-[16rem] max-w-[22rem] flex-1 basis-1/3 rounded-2xl border border-white/10 bg-white/[0.04] p-4 text-left transition hover:border-violet-400/50 hover:bg-violet-500/10 focus:outline-none focus:ring-2 focus:ring-violet-400 disabled:cursor-not-allowed disabled:opacity-50"
                    >
                      <span className="block break-words text-sm font-semibold text-violet-200">{choice.text}</span>
                      <span className="mt-2 block break-words text-sm leading-6 text-slate-400">{choice.description}</span>
                    </button>
                  ))}
                </div>
              ) : (
                <p className="text-sm text-slate-500">Enter a command or choice below.</p>
              )}
            </section>
          )}
        </section>

        <aside className={`hidden shrink-0 self-start xl:flex ${inventoryOpen ? 'w-80' : 'w-40'}`}>
          <div className="w-full rounded-2xl border border-white/10 bg-white/[0.03] p-3">
            <button
              type="button"
              onClick={toggleInventory}
              disabled={isSending || inventoryActionPending || gameDone}
              aria-expanded={inventoryOpen}
              className={`flex w-full items-center gap-3 rounded-xl border px-3 py-3 text-left text-sm font-semibold transition disabled:opacity-50 ${
                inventoryOpen
                  ? 'border-violet-400/50 bg-violet-500/15 text-violet-200'
                  : 'border-white/10 bg-white/[0.04] text-slate-200 hover:border-violet-400/50 hover:text-white'
              }`}
            >
              <Backpack size={17} />
              Inventory
            </button>
            {inventoryOpen && (
              <div className="mt-3">
                {inventoryContents}
              </div>
            )}
          </div>
        </aside>

      </main>

      <form onSubmit={handleSubmit} className="mx-auto w-full max-w-[96rem] shrink-0 px-3 pb-3 sm:px-6 sm:pb-5 lg:px-8">
        <div className="flex items-center gap-2 rounded-2xl border border-white/10 bg-white/[0.05] p-2 pl-4 transition focus-within:border-violet-400/60">
          <label htmlFor="player-input" className="sr-only">Type a choice or command</label>
          <input
            ref={inputRef}
            id="player-input"
            type="text"
            value={input}
            onChange={(event) => setInput(event.target.value)}
            placeholder={inventoryOpen ? 'Type an inventory command...' : 'Type a choice or command...'}
            autoComplete="off"
            disabled={inventoryActionPending || gameDone}
            className="min-w-0 flex-1 bg-transparent py-2 text-sm text-white outline-none placeholder:text-slate-500"
          />
          <button
            type="submit"
            disabled={!input.trim() || isSending || inventoryActionPending || gameDone}
            aria-label="Submit choice"
            className="flex h-10 w-10 shrink-0 items-center justify-center rounded-xl bg-violet-500 text-white transition hover:bg-violet-400 disabled:cursor-not-allowed disabled:opacity-40"
          >
            <ArrowUp size={19} />
          </button>
        </div>
        {error && <p className="mt-2 text-sm text-red-300" role="alert">{error}</p>}
      </form>
    </div>
  );
}
