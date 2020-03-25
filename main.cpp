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

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "args.hpp"
#include "file.hpp"

void help(std::ostream& out = std::cout);
void help(const std::string& unknown);
void version();

// copyright information
static const std::string_view author{"Kjartan Óli Ágústsson"};
static const std::string_view year{"2020"};

// version information
static const short majorVersion{1};
static const short minorVersion{5};
static const short hotfix{0};

int main(int argc, char* argv[])
{
	arguments args{parse_args(argc, argv)};

	if (args.help)
	{
		help();
		return 0;
	}

	if (args.version)
	{
		version();
		return 0;
	}

	if (args.unknownOption != "")
	{
		help(args.unknownOption);
		return 2;
	}

	// exit with error if either fileName or docClass are not provided
	if (args.fileName == "" || args.docClass == "")
	{
		help(std::cerr);
		return 1;
	}

	write(args);

	return 0;
}

// print help
void help(std::ostream& out)
{
	static const std::string_view indent{"  "};

	out << "Usage: texplate [OPTIONS] FILENAME DOCUMENTCLASS\n"
	<< "Create a basic LaTex document FILENAME with class DOCUMENTCLASS\n"
	<< "Example: texplate -a Kjartan test article\n\n"
	<< "Options:\n"
	<< indent << "-a,\t--author=AUTHOR\t\tAdd a \\author{AUTHOR} command to the document\n"
	<< indent << "-b,\t--bibsource=SOURCE\tAdd a \\addbibresources{SOURCE} to the document\n"
	<< indent << "\t\t\t\tand if no biblatex package is used with the\n"
	<< indent << "\t\t\t\t-u option add \\usepackage{biblatex} as well\n"
	<< indent << "-d,\t--date=DATE\t\tAdd a \\date{DATE} command to the document\n"
	<< indent << "-h,\t--help\t\t\tPrint this help and exit\n"
	<< indent << "-l,\t--language=LANGUAGE\tLoad the babel package for LANGUAGE\n"
	<< indent << "-u,\t--usepackage=PACKAGE\tAdd a \\usepackage{PACKAGE} statement\n"
	<< indent << "-t,\t--title=TITLE\t\tAdd a \\title{TITLE} command to the document\n\n"
	<< "\nErrors:\n"
	<< indent << "1\tMissing FILENAME or DOCUMENTCLASS\n"
	<< indent << "2\tUnknown option\n"
	<< "\ntexplate " << majorVersion << '.' << minorVersion << '.' << hotfix
	<< " Copyright (C) " << year << ' ' << author
	<< "\nThis program comes with ABSOLUTELY NO WARRANTY.\n"
	<< "This is free software, and you are welcome to redistribute it\n";
}

// print unknown option message and print help
void help(const std::string& unknown)
{
	std::cerr << "Unknown option: " << unknown << '\n';
	help(std::cerr);
}

// print version information
void version()
{
	std::cout << "texplate " << majorVersion << '.' << minorVersion << '.'
	<< hotfix << " Copyright (C) " << year << ' ' << author << '\n'
	<< "This program comes with ABSOLUTELY NO WARRANTY.\n"
	<< "This is free software, and you are welcome to redistribute it\n";
}

