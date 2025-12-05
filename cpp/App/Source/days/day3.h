#pragma once

#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Joltage
{
	int value;
	int index;
};

static Joltage nextJoltage(std::string_view line, int skipLeftIndex, int i, int nBatteries)
{
	Joltage joltage = { -1, -1 };
	int index = 0;

	for (auto c : line)
	{
		int n = c - '0';

		if (index > skipLeftIndex && n > joltage.value && index <= line.length() - (nBatteries - i))
		{
			joltage.value = n;
			joltage.index = index;
		}

		index++;
	}

	return joltage;
}

int day3()
{
	std::ifstream file{ "D:/Github/adventofcode25/cpp/App/Source/resources/day3.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];
	int64_t sum = 0;
	int nBatteries = 12;

	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string nStr{};
		std::string_view line{ buffer };

		int skipLeftIndex = -1;

		for (size_t i = 0; i < nBatteries; i++)
		{
			auto joltage = nextJoltage(line, skipLeftIndex, i, nBatteries);
			skipLeftIndex = joltage.index;

			nStr += (char)(joltage.value + '0');
		}

		int64_t joltageVal = *to_number<int64_t>(nStr);
		sum += joltageVal;
		Log("{}", joltageVal);
	}

	Log("{}", sum);
}
