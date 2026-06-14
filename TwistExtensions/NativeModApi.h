#pragma once

#include "HookFunctions.h"
#include <Version.h>
#include <Extender/FuncInterceptor.h>

constexpr const char ISCOMPATIBLEFN_NAME[] = "isCompatibleWithVersion";
typedef bool(__cdecl* IsCompatibleFn)(Version*);

constexpr const char INITMODFN_NAME[] = "initMod";
typedef bool (__cdecl* InitModFn)(CodeInjection::FuncInterceptor*, HookFunctions*);
