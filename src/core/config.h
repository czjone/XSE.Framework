#ifndef XSE_CONFIG_H
#define XSE_CONFIG_H 1

// --------------------------------------------
//set platform
// --------------------------------------------

#define XSE_PLATFORM_UNKNOW     0
#define XSE_PLATFORM_MACOS      1
#define XSE_PLATFORM_ANDROID    2
#define XSE_PLATFORM_WIN        3
#define XSE_PLATFORM_LINUX      4

#define XSE_PLATFORM_TARGET XSE_PLATFORM_UNKNOW

#ifndef APPLE_IOS
#   undef XSE_PLATFORM_TARGET
#   define XSE_PLATFORM_TARGET XSE_PLATFORM_MACOS
#endif

#ifndef ANDROID
#   undef XSE_PLATFORM_TARGET
#   define XSE_PLATFORM_TARGET XSE_PLATFORM_ANDROID
#endif

#ifndef WIN
#   undef XSE_PLATFORM_TARGET
#   define XSE_PLATFORM_TARGET XSE_PLATFORM_WIN
#endif

#ifndef LINUX
#   undef XSE_PLATFORM_TARGET
#   define XSE_PLATFORM_TARGET XSE_PLATFORM_LINUX
#endif

// --------------------------------------------
//set libs
// --------------------------------------------
#define NSROOT XSE

#endif