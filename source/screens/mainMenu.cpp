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

#include "config.hpp"
#include "credits.hpp"
#include "gameScreen.hpp"
#include "mainMenu.hpp"
#include "uiSettings.hpp"

extern std::unique_ptr<Config> config;
extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, config->textColor(), "3DVier - " + Lang::get("MAINMENU"));
	GFX::DrawBottom();
	for (int i = 0; i < 4; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, config->buttonColor());
		if (Selection == i) {
			GFX::DrawButtonSelector(mainButtons[i].x, mainButtons[i].y);
		}
	}

	Gui::DrawStringCentered(-80, mainButtons[0].y+12, 0.6f, config->textColor(), Lang::get("NEW_GAME"), 130);
	Gui::DrawStringCentered(80, mainButtons[1].y+12, 0.6f, config->textColor(), Lang::get("UI_SETTINGS"), 130);
	Gui::DrawStringCentered(-80, mainButtons[2].y+12, 0.6f, config->textColor(), Lang::get("CREDITS"), 130);
	Gui::DrawStringCentered(80, mainButtons[3].y+12, 0.6f, config->textColor(), "???", 130);
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			Gui::setScreen(std::make_unique<GameScreen>());
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<UISettings>());
		} else if (touching(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>());
		} else if (touching(touch, mainButtons[3])) {
			// ?
		}
	}

	if(hDown & KEY_UP) {
		if(Selection > 1)	Selection -= 2;
	} else if(hDown & KEY_DOWN) {
		if(Selection < 3 && Selection != 2 && Selection != 3)	Selection += 2;
	} else if (hDown & KEY_LEFT) {
		if (Selection%2) Selection--;
	} else if (hDown & KEY_RIGHT) {
		if (!(Selection%2)) Selection++;
	}

	if (hDown & KEY_A) {
		if (Selection == 0) {
			Gui::setScreen(std::make_unique<GameScreen>());
		} else if (Selection == 1) {
			Gui::setScreen(std::make_unique<UISettings>());
		} else if (Selection == 2) {
			Gui::setScreen(std::make_unique<Credits>());
		} else if (Selection == 3) {
			// ?
		}
	}


	if (hDown & KEY_START) {
		exiting = true;
	}
}