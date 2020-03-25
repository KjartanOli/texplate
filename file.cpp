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
#include <string>

#include "file.hpp"

// write to the file
void write(const arguments& args)
{
	std::ofstream file{open_file(args.fileName)};

	file << "\\documentclass{" << args.docClass << "}\n\n"
	<< "\\usepackage[T1]{fontenc}\n\n"
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
			file << "\\addbibresource{" << add_extension(source, ".bib") << "}\n";
		}
	}
	file << (args.title != ""  ? "\\title{" + args.title + "}\n" : "")
	<< (args.author != "" ? "\\author{" + args.author + "}\n" : "")
	<< (args.date != "" ? "\\date{" + args.date + "}\n" : "")
	<< "\n\\begin{document}\n\t\n\\end{document}\n";
}

// open the output file for writing
std::ofstream open_file(const std::string& name)
{
	// append the ".tex" extension if necesary
	std::ofstream file{add_extension(name, ".tex")};

	return file;
}

// add the filextension if necessary
std::string add_extension(const std::string& fileName, const std::string&  extension)
{
	return (fileName.find(extension) == std::string::npos ? fileName + extension: fileName);
}
