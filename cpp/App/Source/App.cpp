#include "Util.h"
#include "Logger.h"
#include <fstream>

int main()
{
	std::ifstream file { "C:/Git/adventofcode25/cpp/App/Source/resources/day6.txt" };

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
