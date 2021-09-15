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

#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace wildcard
{

	struct transition_t
	{
		union
		{
			wchar_t wSymbol;
			char    cSymbol;
		};
		size_t state;
	};

	struct state_t
	{
		transition_t transition[2];
		bool         isSecondActive;
		bool         isChar;
	};

	enum class result
	{
		ok,
		failed,
		finished
	};

	class Wildcard
	{

	public:
		explicit Wildcard(const std::wstring &pattern);
		explicit Wildcard(const char         *pPattern);
		bool match(const std::wstring &word);
		bool match(const char         *pWord);

	private:
		std::vector<size_t> mCurrentStates;
		std::vector<state_t> mStates;

		void reset();
		result addSymbol(wchar_t symbol);
		result addSymbol(char    symbol);
		bool checkAndAdd(std::vector<size_t> &states, const transition_t &transition, wchar_t symbol);
		bool checkAndAdd(std::vector<size_t> &states, const transition_t &transition, char    symbol);

#ifdef WILDCARD_DEBUG
		void print();
#endif
	};

} // namespace
