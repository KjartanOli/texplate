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

#ifndef ARGS_H
	#define ARGS_H

	#include <string>
	#include <vector>
	#include <map>

	struct arguments
	{
		std::string author;
		std::string title;
		std::string date;
		std::string fileName;
		std::string docClass;
		std::string encoding;
		std::string language;
		std::string unknownOption;
		std::vector<std::string> packages;
		std::vector<std::string> bibsources;
		bool help;
		bool version;
	};

	enum argumentValues
	{
		NOTOPTION,
		AUTHOR,
		DATE,
		BIBSOURCE,
		HELP,
		TITLE,
		ENCODING,
		LANGUAGE,
		USEPACKAGE,
		VERSION,
	};

	arguments parse_args(int argc, char* argv[]);
	bool has_bibpackage(const std::vector<std::string>& packages);
#endif
