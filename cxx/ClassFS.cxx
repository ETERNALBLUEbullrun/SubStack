/* (C) 2024 Swudu Susuwu, dual licenses: choose [GPLv2](./LICENSE_GPLv2) or [Apache 2](./LICENSE), allows all uses. */
#ifndef INCLUDES_cxx_ClassFS_cxx
#define INCLUDES_cxx_ClassFS_cxx
#include "Macros.hxx" /* SUSUWU_IF_CPLUSPLUS SUSUWU_NOEXCEPT SUSUWU_NULLPTR SUSUWU_POSIX SUSUWU_UNIT_TESTS SUSUWU_WIN32 */
#include "ClassFS.hxx" /* FilePath */
#include "ClassSys.hxx" /* templateCatchAll */
//#include SUSUWU_IF_CPLUSPLUS(<cassert>, <assert.h>) /* assert */
#include SUSUWU_IF_CPLUSPLUS(<cerrno>, <errno.h>) /* errno */
#include SUSUWU_IF_CPLUSPLUS(<cstdio>, <stdio.h>) /* FILE fopen */
#ifdef __linux__
#	include <linux/limits.h> /* PATH_MAX */
#endif /* def __linux__ */
#include <string> /* std::to_string */
#ifdef __linux__ /* `clang-tidy` wants ordered `#include`s */
#	include <unistd.h> /* readlink */
#endif /* def __linux__ */
//#include <stdexcept> /* std::runtime_error */
#ifdef SUSUWU_WIN32
# include <windows.h> /* GetModuleFileName GetModuleHandle HMODULE */
# undef ERROR /* undo `windows.h`'s `#define ERROR 0` */
#endif /* def SUSUWU_WIN32 */
namespace Susuwu {
const FILE *classFSFopenOwnPath() {
	return fopen(classFSGetOwnPath().c_str(), "r");
}
const FilePath classFSGetOwnPath() {
#ifdef __linux__
	char path[PATH_MAX]; /* NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays) */
	const ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
	if (len == -1) {
		SUSUWU_ERROR("classFSGetOwnPath(): { if(-1 == readlink(\"/proc/self/exe\", path, sizeof(path) - 1)) { errno == " + std::to_string(errno) + "; } }");
		return FilePath(); /* return EXIT_FAILURE; */
	}
	path[len] = '\0'; /* NOLINT(cppcoreguidelines-pro-bounds-constant-array-index) */
//	`return "/proc/self/exe"; /* if _Termux_, causes `PortableExecutableBytecode(classFSGetOwnPath())` to act as `PortableExecutableBytecode("/apex/com.android.runtime/bin/linker64")` */
	return FilePath(path); /* causes `PortableExecutableBytecode(classFSGetOwnPath())` to act as `PortableExecutableBytecode(argv[0])` */
#elif defined SUSUWU_WIN32
	HMODULE hModule = GetModuleHandle(SUSUWU_NULLPTR);
	if(hModule) {
		char ownPathStr[MAX_PATH];
		GetModuleFileName(hModule, ownPathStr, sizeof(ownPathStr));
		return FilePath(ownPathStr);
	} else {
		SUSUWU_ERROR("classFSGetOwnPath(): { if(!GetModuleHandle(NULL)) {/* this shouldn't happen */} }");
		return FilePath(); /* return EXIT_FAILURE; */
	}
#else /* def SUSUWU_WIN32 else */
	if(SUSUWU_NULLPTR == classFSArgs) {
		SUSUWU_ERROR("classFSGetOwnPath(): { if(SUSUWU_NULLPTR == classFSArgs) {/* `classFSInit()` was not used? */} }");
		return FilePath(); /* return EXIT_FAILURE; */
	} else if(SUSUWU_NULLPTR == classFSArgs[0]) { /* NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
		SUSUWU_ERROR("classFSGetOwnPath(): { if(SUSUWU_NULLPTR == classFSArgs[0]) {/* `classFSInit()` was not used? */} }");
		return FilePath(); /* return EXIT_FAILURE; */
	}
	return FilePath(classFSArgs[0]); /* NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
#endif /* def SUSUWU_WIN32 else */
}

#if SUSUWU_UNIT_TESTS
namespace { /* [misc-use-anonymous-namespace] */
}; /* namespace */
const bool classFSTests() {
	bool retval = true; /* TODO: choose all errors throw exceptions, or choose all errors return error values. Most of the other unit tests use exceptions, but `echo` is the best test for `execves`/`execvex`. */
	return retval;
}
const bool classFSTestsNoexcept() SUSUWU_NOEXCEPT { return templateCatchAll(classFSTests, "classFSTests()"); }
#endif /* SUSUWU_UNIT_TESTS */

}; /* namespace Susuwu */
#endif /* ndef INCLUDES_cxx_ClassFS_cxx */

