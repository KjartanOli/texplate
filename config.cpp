/*
 * Copyright (C) 2020  Ágústsson, Kjartan Óli <kjartanoli@protonmail.com>
 * Author: Ágústsson, Kjartan Óli <kjartanoli@protonmail.com>
 *
 * This file is a part of Texplate
 * Texplate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <json/value.h>
#include <string_view>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <json/json.h>

#include "config.hpp"

std::string get_config_file()
{
	#if defined(unix) || defined(__unix__) || defined(__unix)
		char* home{getenv("HOME")};
		if (home)
		{
			return std::string{strcat(home, "/.config/texplate.conf")};
		}
		return home;
	#elif defined(_WIN32)
		char* homeDrive{getenv("HOMEDRIVE")};
		char* homePath{getenv("HOMEPATH")};
		if (homeDrive && homePath)
		{
			return std::string_view{strcat(homeDrive, homePath)};
		}
	#endif
}

void read_config(Json::Value& config)
{
	std::string path{get_config_file()};
	std::ifstream file{path};
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	if (!parseFromStream(builder, file, &config, &errs)) {
		std::cout << errs << std::endl;
	}
}
