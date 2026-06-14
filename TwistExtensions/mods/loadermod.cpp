#include "loadermod.h"

#include "../HookFunctions.h"
#include "../NativeModApi.h"
#include <Version.h>
#include <Extender/util.h>

#include <filesystem>
#include <regex>

#include <Windows.h>

namespace LoaderMod
{
    constexpr const char MODS_DIRECTORY[] = "data\\mods";
    constexpr const char MOD_FILE_EXTENSION[] = ".dll";
    constexpr const char ERROR_DIALOG_TITLE[] = "Error while loading native mod";
    constexpr const char ERROR_DIALOG_MESSAGE[] = "There was a problem while loading a mod:\n\
%s\n\
\n\
Would you like to continue launching the game anyway?\n\
This might cause the game to become unstable.";

    void ensureAllocSuccess(const char* string) {
        if (string == NULL) {
            printf("Could not allocate memory to format the error string. You should free up some memory or something\n");
            ExitProcess(3);
        }
    }

    char* allocateFormat(const char* string, int count, ...) {
        va_list args;
        va_start(args, count);
        va_list args2;
        va_copy(args2, args);

        int length = vsnprintf(NULL, 0, string, args) + 1;
        va_end(args);

        char* buffer = (char*)malloc(length);
        if (buffer != NULL) {
            vsprintf_s(buffer, length, string, args2);
        }
        va_end(args2);

        return buffer;
    }

    void popupErrorMessage(const char* message) {
        char* formattedMessage = allocateFormat(ERROR_DIALOG_MESSAGE, 1, message);
        ensureAllocSuccess(formattedMessage);
        int chosenOption = MessageBox(
            NULL,
            formattedMessage,
            ERROR_DIALOG_TITLE,
            MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2
        );
        free(formattedMessage);
        if (chosenOption == IDNO) {
            ExitProcess(2);
        }
    }

    LPTSTR formatNativeError(va_list* args)
    {
        LPTSTR message = nullptr;
        DWORD error = GetLastError();
        if (
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&message,
                0,
                args
            ) == NULL
            )
        {
            printf_s("Could not format error! This must be one heck of a problem\n");
            LocalFree(message);
            return nullptr;
        }
        return message;
    }

    void showNativeError(int argCount, ...)
    {
        va_list args;
        va_start(args, argCount);
        LPTSTR message = formatNativeError(&args);
        ensureAllocSuccess(message);
        printf_s("%s\n", message);
        popupErrorMessage(message);
        LocalFree(message);
    }

    void unload(HMODULE library, LPCWSTR libPath, LPCSTR reason)
    {
        char* message = allocateFormat("Native mod %S %s", 2, libPath, reason);
        printf_s("%s; unloading\n", message);
        popupErrorMessage(message);
        free(message);
        if (!FreeLibrary(library)) {
            showNativeError(0);
            printf("Failed to unload.\n");
        }
    }

    void begin(CodeInjection::FuncInterceptor* hook)
    {
        // Yep! This module's entire shtick is calling LoadLibrary in DllMain. I know, crimes against Windows and whatever.
        // Just behave yourselves and don't create any dependency cycles :)

        Version twistExtenderVersion = getTwistExtenderVersion();

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
                std::string libPathString = p.path().string();
                showNativeError(1, libPathString.c_str());
                printf_s("Failed to load native mod %S; skipping\n", libPath);
                continue;
            }

            IsCompatibleFn isCompatible = (IsCompatibleFn)GetProcAddress(library, ISCOMPATIBLEFN_NAME);
            if (isCompatible == NULL) {
                unload(library, libPath, "does not have isCompatibleWithVersion symbol");
                continue;
            }

            if (!isCompatible(&twistExtenderVersion)) {
                unload(library, libPath, "is not compatible with this version of BejeweledTwistExtender");
                continue;
            }

            InitModFn initMod = (InitModFn)GetProcAddress(library, INITMODFN_NAME);
            if (initMod == NULL) {
                unload(library, libPath, "does not have initMod symbol");
                continue;
            }

            if (!initMod(hook, &gHookFunctions)) {
                unload(library, libPath, "failed to initialize");
                continue;
            }
        }
    }
}

void initLoaderMod(CodeInjection::FuncInterceptor* hook)
{
    printf("Native mod loader is starting!\n");

    LoaderMod::begin(hook);
}
