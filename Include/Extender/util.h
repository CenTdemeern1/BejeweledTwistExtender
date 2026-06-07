#ifndef __UTIL_H_
#define __UTIL_H_

#include <string>

#include "ImportExport.h"

#define NAKEDTYPE __declspec(naked) void
#define NAKEDDEF(name) \
    NAKEDTYPE name()

extern CODEINJECTION_EXPORT bool test_string_pointer(const char *testPointer, const char *testStr);

extern CODEINJECTION_EXPORT void inject_jmp(int address, void(*func));
extern CODEINJECTION_EXPORT void inject_nops(int address, int count);
extern CODEINJECTION_EXPORT void inject_byte(int address, int byte);


extern CODEINJECTION_EXPORT int random(int min, int max);

extern CODEINJECTION_EXPORT std::string lastError;
extern CODEINJECTION_EXPORT void setLastError(std::string error);

extern CODEINJECTION_EXPORT bool fileExists(std::string path);

#endif /* __UTIL_H_ */
