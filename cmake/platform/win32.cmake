# Win32-specific CFLAGS/CXXFLAGS.

# Basic platform flags:
# - Enable strict type checking in the Windows headers.
# - Define WIN32_LEAN_AND_MEAN to reduce the number of Windows headers included.
# - Define NOMINMAX to disable the MIN() and MAX() macros.
ADD_DEFINITIONS(-DSTRICT -DWIN32_LEAN_AND_MEAN -DNOMINMAX)

# NOTE: This program only supports Unicode on Windows.
# No support for ANSI Windows, i.e. Win9x.
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

# Minimum Windows version for the SDK is Windows Vista.
ADD_DEFINITIONS(-DWINVER=0x0600 -D_WIN32_WINNT=0x0600 -D_WIN32_IE=0x0600)

# Enable secure template overloads for C++.
# References:
# - MinGW's _mingw_secapi.h
# - http://msdn.microsoft.com/en-us/library/ms175759%28v=VS.100%29.aspx
ADD_DEFINITIONS(-D_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES=1)
ADD_DEFINITIONS(-D_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY=1)
ADD_DEFINITIONS(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1)
ADD_DEFINITIONS(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT=1)
ADD_DEFINITIONS(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY=1)

# Determine the processorArchitecture for the manifest files.
IF(CPU_i386)
	SET(WIN32_MANIFEST_PROCESSOR_ARCHITECTURE "x86")
ELSEIF(CPU_amd64)
	SET(WIN32_MANIFEST_PROCESSOR_ARCHITECTURE "amd64")
ELSEIF(CPU_ia64)
	SET(WIN32_MANIFEST_PROCESSOR_ARCHITECTURE "ia64")
ELSEIF(CPU_arm)
	SET(WIN32_MANIFEST_PROCESSOR_ARCHITECTURE "arm")
ELSEIF(CPU_arm64)
	SET(WIN32_MANIFEST_PROCESSOR_ARCHITECTURE "arm64")
ELSE()
	MESSAGE(FATAL_ERROR "Unsupported CPU architecture, please fix!")
ENDIF()

# Compiler-specific Win32 flags.
IF(MSVC)
	INCLUDE(cmake/platform/win32-msvc.cmake)
ELSE(MSVC)
	INCLUDE(cmake/platform/win32-gcc.cmake)
ENDIF(MSVC)
