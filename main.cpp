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
#include <vector>
#include <fstream>


struct arguments
{
	std::string author;
	std::string title;
	std::string fileName;
	std::string docClass;
	std::string encoding;
	std::string language;
	std::vector<std::string> packages;
	bool help;
	bool version;
};

void help(std::ostream& out = std::cout);
void version();
arguments parse_args(int argc, char* argv[]);

static const std::string_view author{"Kjartan Óli Ágústsson"};
static const std::string_view year{"2020"};
static const std::string_view versionNum{"1.2.0"};

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

	// append the ".tex" extension if necesary
	std::ofstream file{args.fileName.find(".tex") == std::string::npos ? args.fileName + ".tex" : args.fileName};

	file << "\\documentclass{" << args.docClass << "}\n\n"
	<< "\\usepackage[T1]{fontenc}\n"
	<< (args.title != ""  ? "\\title{" + args.title + "}\n" : "")
	<< (args.author != "" ? "\\author{" + args.author + "}\n" : "")
	<< (args.encoding != ""  ? "\\usepackage[" + args.encoding + "]{inputenc}\n" : "")
	<< (args.language != ""  ? "\\usepackage[" + args.language + "]{babel}\n" : "");

	if (args.packages.size() > 0)
	{
		file << '\n';
		for (const std::string& package : args.packages)
		{
			file << "\\usepackage{" << package << "}\n";
		}
	}

	file << "\n\\begin{document}\n\t\n\\end{document}\n";

	return 0;
}

arguments parse_args(int argc, char* argv[])
{
	arguments args{};

	for (int i{1}; i < argc; ++i)
	{
		std::string_view arg{argv[i]};
		if (arg == "-h" || arg == "--help")
		{
			args.help = true;
		}
		else if (arg == "-V" || arg == "--version")
		{
			args.version = true;
		}
		else if (arg == "-a" || arg == "--author")
		{
			 args.author = argv[++i];
		}
		else if (arg == "-t" || arg == "--title")
		{
			args.title = argv[++i];
		}
		else if (arg == "-e" || arg == "--encoding")
		{
			args.encoding = argv[++i];
		}
		else if (arg == "-l" || arg == "--language")
		{
			args.language = argv[++i];
		}
		else if (arg == "-u" || arg == "--usepackage")
		{
			args.packages.push_back(argv[++i]);
		}
		else if (i == argc - 2)
		{
			args.fileName = argv[i++];
			args.docClass = argv[i++];
		}
	}

	return args;
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
	<< indent << "-h,\t--help\t\t\tPrint this help and exit\n"
	<< indent << "-l,\t--language=LANGUAGE\tLoad the babel package for LANGUAGE\n"
	<< indent << "-u,\t--usepackage=PACKAGE\tAdd a \\usepackage{PACKAGE} statement\n"
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
