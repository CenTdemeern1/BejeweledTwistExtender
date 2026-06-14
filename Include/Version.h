#ifndef __VERSION_H_
#define __VERSION_H_

typedef struct {
    // Major version. Different major versions are incompatible, incremented on a backward incompatible API change
    unsigned int major,
    // Minor version. Minor versions are incremented when adding new backward compatible features
    minor,
    // Patch version. Patch versions are incremented when fixing bugs in a backward compatible way
    patch,
    // Prerelease version. Prereleases are used for development builds (pre-alpha, alphas, betas, et cetera).
    // Zero means "not a prerelease". Increment when sharing a development build
    // This number is not used for version requirement checking, see prereleaseCompatible
    prerelease,
    // The oldest prerelease of this version that this version is backward compatible with.
    // This number is used for checking compatibility between prereleases.
    // This number should be equivalent for compatible prereleases of the same version.
    prereleaseCompatible;
} Version;

#ifndef NO_VERSION_IMPL

#ifndef __cplusplus
#include <stdbool.h>
#endif // __cplusplus

// Checks if the version "version" is compatible with the version "requirement".
// Compatible means equivalent, or newer but with a compatible API.
// This roughly follows semver logic.
inline bool meetsVersionRequirement(Version* version, Version* requirement) {
    return version->major == requirement->major // Major version needs to be equivalent, otherwise there are breaking changes
        && version->minor >= requirement->minor // Minor version needs to be equal or greater
        && (
            version->minor != requirement->minor // Unless the minor version is different...
            || version->patch >= requirement->patch // The patch version also needs to be equal or greater
        )
		&& (
            version->minor != requirement->minor // Unless the minor version is different...
            || version->patch != requirement->patch // or the patch version is different...
            || version->prereleaseCompatible == requirement->prereleaseCompatible // They need to have the same prerelease compatibility level
        );
}

// Gets the version of BejeweledTwistExtender you are compiling against.
// This is not always the same as the version that loaded your mod!
// You should use this to check if the version that loaded your mod is compatible with the one you compiled against.
inline Version getTwistExtenderVersion(void) {
    Version version = {
        /* major */ 2,
        /* minor */ 0,
        /* patch */ 0,
        /* prerelease */ 1,
        /* prereleaseCompatible */ 1,
    };
    return version;
}

#ifdef __cplusplus
inline bool operator==(const Version& lhs, const Version& rhs) {
    return lhs.major == rhs.major
        && lhs.minor == rhs.minor
        && lhs.patch == rhs.patch
        && lhs.prerelease == rhs.prerelease
        && lhs.prereleaseCompatible == rhs.prereleaseCompatible;
}
inline bool operator!=(const Version& lhs, const Version& rhs) { return !(lhs == rhs); }
#endif // __cplusplus

#endif // NO_VERSION_IMPL

#endif // __VERSION_H_
