#pragma once

#include <chrono> 
#include <ratio>
#include <string_view>
#include <vector>
#include <ranges>

class Timer
{
private:
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};

template <typename T>
static std::optional<T> to_number(std::string_view sv)
{
	T value {};
	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
	if (ec == std::errc()) return value;
	return std::nullopt;
}

long long mod(long long k, long long n)
{
	return ((k %= n) < 0) ? k + n : k;
}

std::vector<std::string_view> split(std::string_view data, std::string_view delimiter)
{
	std::vector<std::string_view> result;

	auto range =
		data | std::views::split(delimiter)
		| std::views::transform([](auto&& rng)
			{
				return std::string_view(rng.data(), rng.size());
			});

	for (auto sv : range)
		result.push_back(sv);

	return result;
}
