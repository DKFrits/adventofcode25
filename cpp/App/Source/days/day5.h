#include "Util.h"
#include "Logger.h"
#include <fstream>
#include <algorithm>
#include <set>
#include <cassert>

struct IngredientRange
{
	int64_t start;
	int64_t end;
};

int day5()
{
	std::ifstream file { "D:/Github/adventofcode25/cpp/App/Source/resources/day5.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];
	std::vector<IngredientRange> ranges {};

	size_t total = 0;

	//process ranges
	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line { buffer };

		if (line.size() == 0)
			break;

		auto range = split(line, "-");
		auto start = *to_number<int64_t>(range[0]);
		auto end = *to_number<int64_t>(range[1]);

		ranges.emplace_back(IngredientRange { start, end });
	}

	std::sort(ranges.begin(), ranges.end(), [](const IngredientRange& a, const IngredientRange& b)
		{
			return b.start > a.start;
		});

	IngredientRange previous { ranges[0] };
	std::vector<IngredientRange> filteredRanges {};

	for (size_t i = 1; i < ranges.size(); i++)
	{
		if (ranges[i].start >= previous.start && ranges[i].end <= previous.end && i != ranges.size() - 1)
			continue;

		if (ranges[i].start > previous.end)
		{
			filteredRanges.push_back(previous);
			previous = ranges[i];
		}
		else
		{
			auto start = ranges[i].start <= previous.end ? previous.start : ranges[i].start;

			auto end = ranges[i].end;

			previous = { start, end };
		}

		if (i == ranges.size() - 1)
			filteredRanges.push_back(previous);
	}

	for (auto& range : filteredRanges)
	{
		total += range.end - range.start + 1;
	}

	Log("Total: {}", total);
}

int part1()
{
	std::ifstream file { "D:/Github/adventofcode25/cpp/App/Source/resources/day5.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	char buffer[4096];

	bool processIngredients = false;
	std::vector<size_t> ingredients;

	//collect ingredients list
	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line { buffer };

		if (processIngredients)
			ingredients.emplace_back(*to_number<size_t>(line));

		if (line.size() == 0)
			processIngredients = true;
	}

	file = std::ifstream { "D:/Github/adventofcode25/cpp/App/Source/resources/day5.txt" };
	std::set<size_t> freshIngredients {};

	//process ranges
	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line { buffer };

		if (line.size() == 0)
			break;

		auto range = split(line, "-");
		auto start = *to_number<size_t>(range[0]);
		auto end = *to_number<size_t>(range[1]);


		for (auto ingredient : ingredients)
		{
			if (freshIngredients.contains(ingredient))
				continue;

			if (ingredient >= start && ingredient <= end)
				freshIngredients.insert(ingredient);
		}
	}

	Log("{}", freshIngredients.size());
}
