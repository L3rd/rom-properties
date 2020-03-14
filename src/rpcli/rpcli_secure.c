/***************************************************************************
 * ROM Properties Page shell extension. (rpcli)                            *
 * rpcli_secure.c: Security options for rpcli.                             *
 *                                                                         *
 * Copyright (c) 2016-2020 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "stdafx.h"
#include "rpcli_secure.h"
#include "librpsecure/os-secure.h"

/**
 * Enable security options.
 * @return 0 on success; negative POSIX error code on error.
 */
int rpcli_do_security_options(void)
{
	// Set OS-specific security options.
	rp_secure_param_t param;
#if defined(_WIN32)
	param.bHighSec = FALSE;
#elif defined(HAVE_SECCOMP)
	static const int syscall_wl[] = {
		// Syscalls used by rp-download.
		// TODO: Add more syscalls.
		// FIXME: glibc-2.31 uses 64-bit time syscalls that may not be
		// defined in earlier versions, including Ubuntu 14.04.
		SCMP_SYS(close),
		SCMP_SYS(dup),		// gzdopen()
		SCMP_SYS(fstat), SCMP_SYS(fstat64),
		SCMP_SYS(fstatat64),	// Ubuntu 19.10 (32-bit)
		SCMP_SYS(ftruncate),	// LibRpBase::RpFile::truncate() [from LibRpBase::RpPngWriterPrivate::init()]
		SCMP_SYS(ftruncate64),
		SCMP_SYS(futex),
		SCMP_SYS(gettimeofday),	// 32-bit only?
		SCMP_SYS(ioctl),	// for devices; also afl-fuzz
		SCMP_SYS(lseek), SCMP_SYS(_llseek),
		SCMP_SYS(lstat), SCMP_SYS(lstat64),	// LibRpBase::FileSystem::is_symlink(), resolve_symlink()
		SCMP_SYS(mmap), SCMP_SYS(mmap2),
		SCMP_SYS(mprotect),	// dlopen()
		SCMP_SYS(munmap),
		SCMP_SYS(open),		// Ubuntu 16.04
		SCMP_SYS(openat),	// glibc-2.31
#ifdef __NR_openat2
		SCMP_SYS(openat2),	// Linux 5.6
#endif /* __NR_openat2 */
		SCMP_SYS(readlink),	// realpath() [LibRpBase::FileSystem::resolve_symlink()]

		// KeyManager (keys.conf)
		SCMP_SYS(access),	// LibUnixCommon::isWritableDirectory()
		SCMP_SYS(stat), SCMP_SYS(stat64),	// LibUnixCommon::isWritableDirectory()

#ifdef __NR_statx
		SCMP_SYS(getcwd),	// called by glibc's statx()
		SCMP_SYS(statx),
#endif /* __NR_statx */

		// glibc ncsd
		// TODO: Restrict connect() to AF_UNIX.
		SCMP_SYS(connect), SCMP_SYS(recvmsg), SCMP_SYS(sendto),

		// NOTE: The following syscalls are only made if either access() or stat() can't be run.
		// TODO: Can this happen in other situations?
		//SCMP_SYS(getuid),
		//SCMP_SYS(socket),	// ???
		//SCMP_SYS(socketcall),	// FIXME: Enhanced filtering? [cURL+GnuTLS only?]

		-1	// End of whitelist
	};
	param.syscall_wl = syscall_wl;
#elif defined(HAVE_PLEDGE)
	// Promises:
	// - stdio: General stdio functionality.
	// - rpath: Read from ~/.config/rom-properties/ and ~/.cache/rom-properties/
	// - wpath: Write to ~/.cache/rom-properties/
	// - cpath: Create ~/.cache/rom-properties/ if it doesn't exist.
	// - getpw: Get user's home directory if HOME is empty.
	param.promises = "stdio rpath wpath cpath getpw";
#elif defined(HAVE_TAME)
	param.tame_flags = TAME_STDIO | TAME_RPATH | TAME_WPATH | TAME_CPATH | TAME_GETPW;
#else
	param.dummy = 0;
#endif
	return rp_secure_enable(param);
}