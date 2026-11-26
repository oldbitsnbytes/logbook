////////////////////////////////////////////////////////////////////////////////////////////
//   Copyright (C) ...,2026,... by Serge Lussier
//   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com
//   ----------------------------------------------------------------------------------
//   Unless otherwise specified, all Codes and files in this project is written
//   by the author and owned by the author (Serge Lussier), unless otherwise specified.
//   ----------------------------------------------------------------------------------
//   Copyrights from authors other than Serge Lussier also apply here.
//   Open source FREE licences also apply to the code from the author (Serge Lussier)
//   ----------------------------------------------------------------------------------
//   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.
//   ----------------------------------------------------------------------------------
//   NOTE : All source code that I am the only author, I reserve for myself, the rights to
//   make it to restricted private license.
////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------
/*## Trademarks & Credits
* "Linux" is a registered trademark of Linus Torvalds. This project is an independent, open-source framework and is not officially endorsed
* by or affiliated with Linus Torvalds or the Linux Foundation.
* The "tux" penguin logo (if used) was created by Larry Ewing using The GIMP.
*/
#pragma once


#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
//#error "Windows detected - msvc env and Windows console terminal not supported...yet..."
pragma warning(disable : 4996)
//#   pragma warning(disable : 4005)
//#   pragma warning(disable : 4267)
//#   pragma warning(disable : 4251)
//class __declspec(dllimport) std::thread;
#   define _CRT_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS
#   define NOMINMAX
#   if defined(LOGBOOK_EXPORT)
#       define LOGBOOK_LIB __declspec(dllexport)
#   else
#       define LOGBOOK_LIB __declspec(dllimport)
#   endif
#else
	#include <unistd.h>
#endif



// ------------ Mandatory includes ------------
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>
#include <string>

// ------------ PRSEUDO NAME ------------
#ifndef CLASSNAME_START
#define CLASSNAME_START(CLASS) \
    public: virtual const char* class_name() const noexcept { return #CLASS; }\
    private:
#endif




#ifndef CLASSNAME_DERIVED
# define CLASSNAME_DERIVED(CLASS) \
    public: const char*  class_name() const noexcept override { return #CLASS; }\
    private:
#endif



//--  Stand alone non-virtual class names macros : --

#ifndef CLASSNAME
# define CLASSNAME(CLASS) \
public: const char*  class_name() const noexcept { return #CLASS; }\
private:

#endif



//----------------------------------------------------------------------------

namespace Integers
{
using Byte  = uint8_t;
using I8    = int8_t;
using U8    = uint8_t;
using I16   = int16_t;
using U16   = uint16_t;
using I32   = int32_t;
using Int   = int32_t;
using U32   = uint32_t;
using UInt  = uint32_t;
using I64   = int64_t;
using U64   = uint64_t;
using UReg  = uint64_t;
using byte  = uint8_t;
using i8    = int8_t;
using u8    = uint8_t;
using i16   = int16_t;
using u16   = uint16_t;
using i32   = int32_t;
using u32   = uint32_t;
using i64   = int64_t;
using u64   = uint64_t;
using ureg  = uint64_t;
using UReg  = uint64_t;
//using Reg   = int64_t;
using f32   = float;
using f64   = double;
using f128  = long double;
using F32   = float;
using F64   = double;
using F128  = long double;

}

//------------------------------------------------------------------------------

