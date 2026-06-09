#include "Hooks.h"

#define GENHOOKFN(type, name, args, argNames) \
	type name args { return gHooks.name argNames; }

namespace HookFunctionDefinitions {
	GENHOOKFN(int, registerPreInitHook, (PreInitHook preInit), (preInit));
	GENHOOKFN(int, registerPostInitHook, (PostInitHook postInit), (postInit));
	GENHOOKFN(int, registerUpdateBoardHook, (UpdateBoardHook updateBoard), (updateBoard));
	GENHOOKFN(int, registerBoardKeyPressHook, (BoardKeyPressHook boardKeyPress), (boardKeyPress));
	GENHOOKFN(int, registerShouldAllowSelectionsHook, (ShouldAllowSelectionsHooks shouldAllowSelections), (shouldAllowSelections));
	GENHOOKFN(int, registerWindowInputHook, (WindowInputHook windowInput), (windowInput));

	GENHOOKFN(void, removePreInitHook, (int index), (index));
	GENHOOKFN(void, removePostInitHook, (int index), (index));
	GENHOOKFN(void, removeUpdateBoardHook, (int index), (index));
	GENHOOKFN(void, removeBoardKeyPressHook, (int index), (index));
	GENHOOKFN(void, removeShouldAllowSelectionsHook, (int index), (index));
	GENHOOKFN(void, removeWindowInputHook, (int index), (index));

	GENHOOKFN(void, callPreInitHooks, (Sexy::WinTwistApp* app), (app));
	GENHOOKFN(void, callPostInitHooks, (Sexy::WinTwistApp* app), (app));
	GENHOOKFN(void, callUpdateBoardHooks, (TwistFunctions* game), (game));
	GENHOOKFN(void, callBoardKeyPressHooks, (TwistFunctions* game, int key), (game, key));
	GENHOOKFN(bool, callShouldAllowSelectionsHooks, (TwistFunctions* game), (game));
	GENHOOKFN(void, callWindowInputHooks, (Sexy::WinTwistApp* app, int input), (app, input));
}
using namespace HookFunctionDefinitions;

HookFunctions gHookFunctions = {
	&registerPreInitHook,
	&registerPostInitHook,
	&registerUpdateBoardHook,
	&registerBoardKeyPressHook,
	&registerShouldAllowSelectionsHook,
	&registerWindowInputHook,

	&removePreInitHook,
	&removePostInitHook,
	&removeUpdateBoardHook,
	&removeBoardKeyPressHook,
	&removeShouldAllowSelectionsHook,
	&removeWindowInputHook,

	&callPreInitHooks,
	&callPostInitHooks,
	&callUpdateBoardHooks,
	&callBoardKeyPressHooks,
	&callShouldAllowSelectionsHooks,
	&callWindowInputHooks,
};
