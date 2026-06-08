#pragma once

#include "Extender/FuncInterceptor.h"
#include "HookFunctions.h"

typedef bool (__cdecl* InitModFn)(CodeInjection::FuncInterceptor*, HookFunctions*);
