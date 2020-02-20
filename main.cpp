/*
 * Copyright (C) 2020  Ágústsson, Kjartan Óli <kjartanoli@protonmail.com>
 * Author: Ágústsson, Kjartan Óli <kjartanoli@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
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

#include "file.h"

void help(std::ostream& out = std::cout);
void version();

static const std::string_view author{"Kjartan Óli Ágústsson"};
static const std::string_view year{"2020"};
static const std::string_view versionNum{"1.0.1"};

int main(int argc, char* argv[])
{
	std::string docAuthor{};
	std::string title{};
	std::string fileName{};
	std::string docClass{};
	bool utf8{false};

	for (int i{1}; i < argc; ++i)
	{
		std::string_view arg{argv[i]};
		if (arg == "-h" || arg == "--help")
		{
			help();
			return 0;
		}
		else if (arg == "-V" || arg == "--version")
		{
			version();
			return 0;
		}
		else if (arg == "-a" || arg == "--author")
		{
			docAuthor = argv[++i];
		}
		else if (arg == "-t" || arg == "--title")
		{
			title = argv[++i];
		}
		else if (arg == "-u" || arg == "--utf8")
		{
			utf8 = true;
		}
		else if (i == argc - 2)
		{
			fileName = argv[i++];
			docClass = argv[i++];
		}
	}

	File file{fileName.find(".tex") == std::string::npos ? fileName + ".tex" : fileName};

	file << "\\documentclass{" << docClass << "}\n\n"
	<< (title != ""  ? "\\title{" + title + "}\n" : "")
	<< (docAuthor != "" ? "\\author{" + docAuthor + "}\n" : "")
	<< (utf8 ? "\\usepackage[T1]{fontenc}\n\\usepackage[utf8]{inputenc}\n" : "")
	<< "\n\\begin{document}\n\t\n\\end{document}\n";

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
	<< indent << "-h,\t--help\t\t\tPrint this help and exit\n"
	<< indent << "-a,\t--author=AUTHOR\t\tAdd a \\author{AUTHOR} command to the document\n"
	<< indent << "-t,\t--title=TITLE\t\tAdd a \\title{TITLE} command to the document\n\n"
	<< "texplate " << versionNum << " Copyright (C) " << year << ' ' << author << "\nThis pragram comes with"
	<< " ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\n";
}

// print version information
void version()
{
	std::cout << "texplate " << versionNum << " Copyright (C) " << year
	<< ' ' << author << "\nThis pragram comes with"
	<< " ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\n";

}
