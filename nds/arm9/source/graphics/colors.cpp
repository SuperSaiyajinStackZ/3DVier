/*
*   This file is part of DSVier
*   Copyright (C) 2020 Universal-Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "colors.hpp"
#include "graphics.hpp"
#include "tonccpy.h"

#include <nds.h>

const u16 defaultPalette[] = {
	0x0000, 0xFBDE, 0xE739, 0xCA52, 0xBDEF, 0x98C6, 0x94A5, 0x8842, 0x8000, // Grays.
	0xECE7, 0xEE73, 0xD407, 0xBC00, 0x8260, 0x8320, 0x83E0, // Colors.
	0x0000, 0xFBDE, 0xBDEF, 0xA108, // WHITE_TEXT.
	0x0000, 0x8C63, 0xA94A, 0xCA52, // GRAY_TEXT.
	0x0000, 0x8000, 0xB5AD, 0xC210, // BLACK_TEXT.
	0x0000, 0xF800, 0xBC00, 0xE800, // BLUE_TEXT.
};

void Colors::load(void) {
	u16 palette[sizeof(defaultPalette)];
	tonccpy(palette, defaultPalette, sizeof(palette));

	tonccpy(BG_PALETTE, palette, sizeof(palette));
	tonccpy(BG_PALETTE_SUB, palette, sizeof(palette));
}