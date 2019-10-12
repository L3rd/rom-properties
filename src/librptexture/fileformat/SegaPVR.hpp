/***************************************************************************
 * ROM Properties Page shell extension. (librptexture)                     *
 * SegaPVR.hpp: Sega PVR texture reader.                                   *
 *                                                                         *
 * Copyright (c) 2017-2019 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_LIBRPTEXTURE_FILEFORMAT_SEGAPVR_HPP__
#define __ROMPROPERTIES_LIBRPTEXTURE_FILEFORMAT_SEGAPVR_HPP__

#include "FileFormat.hpp"
#include <stdint.h>

namespace LibRpTexture {

FILEFORMAT_DECL_BEGIN(SegaPVR)

	public:
		/**
		 * ROM detection information.
		 * Used for isRomSupported() functions.
		 * TODO: Move to FileFormat.
		 */
		struct DetectInfo {
			struct {
				uint32_t addr;		// Start address in the ROM.
				uint32_t size;		// Length.
				const uint8_t *pData;	// Data.
			} header;		// ROM header.
			const char *ext;	// File extension, including leading '.'
			int64_t szFile;		// File size. (Required for certain types.)
		};

		static int isRomSupported_static(const DetectInfo *info);

FILEFORMAT_DECL_END()

}

#endif /* __ROMPROPERTIES_LIBRPTEXTURE_FILEFORMAT_SEGAPVR_HPP__ */