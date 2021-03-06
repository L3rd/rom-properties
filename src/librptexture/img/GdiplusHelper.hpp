/***************************************************************************
 * ROM Properties Page shell extension. (librpbase)                        *
 * GdiplusHelper.hpp: GDI+ helper class. (Win32)                           *
 *                                                                         *
 * Copyright (c) 2016 by David Korth.                                      *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_LIBRPBASE_IMG_GDIPLUSHELPER_HPP__
#define __ROMPROPERTIES_LIBRPBASE_IMG_GDIPLUSHELPER_HPP__

#ifndef _WIN32
#error GdiplusHelper is Win32 only.
#endif

#include "common.h"
#include "libwin32common/RpWin32_sdk.h"

class GdiplusHelper
{
	private:
		// GdiplusHelper is a static class.
		GdiplusHelper();
		~GdiplusHelper();
		RP_DISABLE_COPY(GdiplusHelper)

	public:
		/**
		 * Initialize GDI+.
		 * @return GDI+ token, or 0 on failure.
		 */
		static ULONG_PTR InitGDIPlus(void);

		/**
		 * Shut down GDI+.
		 * @param gdipToken GDI+ token.
		 */
		static void ShutdownGDIPlus(ULONG_PTR gdipToken);
};

#endif /* __ROMPROPERTIES_LIBRPBASE_IMG_GDIPLUSHELPER_HPP__ */
