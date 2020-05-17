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

#include "common.hpp"
#include "config.hpp"
#include "json.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <string>
#include <unistd.h>

// In case it doesn't exist.
void Config::initialize() {
	// Create through fopen "Write".
	FILE *file = fopen("sdmc:/3ds/3DVier/Settings.json", "w");

	// Set default values.
	this->setInt("Player1_Chip", C2D_Color32(255, 255, 255, 255));
	this->setInt("Player2_Chip", C2D_Color32(0, 0, 0, 255));
	this->setInt("Raster_Color", C2D_Color32(60, 60, 60, 255));
	this->setBool("Darken_Screen", true);
	this->setInt("Bar_Color", C2D_Color32(60, 60, 220, 255));
	this->setInt("Text_Color", C2D_Color32(255, 255, 255, 255));
	this->setInt("BG_Color", C2D_Color32(160, 160, 220, 255));
	this->setInt("Button_Color", C2D_Color32(60, 0, 170, 255));
	this->setInt("Selector_Color", C2D_Color32(0, 0, 255, 255));
	this->setInt("Language", 1);

	// Write to file.
	fwrite(this->json.dump(1, '\t').c_str(), 1, this->json.dump(1, '\t').size(), file);
	fclose(file); // Now we have the file and can properly access it.
}

Config::Config() {
	if (access("sdmc:/3ds/3DVier/Settings.json", F_OK) != 0 ) {
		this->initialize();
	}
	FILE* file = fopen("sdmc:/3ds/3DVier/Settings.json", "r");
	this->json = nlohmann::json::parse(file, nullptr, false);
	fclose(file);

	// Here we get the initial colors.

	if (!this->json.contains("Player1_Chip")) {
		this->p1Chip(C2D_Color32(200, 0, 0, 255));
	} else {
		this->p1Chip(this->getInt("Player1_Chip"));
	}

	if (!this->json.contains("Player2_Chip")) {
		this->p2Chip(C2D_Color32(0, 200, 0, 255));
	} else {
		this->p2Chip(this->getInt("Player2_Chip"));
	}

	if (!this->json.contains("Raster_Color")) {
		this->raster(C2D_Color32(200, 200, 0, 255));
	} else {
		this->raster(this->getInt("Raster_Color"));
	}

	if (!this->json.contains("Darken_Screen")) {
		this->darkenScreen(C2D_Color32(200, 0, 0, 255));
	} else {
		this->darkenScreen(this->getBool("Darken_Screen"));
	}

	if (!this->json.contains("Bar_Color")) {
		this->barColor(C2D_Color32(220, 60, 0, 255));
	} else {
		this->barColor(this->getInt("Bar_Color"));
	}

	if (!this->json.contains("BG_Color")) {
		this->bgColor(C2D_Color32(220, 160, 0, 255));
	} else {
		this->bgColor(this->getInt("BG_Color"));
	}

	if (!this->json.contains("Text_Color")) {
		this->textColor(C2D_Color32(255, 255, 255, 255));
	} else {
		this->textColor(this->getInt("Text_Color"));
	}

	if (!this->json.contains("Button_Color")) {
		this->buttonColor(C2D_Color32(170, 60, 0, 255));
	} else {
		this->buttonColor(this->getInt("Button_Color"));
	}

	if (!this->json.contains("Selector_Color")) {
		this->selectorColor(C2D_Color32(200, 0, 0, 255));
	} else {
		this->selectorColor(this->getInt("Selector_Color"));
	}

	if (!this->json.contains("Language")) {
		this->language(1);
	} else {
		this->language(this->getInt("Language"));
	}

	this->changesMade = false; // No changes made yet.
}

// Write to config if changesMade.
void Config::save() {
	if (this->changesMade) {
		FILE *file = fopen("sdmc:/3ds/3DVier/Settings.json", "w");
		// Set values.
		this->setInt("Player1_Chip", this->p1Chip());
		this->setInt("Player2_Chip", this->p2Chip());
		this->setInt("Raster_Color", this->raster());
		this->setBool("Darken_Screen", this->darkenScreen());
		this->setInt("Bar_Color", this->barColor());
		this->setInt("Text_Color", this->textColor());
		this->setInt("BG_Color", this->bgColor());
		this->setInt("Button_Color", this->buttonColor());
		this->setInt("Selector_Color", this->selectorColor());
		this->setInt("Language", this->language());
		// Write changes to file.
		fwrite(this->json.dump(1, '\t').c_str(), 1, this->json.dump(1, '\t').size(), file);
		fclose(file);
	}
}

// Helper functions.
bool Config::getBool(const std::string &key) {
	if(!this->json.contains(key)) {
		return false;
	}
	return this->json.at(key).get_ref<const bool&>();
}
void Config::setBool(const std::string &key, bool v) {
	this->json[key] = v;
}

int Config::getInt(const std::string &key) {
	if(!this->json.contains(key)) {
		return 0;
	}
	return this->json.at(key).get_ref<const int64_t&>();
}
void Config::setInt(const std::string &key, int v) {
	this->json[key] = v;
}

std::string Config::getString(const std::string &key) {
	if(!this->json.contains(key)) {
		return "";
	}
	return this->json.at(key).get_ref<const std::string&>();
}
void Config::setString(const std::string &key, const std::string &v) {
	this->json[key] = v;
}