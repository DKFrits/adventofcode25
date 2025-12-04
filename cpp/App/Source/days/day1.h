#pragma once

#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>

int day1()
{
	std::ifstream file{ "D:/Github/adventofcode25/cpp/App/Source/resources/day1.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];

	int points = 0;
	int dial = 50;

	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line{ buffer };

		auto direction = line.substr(0, 1);
		auto value = *toNumber<int>(line.substr(1));

		auto curr = dial;

		points += value / 100;
		value %= 100;

		dial = direction == "L" ? dial - value : dial + value;

		if ((dial < 0 && curr > 0) || dial > 100)
		{
			Warning("{}", value);
			points++;
		}

		dial = mod(dial, 100);

		if (dial == 0)
			points++;
	}

	Log("Answer: {}", points);
}
