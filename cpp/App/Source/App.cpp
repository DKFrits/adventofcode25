#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int main()
{
	std::ifstream file { "D:/Github/adventofcode25/cpp/App/Source/resources/day2.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];

	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line { buffer };
	}
}
