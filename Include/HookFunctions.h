#ifndef __HOOKFUNCTIONS_H_
#define __HOOKFUNCTIONS_H_

#include <Engine.h>
#include <TwistFunctions.h>

typedef void(*PreInitHook)(Sexy::WinTwistApp* app);
typedef void(*PostInitHook)(Sexy::WinTwistApp* app);
typedef void(*UpdateBoardHook)(TwistFunctions* game);
typedef void(*BoardKeyPressHook)(TwistFunctions* game, int key);
typedef bool(*ShouldAllowSelectionsHooks)(TwistFunctions* game, bool& force);
typedef void(*WindowInputHook)(Sexy::WinTwistApp* app, int input);

typedef struct {
    int (*registerPreInitHook)(PreInitHook preInit);
    int (*registerPostInitHook)(PostInitHook postInit);
    int (*registerUpdateBoardHook)(UpdateBoardHook updateBoard);
    int (*registerBoardKeyPressHook)(BoardKeyPressHook boardKeyPress);
    int (*registerShouldAllowSelectionsHook)(ShouldAllowSelectionsHooks shouldAllowSelections);
    int (*registerWindowInputHook)(WindowInputHook windowInput);

    void (*removePreInitHook)(int index);
    void (*removePostInitHook)(int index);
    void (*removeUpdateBoardHook)(int index);
    void (*removeBoardKeyPressHook)(int index);
    void (*removeShouldAllowSelectionsHook)(int index);
    void (*removeWindowInputHook)(int index);

    void (*callPreInitHooks)(Sexy::WinTwistApp* app);
    void (*callPostInitHooks)(Sexy::WinTwistApp* app);
    void (*callUpdateBoardHooks)(TwistFunctions* game);
    void (*callBoardKeyPressHooks)(TwistFunctions* game, int key);
    bool (*callShouldAllowSelectionsHooks)(TwistFunctions* game);
    void (*callWindowInputHooks)(Sexy::WinTwistApp* app, int input);
} HookFunctions;

#endif // __HOOKFUNCTIONS_H_
