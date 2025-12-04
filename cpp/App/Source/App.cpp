#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>
#include <array>

struct Position
{
	size_t x;
	size_t y;
};

int main()
{
	std::ifstream file { "D:/Github/adventofcode25/cpp/App/Source/resources/day4.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];

	auto fileStart = file.tellg();

	file.getline(buffer, sizeof(buffer));
	const std::string_view firstLine = { buffer };

	file.seekg(fileStart);

	const size_t gridSize = firstLine.size() * firstLine.size();

	std::vector<std::vector<char>> grid(firstLine.size(), std::vector<char>(firstLine.size()));

	std::array<Position, 8> dirs { {
		{-1, -1},
		{0, -1},
		{1, -1},
		{-1, 0},
		{1, 0},
		{-1, 1},
		{0, 1},
		{1, 1}
	} };

	size_t y = 0;
	while (file.getline(buffer, sizeof(buffer)))
	{
		size_t x = 0;
		std::string_view line { buffer };
		for (auto c : line)
		{
			grid[x][y] = c;
			x++;
		}
		y++;
	}

	size_t gridArea = grid.size() * grid.size();
	size_t totalRolls = 0;

	for (size_t y = 0; y < grid.size(); y++)
	{
		for (size_t x = 0; x < grid.size(); x++)
		{
			size_t rolls = 0;

			if (grid[x][y] != '@')
				continue;

			for (auto dir : dirs)
			{
				auto offsetX = x + dir.x;
				auto offsetY = y + dir.y;

				if (offsetX > gridArea || offsetY > gridArea || offsetX > grid.size() - 1 || offsetY > grid.size() - 1)
					continue;

				if (grid[offsetX][offsetY] == '@')
					rolls++;
			}

			if (rolls < 4)
				totalRolls++;
		}
	}

	Log("Total: {}", totalRolls);
}
