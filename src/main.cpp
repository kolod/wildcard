//================================================================================
//
// Copyright (c) 2021 by Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
//
// This file is provided under the terms of the MIT License:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//================================================================================

#include <string>
#include <array>
#include "../src/wildcard.h"
#include "../src/setlocale.h"

typedef struct {
	const std::array<bool, 5> answer;
	const std::wstring text;
} sample_t;

const sample_t s1 = { {true, false, true, true, false}, L"wildcard.cpp"};
const sample_t s2 = { {false, true, false, true, false}, L"wildcard.h"};
const sample_t s3 = { {false, false, false, true, false}, L"wildcard.hpp"};
const sample_t s4 = { {false, false, true, true, false}, L"ワイルドカード.cpp"};
const sample_t s5 = { {false, true, false, true, false}, L"ワイルドカード.h"};
const sample_t s6 = { {false, false, true, true, false}, L"шаблон.cpp"};
const sample_t s7 = { {false, true, false, true, false}, L"шаблон.h"};
const sample_t s8 = { {false, false, false, true, true}, L""};

const std::array<const sample_t, 8> samples {s1, s2, s3, s4, s5, s6, s7, s8};

std::wstring fromBool(bool value) {
	return value ? L"'true'" : L"'false'";
}

bool test(std::wstring pattern, int answer) {
	wildcard::Wildcard w(pattern);

	std::wcout << L"Test pattern: '" << pattern << L"'" << std::endl;

	for (auto sample : samples) {
		std::wcout << L"Test sample: '" << sample.text << L"'" << std::endl;
		bool result = w.match(sample.text);
		if (result != sample.answer[answer]) {
			std::wcout
				<< L"Error: must be " << fromBool(sample.answer[answer])
				<< L" but return " << fromBool(result )	<< std::endl;
			return false;
		}
	}
	std::wcout << L"OK" << std::endl;
	return true;
}

int main() {
	init_locale();

	wildcard::Wildcard w(L"");
	w.match(L"");

	return (
		test(L"wildcard.cpp", 0) &&
		test(L"*.h", 1) &&
		test(L"*.cpp", 2) &&
		test(L"*", 3) &&
		test(L"", 4)
	) ? 0 : 1;
}