#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <unordered_map>
#include <algorithm>

struct Position
{
	size_t x;
	size_t y;
	size_t t;

	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}
};

struct PairHash
{
	size_t operator()(const std::pair<size_t, size_t>& p) const noexcept
	{
		return std::hash<size_t>()(p.first) ^ (std::hash<size_t>()(p.second) << 1);
	}
};

static std::vector<std::vector<char>> buildGrid(std::ifstream& file)
{
	char buffer[4096];

	auto fileStart = file.tellg();

	file.getline(buffer, sizeof(buffer));
	const std::string_view firstLine = { buffer };

	file.seekg(fileStart);

	size_t y = 0;
	size_t x = 0;
	while (file.getline(buffer, sizeof(buffer)))
	{
		x = 0;
		std::string_view line { buffer };
		for (auto c : line)
		{
			x++;
		}
		y++;
	}

	file = std::ifstream { "D:/Github/adventofcode25/cpp/App/Source/resources/day7.txt" };
	std::vector<std::vector<char>> grid(x, std::vector<char>(y));
	y = 0;

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

	return grid;
}

static void printGrid(const std::vector<std::vector<char>>& grid)
{
	for (size_t y = 0; y < grid[0].size(); y++)
	{
		for (size_t x = 0; x < grid.size(); x++)
		{
			std::cout << grid[x][y];
		}

		std::cout << std::endl;
	}
}

static void traverseBeam(int64_t& nSplit, const std::vector<std::vector<char>>& grid, Position& s, std::vector<Position>& splitters, std::vector<Position>& beams)
{
	while (grid[s.x][s.y] != '^')
	{
		s.y++;
		if (s.y == grid[0].size())
			return;
	}

	Position splitter { s.x, s.y };
	if (std::find(splitters.begin(), splitters.end(), splitter) == splitters.end())
	{
		nSplit++;
		splitters.push_back(splitter);
	}

	Position newBeam1 = { s.x + 1, s.y };
	if (std::find(beams.begin(), beams.end(), newBeam1) == beams.end())
	{
		beams.push_back(newBeam1);
		traverseBeam(nSplit, grid, newBeam1, splitters, beams);
	}

	Position newBeam2 = { s.x - 1, s.y };
	if (std::find(beams.begin(), beams.end(), newBeam2) == beams.end())
	{
		beams.push_back(newBeam2);
		traverseBeam(nSplit, grid, newBeam2, splitters, beams);
	}
}

static void mergeBeam(
	std::unordered_map<std::pair<size_t, size_t>, Position, PairHash>& m,
	const Position& incoming,
	std::vector<std::vector<char>>& grid)
{
	using Key = std::pair<size_t, size_t>;

	Key k = { incoming.x, incoming.y };

	auto it = m.find(k);
	if (it != m.end())
	{
		it->second.t += incoming.t;
	}
	else
	{
		m[k] = incoming;
	}
}

static void traverseBeamQuantum(std::vector<std::vector<char>>& grid, Position s)
{
	using Key = std::pair<size_t, size_t>;

	std::unordered_map<Key, Position, PairHash> beams;      // current beams
	std::unordered_map<Key, Position, PairHash> newBeams;   // next-step beams

	beams[{s.x, s.y}] = s;

	size_t height = grid.size();
	size_t width = grid[0].size();

	for (size_t y = 1; y < width; y++)
	{
		newBeams.clear();

		for (const auto& [key, b] : beams)
		{
			Position nb = b;
			nb.y = y;

			if (grid[b.x][y] == '^')
			{
				if (b.x > 0)
				{
					Position leftBeam { b.x - 1, y, b.t };
					mergeBeam(newBeams, leftBeam, grid);
				}

				if (b.x + 1 < height)
				{
					Position rightBeam { b.x + 1, y, b.t };
					mergeBeam(newBeams, rightBeam, grid);
				}
			}
			else
			{
				mergeBeam(newBeams, nb, grid);
			}
		}

		beams.swap(newBeams);
	}

	size_t sum = 0;

	for (auto& beam : beams)
		sum += beam.second.t;

	Log("{}", sum);
}

int main()
{
	std::ifstream file { "D:/Github/adventofcode25/cpp/App/Source/resources/day7.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	std::vector<std::vector<char>> grid = buildGrid(file);

	Position start {};

	for (size_t y = 0; y < grid[0].size(); y++)
	{
		for (size_t x = 0; x < grid.size(); x++)
		{
			if (grid[x][y] == 'S')
				start = { x, y, 1 };
		}
	}

	Log("START: {},{}", start.x, start.y);

	//int64_t nSplit = 0;
	std::vector<Position> splitters;
	std::vector<Position> beams;

	//traverseBeam(nSplit, grid, start, splitters, beams);

	traverseBeamQuantum(grid, start);
}
