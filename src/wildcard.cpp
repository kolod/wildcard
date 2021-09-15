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

#include "wildcard.h"

namespace wildcard
{

	Wildcard::Wildcard(const std::wstring& pattern)
	{
		for (size_t i = 0; i < pattern.size() + 1; i++)
		{
			state_t state;

			if (pattern[i] != L'*')
			{
				state.isSecondActive = false;
			}
			else
			{
				i++;
				state.isSecondActive = true;
				state.transition[1].wSymbol = L'?';
				state.transition[1].state = mStates.size();
			}

			state.transition[0].wSymbol = pattern[i];
			state.transition[0].state = mStates.size() + 1;
			mStates.push_back(state);
		}

#ifdef WILDCARD_DEBUG
		print();
#endif
	}

	Wildcard::Wildcard(const char* pPattern)
	{
		for (size_t i = 0; i < strlen(pPattern); i++)
		{
			state_t state;

			if (pPattern[i] != '*')
			{
				state.isSecondActive = false;
			}
			else
			{
				i++;
				state.isSecondActive = true;
				state.transition[1].cSymbol = '?';
				state.transition[1].state = mStates.size();
			}

			state.isChar = true;
			state.transition[0].cSymbol = pPattern[i];
			state.transition[0].state = mStates.size() + 1;
			mStates.push_back(state);
		}

#ifdef WILDCARD_DEBUG
		print();
#endif
	}

	void Wildcard::reset()
	{
		mCurrentStates.clear();
		mCurrentStates.push_back(0);
	}

	bool Wildcard::checkAndAdd(std::vector<size_t>& states, const transition_t& transition, wchar_t symbol)
	{
		bool finished = false;
		if ((transition.wSymbol == symbol) || (transition.wSymbol == L'?'))
		{
			states.push_back(transition.state);
			if (transition.state == mStates.size())
				finished = true;
		}
		return finished;
	}

	bool Wildcard::checkAndAdd(std::vector<size_t>& states, const transition_t& transition, char symbol)
	{
		bool finished = false;
		if ((transition.cSymbol == symbol) || (transition.cSymbol == '?'))
		{
			states.push_back(transition.state);
			if (transition.state == mStates.size())
				finished = true;
		}
		return finished;
	}

	result Wildcard::addSymbol(wchar_t symbol)
	{
		std::vector<size_t> newStates;
		bool finishedState = false;

		for (auto currentState : mCurrentStates)
		{
			finishedState = finishedState || checkAndAdd(newStates, mStates[currentState].transition[0], symbol);
			if (mStates[currentState].isSecondActive)
				finishedState = finishedState || checkAndAdd(newStates, mStates[currentState].transition[1], symbol);
		}

		if (newStates.size() == 0)
			return result::failed;
		if (!symbol && finishedState)
			return result::finished;

		mCurrentStates = newStates;
		return result::ok;
	}

	result Wildcard::addSymbol(char symbol)
	{
		std::vector<size_t> newStates;
		bool finishedState = false;

		for (auto currentState : mCurrentStates)
		{
			finishedState = finishedState || checkAndAdd(newStates, mStates[currentState].transition[0], symbol);
			if (mStates[currentState].isSecondActive)
				finishedState = finishedState || checkAndAdd(newStates, mStates[currentState].transition[1], symbol);
		}

		if (newStates.size() == 0)
			return result::failed;
		if (!symbol && finishedState)
			return result::finished;

		mCurrentStates = newStates;
		return result::ok;
	}

	bool Wildcard::match(const std::wstring &word)
	{
		reset();
		for (auto c : word)
			if (addSymbol(c) == result::failed)
				return false;
		return addSymbol(static_cast<wchar_t>(0)) == result::finished;
	}

	bool Wildcard::match(const char *pWord)
	{
		reset();
		for (uint32_t i = 0; i < strlen(pWord); i++)
		{
			const char c = pWord[i];
			if (addSymbol(c) == result::failed)
				return false;
		}
		return addSymbol(static_cast<char>(0)) == result::finished;
	}

#ifdef WILDCARD_DEBUG
	void Wildcard::print()
	{
		for (auto state : mStates)
		{
			if (state.isChar)
			{
				std::cout << " -" << state.transition[0].cSymbol << "-> " << state.transition[0].state << std::endl;
				if (state.isSecondActive)
					std::cout << " -" << state.transition[1].cSymbol << "-> " << state.transition[1].state << std::endl;
			}
			else
			{
				std::wcout << L" -" << state.transition[0].wSymbol << L"-> " << state.transition[0].state << std::endl;
				if (state.isSecondActive)
					std::wcout << L" -" << state.transition[1].wSymbol << L"-> " << state.transition[1].state << std::endl;
			}
		}
	}
#endif

} // namespace
