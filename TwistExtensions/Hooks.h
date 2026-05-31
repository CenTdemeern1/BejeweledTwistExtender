#pragma once

#include <string>
#include <map>

#include <Engine.h>
#include "BejeweledTwist.h"

typedef void(*PreInitHook)(Sexy::WinTwistApp* app);
typedef void(*PostInitHook)(Sexy::WinTwistApp* app);
typedef void(*UpdateBoardHook)();
typedef void(*BoardKeyPressHook)(int key);
typedef bool(*ShouldAllowSelectionsHooks)(bool& force);
typedef void(*WindowInputHook)(Sexy::WinTwistApp* app, int input);

class Hooks
{
public:
    Hooks();
    virtual ~Hooks();

    int registerPreInitHook(PreInitHook preInit);
    int registerPostInitHook(PostInitHook postInit);
    int registerUpdateBoardHook(UpdateBoardHook updateBoard);
    int registerBoardKeyPressHook(BoardKeyPressHook boardKeyPress);
    int registerShouldAllowSelectionsHook(ShouldAllowSelectionsHooks shouldAllowSelections);
    int registerWindowInputHook(WindowInputHook windowInput);

    void removePreInitHook(int index);
    void removePostInitHook(int index);
    void removeUpdateBoardHook(int index);
    void removeBoardKeyPressHook(int index);
    void removeShouldAllowSelectionsHook(int index);
    void removeWindowInputHook(int index);

    void callPreInitHooks(Sexy::WinTwistApp* app);
    void callPostInitHooks(Sexy::WinTwistApp* app);
    void callUpdateBoardHooks();
    void callBoardKeyPressHooks(int key);
    bool callShouldAllowSelectionsHooks();
    void callWindowInputHooks(Sexy::WinTwistApp* app, int input);

private:
    std::map<int, PreInitHook> mPreInitHooks;
    int mPreInitHooksCount;

    std::map<int, PostInitHook> mPostInitHooks;
    int mPostInitHooksCount;

    std::map<int, UpdateBoardHook> mUpdateBoardHooks;
    int mUpdateBoardHooksCount;

    std::map<int, BoardKeyPressHook> mBoardKeyPressHooks;
    int mBoardKeyPressHooksCount;

    std::map<int, ShouldAllowSelectionsHooks> mShouldAllowSelectionsHooks;
    int mShouldAllowSelectionsHooksCount;

    std::map<int, WindowInputHook> mWindowInputHooks;
    int mWindowInputHooksCount;
};

extern Hooks gHooks;
