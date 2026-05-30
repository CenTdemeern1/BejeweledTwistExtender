#pragma once

#include "Extender/FuncInterceptor.h"
#include "Hooks.h"

typedef bool (__cdecl* InitModFn)(CodeInjection::FuncInterceptor*, Hooks*);
