#include <Windows.h>

#include <Addresses.h>
#include <CodeInjection.h>
#include <Version.h>
#include <Extender/CodeAllocator.h>
#include <Extender/CodeInjectionStream.h>
#include <Extender/FuncInterceptor.h>
#include <Extender/util.h>
#include "mods/mods.h"
#include "Engine.h"

void fixFloatingPointSupport(CodeInjection::FuncInterceptor* hook);

namespace
{
    CodeInjection::CodeAllocator* codeAlloc;
    CodeInjection::CodeInjectionStream* injectionStream;
    CodeInjection::FuncInterceptor* hook;

    bool initCore()
    {
        printf("> Initializing Core\n");
        codeAlloc = new CodeInjection::CodeAllocator();
        injectionStream = new CodeInjection::CodeInjectionStream(reinterpret_cast<void*>(BJT_TEXT_START), BJT_TEXT_SIZE);
        hook = new CodeInjection::FuncInterceptor(injectionStream, codeAlloc);

        fixFloatingPointSupport(hook);

        return true;
    }


    void printVersion(Version* version) {
        printf_s("%d.%d.%d", version->major, version->minor, version->patch);
        if (version->prerelease) {
            printf_s(" prerelease %d", version->prerelease);
        }
        if (version->prereleaseCompatible && version->prereleaseCompatible != version->prerelease) {
            printf_s(" (compatible with prerelease %d mods and newer)", version->prereleaseCompatible);
        }
        printf("\n");
    }

    void checkVersion() {
        printf("BejeweledTwistExtender ");
        Version twistExtenderVersion = getTwistExtenderVersion();
        printVersion(&twistExtenderVersion);

        printf("CodeInjection ");
        Version codeInjectionVersion = getCodeInjectionVersion();
        printVersion(&codeInjectionVersion);

        if (twistExtenderVersion != codeInjectionVersion) {
            printf("Version mismatch!!");
            MessageBox(
                NULL,
                "The BejeweledTwistExtender version does not match the CodeInjection version.\n\
Did you forget to update one of the DLLs?\n\
Start the game with the debug console enabled for more information.\n\
The game will now close.",
                "Version mismatch",
                MB_OK | MB_ICONERROR
            );
            ExitProcess(1);
        }
    }

    bool initTwistExtender()
    {
        printf("== Initializing Twist Extender ==\n");
        checkVersion();
        if (!initCore())
        {
            setLastError("Failed to initialize core!");
            return false;
        }

        if (!initMods(hook))
        {
            setLastError("Failed to initialize one or more mods!");
            return false;
        }

        printf("Twist Extender Loaded Successfully!\n");

        return true;
    }
}

bool verifyGame();

extern "C" __declspec(dllexport) bool loadTwistExtender()
{
    const char* testPointer = reinterpret_cast<const char*>(BJT_VERIFY_TEXT);
    const char* testStr = "BejeweledTwist";

    if (!test_string_pointer(testPointer, testStr))
    {
        setLastError("TwistExtender is only designed for Bejeweled Twist from Popcap.com");
        return false;
    }

    return initTwistExtender();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            if (!loadTwistExtender())
            {
                std::string msg = "TwistExtender Initialization Failed!";
                if (lastError.length() > 0)
                    msg.append("\n\n" + lastError);
                MessageBox(nullptr, msg.c_str(), "TwistExtender", MB_OK | MB_ICONERROR);
                TerminateProcess(GetCurrentProcess(), 0);
            }
            break;
        case DLL_PROCESS_DETACH:
            break;
        default:
            break;
    }

    return TRUE;
}
