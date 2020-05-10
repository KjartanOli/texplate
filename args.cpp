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

#include <json/json.h>
#include <json/value.h>

#include "config.hpp"
#include "args.hpp"

std::map<std::string_view, argumentValues> argumentMap
{
	{"-a", AUTHOR},
	{"--author", AUTHOR},
	{"-d", DATE},
	{"--date", DATE},
	{"-t", TITLE},
	{"--title", TITLE},
	{"-b", BIBSOURCE},
	{"--bibsource", BIBSOURCE},
	{"-h", HELP},
	{"--help", HELP},
	{"-e", ENCODING},
	{"--encoding", ENCODING},
	{"-l", LANGUAGE},
	{"--language", LANGUAGE},
	{"-u", USEPACKAGE},
	{"--usepackage", USEPACKAGE},
	{"-V", VERSION},
	{"--version", VERSION}
};


// set the members of the arguments struct appropriately to command line arguments
#include <iostream>
void parse_args(arguments& args, const Json::Value& config, int argc, char* argv[])
{
	for (auto& package : config["packages"])
	{
		args.packages.push_back(package.asString());
	}
	for (int i{1}; i < argc; ++i)
	{
		std::string_view arg{argv[i]};
		switch(argumentMap[arg])
		{
			case AUTHOR:
				// assume that if the next element in argv starts with a '-' assume it is a command
				args.author = (argv[i + 1][0] == '-' || i + 1 == argc - 2 ? config["author"].asString() : argv[++i]);
				break;
			case TITLE:
				args.title = (argv[i + 1][0] == '-' || i + 1 == argc - 2 ? "" : argv[++i]);
				break;
			case DATE:
				// allow for empty date command
				args.date = (argv[i + 1][0] == '-' || i + 1 == argc - 2 ? "" : argv[++i]);
				break;
			case USEPACKAGE:
				args.packages.push_back(argv[++i]);
				break;
			case HELP:
				args.help = true;
				break;
			case VERSION:
				args.version = true;
				break;
			case ENCODING:
				args.encoding = (argv[i + 1][0] == '-' || i + 1 == argc - 2 ? config["encoding"].asString() : argv[++i]);
				break;
			case LANGUAGE:
				args.language = (argv[i + 1][0] == '-' || i + 1 == argc - 2 ? config["language"].asString() : argv[++i]);
				break;
			case BIBSOURCE:
				args.bibsources.push_back(argv[++i]);

				// add \usepackage{biblatex} if no biblatex package is used
				if (has_bibpackage(args.packages))
				{
					args.packages.push_back("biblatex");
				}
				break;
			case NOTOPTION:
				if (i == argc - 2)
				{
					args.fileName = argv[i++];
					args.docClass = argv[i++];
				}
				else
				{
					args.unknownOption = arg;
				}
				break;
		}
	}
}

// check if the packages list contains some biblatex package
bool has_bibpackage(const std::vector<std::string>& packages)
{
	for (const std::string& package : packages)
	{
		if (package.find("biblatex"))
		{
			return true;
		}
	}
	return false;
}
