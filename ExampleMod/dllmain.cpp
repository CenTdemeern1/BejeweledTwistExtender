#include <Engine.h>
#include <Extender/FuncInterceptor.h>
#include <HookFunctions.h>
#include <TwistFunctions.h>
#include <Extender/util.h>

void onPreInit(Sexy::WinTwistApp* app) {
    printf_s("Hello from a C++ native mod's preInit hook!");
}

void evilPreInit(Sexy::WinTwistApp* app) {
    printf_s("Hello! I am evil!");
}

void onBoardUpdate(TwistFunctions* game) {
    printf_s("The board has updated! Let's twist\n");
    //for (int y = 0; y < 7; y++) {
    //    for (int x = 0; x < 7; x++) {
    //        game->TwistGemsAt(false, x, y);
    //    }
    //}
}

//void __declspec(naked) levelUpMeterHoverInjection() {
//    __asm
//    {
//
//    }
//}

extern "C" bool __declspec(dllexport) __cdecl initMod(CodeInjection::FuncInterceptor* interceptor, HookFunctions* hooks)
{
    //interceptor->intercept(onPreInit, evilPreInit);
    //onPreInit(nullptr);

    // This is in the middle of an instruction(!!)
    // This patches the instruction at 0x6d5a67 to load the levelup requirement instead of the current level
    // Offset 0x204 in GameManager seems to be the levelup requirement
    inject_byte(0x6d5a69, 0x04);
    inject_byte(0x6d5a6A, 0x02);
    // Also useful to know: offset 0x200 in GameManager seems to be the progress towards the levelup requirement

    inject_nops(0x6D5A71, 12);

    //constexpr const char string[] = "%d%% of level %d or something idk\0";
    //                              "You have completed %d%% of Level %d";
    constexpr const char string[] = "You have scored %d out of %d points";
    for (int i = 0; string[i]; i++) {
        // 8-bit version
        inject_byte(0x7deac0, string[i]);
        // Wide version
        inject_byte(0x7dea78 + i * 2, string[i]);
        inject_byte(0x7dea79 + i * 2, 0);
    }
    hooks->registerPreInitHook(onPreInit);
    hooks->registerUpdateBoardHook(onBoardUpdate);
    return true;
}
