#pragma once

#include <chrono> 
#include <ratio>
#include <string_view>
#include <vector>

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

static std::optional<int> toInt(std::string_view sv)
{
	int value;
	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
	if (ec == std::errc()) return value;
	return std::nullopt;
}

long long mod(long long k, long long n)
{
	return ((k %= n) < 0) ? k + n : k;
}
