# wildcard

A simple c ++ implementation of a Unicode-enabled wildcard matching algorithm.

![GitHub](https://img.shields.io/github/license/kolod/wildcard) ![GitHub all releases](https://img.shields.io/github/downloads/kolod/wildcard/total) ![GitHub last commit](https://img.shields.io/github/last-commit/kolod/wildcard) ![GitHub Release Date](https://img.shields.io/github/release-date/kolod/wildcard) ![Travis (.com)](https://img.shields.io/travis/com/kolod/wildcard) [![codecov](https://codecov.io/gh/kolod/wildcard/branch/main/graph/badge.svg?token=GDZUER1HJP)](https://codecov.io/gh/kolod/wildcard)

## Usage

Copy `wildcard.h` & `wildcard.cpp` to your project.

```c++
#include "wildcard.h"
...
wildcard::Wildcard w(L"*.cpp");
if (w.match(L"wildcard.cpp") {
	...
}

```
