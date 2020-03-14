# Changelog

## [1.4.1]
### Added
* CHANGELOG.md
* README.md

## [1.4.0]
### Added
* Support for insertion of bib resources
* Explanation of the meaning of possible error codes
* Error message for unknown options
* Error message if FILENAME or DOCUMENTCLASS are not provided

### Changed
* Moved writing files out of main() into write()
* Moved deciding the output file name from main() to open_file()
* Changed parse_args() to use a switch on Eunum values instead of chained if statements

## [1.3.0]
### Added
* Support for insertion of usepackage statements
* Support for \usepackage[LANGUAGE]{babel}
### Changed
* Moved the various command line arguments from variables to a struct
* Moved parsing command line arguments from main() to parse_args()
### Removed
* Unnecesary dependency on non-STL wrapper for std::fstreams

## [1.2.0]
### Added
* Support for setting the output encoding used by latex
### Changed
* Made the fontenc package part of the standard template

## [1.1.0]
### Added
* Option to load the fontenc package to make LaTex use UTF-8 encoding

## [1.0.0]
### Added
* Created texplate