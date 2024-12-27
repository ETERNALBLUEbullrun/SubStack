/* (C) 2024 Swudu Susuwu, dual licenses: choose [GPLv2](./LICENSE_GPLv2) or [Apache 2](./LICENSE), allows all uses. */
#pragma once
#ifndef INCLUDES_cxx_ClassFS_hxx
#define INCLUDES_cxx_ClassFS_hxx
#include "Macros.hxx" /* SUSUWU_NOEXCEPT SUSUWU_UNIT_TESTS */
#include SUSUWU_IF_CPLUSPLUS(<cstdio>, <stdio.h>) /* FILE */
#include <string> /* std::string */
/* Abstractions to do with filesystems (such as `procfs`) */
namespace Susuwu {
typedef std::string FilePath; /* TODO: `std::char_traits<unsigned char>`, `std::basic_string<unsigned char>("string literal")` */
typedef FilePath FileBytecode; /* Uses `std::string` for bytecode (versus `std::vector`) because:
 * "If you are going to use the data in a string like fashon then you should opt for std::string as using a std::vector may confuse subsequent maintainers. If on the other hand most of the data manipulation looks like plain maths or vector like then a std::vector is more appropriate." -- https://stackoverflow.com/a/1556294/24473928
*/
typedef FilePath FileHash; /* TODO: `std::unordered_set<std::basic_string<unsigned char>>` */

/* Usage: for Linux (or Windows,) if you don't trust `argv[0]`, replace it with `classFSGetOwnPath()`.
 * Error values: `return FilePath();` */
const FilePath classFSGetOwnPath() /* TODO: SUSUWU_NOEXCEPT(std::is_nothrow_constructible<FilePath>::value) */;
const FILE *classFSFopenOwnPath() /* TODO: SUSUWU_NOEXCEPT(std::is_nothrow_invocable<classFSGetFilePath()>::value) */;

#if SUSUWU_UNIT_TESTS
/* @throw std::runtime_error */
const bool classFSTests();
const bool classFSTestsNoexcept() SUSUWU_NOEXCEPT;
#endif /* SUSUWU_UNIT_TESTS */

}; /* namespace Susuwu */
#endif /* ndef INCLUDES_cxx_ClassFS_hxx */

