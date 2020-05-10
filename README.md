# Texplate

Texplate is an unofficial LaTex utility to generate document preambles.

## Requirements

* C++ compiler with support for C++17
* Open Source Parsers [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## Getting started

```
git clone https://github.com/KjartanOli/texplate.git
cd texplate
make
make install
```

## Usage

```
texplate [OPTIONS] FILENAME DOCUMENTCLASS
```

### Examples

```
texplate -a "John Doe" -t "My Document" main article
texplate -a -t Document main report
```
