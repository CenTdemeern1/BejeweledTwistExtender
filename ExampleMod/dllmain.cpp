#include <Engine.h>
#include <Extender/FuncInterceptor.h>
#include <HookFunctions.h>
#include <TwistFunctions.h>
#include <Extender/util.h>
#include <Version.h>

#define BOILERPLATE extern "C" bool __declspec(dllexport) __cdecl


BOILERPLATE isCompatibleWithVersion(Version* version) {
    Version compiledAgainst = getTwistExtenderVersion();
    // Checks whether the version actually loading this mod (the function argument)
    // is compatible with the version of TwistExtender this mod was compiled against
    return meetsVersionRequirement(version, &compiledAgainst);
}

void onPreInit(Sexy::WinTwistApp* app) {
    printf_s("Hello world from ExampleMod's preInit hook!");
}

BOILERPLATE initMod(CodeInjection::FuncInterceptor* interceptor, HookFunctions* hooks)
{
    hooks->registerPreInitHook(onPreInit);

    // This is in the middle of an instruction(!!)
    // This patches the instruction at 0x6d5a67 to load the levelup requirement instead of the current level
    // Offset 0x204 in GameManager is the levelup requirement
    inject_byte(0x6d5a69, 0x04);
    inject_byte(0x6d5a6A, 0x02);

    // Remove the math operations being applied to the current level progress value
    inject_nops(0x6D5A71, 12);

    // Replace the tooltip text. This string is the same length as the original!
    //                                   "You have completed %d%% of Level %d"
    constexpr const char tooltipText[] = "You have scored %d out of %d points";
    constexpr const wchar_t tooltipTextWide[] = L"You have scored %d out of %d points";
    CodeInjection::CodeInjectionStream stream((void*)0x7dea78, 108);
    stream.write(tooltipTextWide, sizeof(tooltipTextWide));
    stream.write(tooltipText, sizeof(tooltipText));
    stream.flush();

    printf_s("ExampleMod has been initialized successfully!\n");
    return true;
}
