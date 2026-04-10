#include "Game.h"

#include <cstdio>
#include <exception>
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

// So relative paths like assets/fonts/... work when the exe is started from another working directory
// (Explorer, shortcuts, or some IDE run configurations).
static void setWorkingDirectoryNextToExecutable() {
#ifdef _WIN32
    wchar_t path[MAX_PATH]{};
    const DWORD n = GetModuleFileNameW(nullptr, path, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) {
        return;
    }
    std::wstring full(path, n);
    const auto slash = full.find_last_of(L"\\/");
    if (slash != std::wstring::npos) {
        SetCurrentDirectoryW(full.substr(0, slash).c_str());
    }
#endif
}

int main() {
    setWorkingDirectoryNextToExecutable();
    try {
        Game game;
        game.run();
    } catch (const std::exception& ex) {
        std::fprintf(stderr, "Breakout: %s\n", ex.what());
        return 1;
    } catch (...) {
        std::fprintf(stderr, "Breakout: unknown error.\n");
        return 1;
    }
    return 0;
}
