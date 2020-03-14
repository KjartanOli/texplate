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

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>
#include <fstream>
#include <map>

struct arguments
{
	std::string author;
	std::string title;
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
	BIBSOURCE,
	HELP,
	TITLE,
	ENCODING,
	LANGUAGE,
	USEPACKAGE,
	VERSION,
};

static std::map<std::string_view, argumentValues> argumentMap
{
	{"-a", AUTHOR},
	{"--author", AUTHOR},
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

void help(std::ostream& out = std::cout);
void help(const std::string& unknown);
void version();
arguments parse_args(int argc, char* argv[]);
bool has_bibpackage(const std::vector<std::string>& packages);
std::ofstream open_file(const std::string& fileName);
void write(const arguments& args);

// copyright information
static const std::string_view author{"Kjartan Óli Ágústsson"};
static const std::string_view year{"2020"};

// version information
static const short majorVersion{1};
static const short minorVersion{3};
static const short hotfix{1};

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

// set the members of the arguments struct appropriately to command line arguments
arguments parse_args(int argc, char* argv[])
{
	arguments args{};

	for (int i{1}; i < argc; ++i)
	{
		std::string_view arg{argv[i]};
		switch(argumentMap[arg])
		{
			case AUTHOR:
				args.author = argv[++i];
				break;
			case TITLE:
				args.title = argv[++i];
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
				args.encoding = argv[++i];
				break;
			case LANGUAGE:
				args.language = argv[++i];
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
					return args;
				}
				break;
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
	<< indent << "-b,\t--bibsource=SOURCE\tAdd a \\addbibresources{SOURCE} to the document\n"
	<< indent << "\t\t\t\tand if no biblatex package is used with the\n"
	<< indent << "\t\t\t\t-u option add \\usepackage{biblatex} as well\n"
	<< indent << "-h,\t--help\t\t\tPrint this help and exit\n"
	<< indent << "-l,\t--language=LANGUAGE\tLoad the babel package for LANGUAGE\n"
	<< indent << "-u,\t--usepackage=PACKAGE\tAdd a \\usepackage{PACKAGE} statement\n"
	<< indent << "-t,\t--title=TITLE\t\tAdd a \\title{TITLE} command to the document\n\n"
	<< "\nErrors:\n"
	<< indent << "1\tMissing FILENAME or DOCUMENTCLASS\n"
	<< indent << "2\tUnknown option\n"
	<< "\ntexplate " << majorVersion << '.' << minorVersion << '.' << hotfix << " Copyright (C) "
	<< year << ' ' << author << "\nThis program comes with ABSOLUTELY NO WARRANTY.\n"
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
	std::cout << "texplate " << majorVersion << '.' << minorVersion << '.' << hotfix << " Copyright (C) " << year
	<< ' ' << author << "\nThis pragram comes with"
	<< " ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\n";
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

// write to the file
void write(const arguments& args)
{
	std::ofstream file{open_file(args.fileName)};

	file << "\\documentclass{" << args.docClass << "}\n\n"
	<< "\\usepackage[T1]{fontenc}\n\n"
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

	if (args.bibsources.size() > 0)
	{
		file << '\n';
		for (const std::string& source : args.bibsources)
		{
			// check if the .bib extension needs to be added
			file << "\\addbibresource{" << (source.find(".bib") == std::string::npos ? source + ".bib" : source) << "}\n";
		}
	}

	file << "\n\\begin{document}\n\t\n\\end{document}\n";

}

// open the output file for writing
std::ofstream open_file(const std::string& name)
{
	// append the ".tex" extension if necesary
	std::ofstream file{name.find(".tex") == std::string::npos ? name + ".tex" : name};

	return file;
}

