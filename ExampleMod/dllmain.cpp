// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#include <Engine.h>
#include <Extender/FuncInterceptor.h>
#include <Hooks.cpp>
//#include <extender/util.cpp>
//#include <BejeweledTwist.cpp>

void onPreInit(Sexy::WinTwistApp* app) {
    printf_s("Hello from a C++ native mod's preInit hook!");
}

void evilPreInit(Sexy::WinTwistApp* app) {
    printf_s("Hello! I am evil!");
}

//void onBoardUpdate(BejeweledTwist* game) {
//    printf_s("The board has updated! Let's twist");
//    game->TwistGemsAt(true, 3, 3);
//}

extern "C" bool __declspec(dllexport) __cdecl initMod(CodeInjection::FuncInterceptor* interceptor, Hooks* hooks)
{
    interceptor->intercept(onPreInit, evilPreInit);
    hooks->registerPreInitHook(onPreInit);
    //hooks->registerUpdateBoardHook(onBoardUpdate);
    return true;
}
