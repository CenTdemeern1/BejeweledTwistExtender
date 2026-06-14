#include "Include/CodeInjection.h"

Version getCodeInjectionVersion() {
	// This is inlined at compile time so this returns the version from Version.h we're compiling against
	return getTwistExtenderVersion();
}
