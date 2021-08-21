# wildcard
A simple c ++ implementation of a Unicode-enabled wildcard matching algorithm.
![GitHub](https://img.shields.io/github/license/kolod/wildcard) ![GitHub all releases](https://img.shields.io/github/downloads/kolod/wildcard/total) ![GitHub last commit](https://img.shields.io/github/last-commit/kolod/wildcard) ![GitHub Release Date](https://img.shields.io/github/release-date/kolod/wildcard)


## Usage

```c++
#include "wildcard.h"
...
wildcard::Wildcard w(L"*.cpp");
if (w.match(L"wildcard.cpp") {
	...
}

```

