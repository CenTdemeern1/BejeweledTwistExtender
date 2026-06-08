#include "loadermod.h"

#include "../HookFunctions.h"
#include "Extender/util.h"
#include "../NativeModApi.h"

#include <filesystem>
#include <regex>

#include <Windows.h>

namespace LoaderMod
{
    static const char MODS_DIRECTORY[] = "data\\mods";
    static const char MOD_FILE_EXTENSION[] = ".dll";

    void logNativeError()
    {
        LPTSTR message = nullptr;
        DWORD error = GetLastError();
        if (
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&message,
                0,
                NULL
            ) == NULL
            )
        {
            printf_s("Could not format error! This must be one heck of a problem\n");
            return;
        }
        printf_s("%s\n", message);
        LocalFree(message);
    }

    void begin(CodeInjection::FuncInterceptor* hook)
    {
        // Yep! This module's entire shtick is calling LoadLibrary in DllMain. I know, crimes against Windows and whatever.
        // Just behave yourselves and don't create any dependency cycles :)

        if (!std::filesystem::exists(MODS_DIRECTORY))
            std::filesystem::create_directories(MODS_DIRECTORY);
        for (auto& p : std::filesystem::directory_iterator(MODS_DIRECTORY))
        {
            if (p.is_directory()) continue;
            if (p.path().extension() != MOD_FILE_EXTENSION) continue;

            LPCWSTR libPath = p.path().c_str();
            printf_s("Loading native mod: %S\n", libPath);
            HMODULE library = LoadLibraryW(libPath);
            if (library == NULL) {
                logNativeError();
                printf_s("Failed to load native mod %S; skipping\n", libPath);
                continue;
            }

            InitModFn initMod = (InitModFn)GetProcAddress(library, "initMod");
            if (initMod == NULL) {
                printf_s("Native mod %S does not have initMod; unloading\n", libPath);
                if (!FreeLibrary(library)) {
                    logNativeError();
                    printf_s("Failed to unload.\n");
                }
                continue;
            }

            if (!initMod(hook, &gHookFunctions)) {
                printf_s("Native mod %S failed to initialize; unloading\n", libPath);
                if (!FreeLibrary(library)) {
                    logNativeError();
                    printf_s("Failed to unload.\n");
                }
            }
        }
    }
}

void initLoaderMod(CodeInjection::FuncInterceptor* hook)
{
    printf_s("Native mod loader is starting!\n");

    LoaderMod::begin(hook);
}
