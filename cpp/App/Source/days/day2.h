#pragma once

#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>

int day2()
{
	std::ifstream file{ "D:/Github/adventofcode25/cpp/App/Source/resources/day2.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];

	long long invalidSum = 0;

	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line{ buffer };

		auto ranges = split(line, ",");

		for (auto& range : ranges)
		{
			auto numbers = split(range, "-");

			auto n1 = std::stoll(numbers[0].data());
			auto n2 = std::stoll(numbers[1].data());

			while (n1 <= n2)
			{
				auto nStr = std::to_string(n1);
				auto max = nStr.size() / 2;

				long long last{};

				for (size_t i = 1; i <= max; i++)
				{
					int nMatches = 0;
					auto pattern = nStr.substr(0, i);
					auto patternFitCount = nStr.size() / pattern.size();
					bool canFit = nStr.size() % pattern.size() == 0;

					if (canFit)
					{
						for (size_t j = 0; j < patternFitCount; j++)
						{
							if (nStr.substr(j * i, i) == pattern)
								nMatches += 1;
						}

						int minMatches = nStr.size() / i;

						if (nMatches == minMatches && n1 != last)
						{
							invalidSum += n1;
							last = n1;
						}
					}
				}
				n1++;
			}
		}
	}

	Log("Answer: {}", invalidSum);
}
