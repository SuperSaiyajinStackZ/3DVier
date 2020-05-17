/*
*   This file is part of 3DVier
*   Copyright (C) 2020 SuperSaiyajinStackZ
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

#ifndef GFX_HPP
#define GFX_HPP

#include "chars.h"
#include "colorHelper.hpp"
#include "sprites.h"

namespace GFX
{
	// Basic GUI.
	void DrawTop(bool useBars = true);
	void DrawBottom(bool useBars = true);
	void DrawSprite(int index, int x, int y, float ScaleX = 1, float ScaleY = 1);
	// Selectors.
	void DrawButtonSelector(int x, int y, float ScaleX = 1, float ScaleY = 1, bool useSmall = false);
	void DrawSelectedChip(int x, int y, float ScaleX = 1, float ScaleY = 1);
	
	void DrawChar(int image, int x, int y, float ScaleX = 1, float ScaleY = 1);
	void DrawChip(int x, int y, float ScaleX = 1, float ScaleY = 1, int player = 1);
	void DrawRaster(int x, int y);
	void DrawPlayer(int x, int y, float ScaleX, float ScaleY, int player);
}

#endif