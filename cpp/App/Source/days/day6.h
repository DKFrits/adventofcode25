#include "Util.h"
#include "Logger.h"
#include <fstream>

static std::tuple<std::vector<std::string>, size_t> get_operations(std::ifstream& file)
{
	char buffer[4096];
	std::vector<std::string> operations;

	size_t operationsPerLine = 0;

	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string_view line { buffer };
		std::string operation = "";
		operationsPerLine = 0;
		size_t lineIndex = 0;

		for (auto c : line)
		{
			if (c == ' ')
			{
				if (operation != "")
				{
					operations.push_back(operation);
					operation = "";
					operationsPerLine++;
				}

				lineIndex++;
				continue;
			}

			lineIndex++;
			operation += c;

			if (line.size() == lineIndex && operation != "")
				operations.push_back(operation);
		}
	}

	return { operations, operationsPerLine };
}

struct Calculation
{
	std::vector<int64_t> numbers;
	char operation;
};

static std::vector<Calculation> get_calculations(std::ifstream& file)
{
	char buffer[4096];
	std::vector<Calculation> calculations;
	std::vector<std::string> lines;

	while (file.getline(buffer, sizeof(buffer)))
	{
		std::string line { buffer };
		lines.push_back(line);
	}

	size_t maxSize = 0;

	for (auto& l : lines)
	{
		if (l.size() > maxSize)
			maxSize = l.size();
	}

	size_t operationsPerLine = 0;
	std::vector<int64_t> numbers;
	char o;

	for (int64_t i = maxSize - 1; i >= 0; i--)
	{
		std::string_view line { buffer };
		std::string operation = "";

		for (int64_t j = 0; j < lines.size(); j++)
		{
			char c = lines[j][i];

			if (c == ' ' || c == '\n' || c == '\0')
			{
				if (operation != "")
				{
					numbers.push_back(*to_number<int64_t>(operation));
					operation = "";
				}

				continue;
			}

			if (c == '+' || c == '*')
			{
				if (operation != "")
					numbers.push_back(*to_number<int64_t>(operation));

				o = c;

				calculations.push_back({ numbers, o });
				numbers.clear();

				continue;
			}

			operation += c;
		}
	}

	return calculations;
}

int day6()
{
	std::ifstream file { "D:/Github/adventofcode25/cpp/App/Source/resources/day6.txt" };

	if (!file)
	{
		Error("Failed to open file");
		return 1;
	}

	auto [operations, n] = get_operations(file);
	size_t nOperation = operations.size() / n;

	int64_t total = 0;

	for (size_t i = 0; i < n; i++)
	{
		auto& o = operations[i + (n * (nOperation - 1))];
		int64_t answer = 0;

		for (size_t j = 0; j < nOperation - 1; j++)
		{
			auto number = *to_number<int64_t>(operations[i + (n * j)]);

			if (j == 0)
			{
				answer += number;
				continue;
			}

			if (o == "+")
				answer += number;
			else if (o == "*")
				answer *= number;
		}

		total += answer;
	}

	Log("Part 1: {}", total);

	file = std::ifstream { "D:/Github/adventofcode25/cpp/App/Source/resources/day6.txt" };

	auto calculations = get_calculations(file);
	total = 0;

	for (auto& c : calculations)
	{
		int64_t answer = 0;

		for (size_t i = 0; i < c.numbers.size(); i++)
		{
			if (i == 0)
			{
				answer += c.numbers[i];
				continue;
			}

			if (c.operation == '+')
				answer += c.numbers[i];
			else if (c.operation == '*')
				answer *= c.numbers[i];
		}

		total += answer;
	}

	Log("Part 2: {}", total);
}
