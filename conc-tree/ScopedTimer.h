#pragma once

#include <iostream>
#include <chrono>
#include "Macros.h"

#define MEASURE_FUNCTION() ScopedTimer timer{__func__}

class ScopedTimer {
public:
	using clock_type = std::chrono::steady_clock;

	ScopedTimer(const char* function)
		: function_{ function }
		, start_{ clock_type::now() }
	{
	}

	~ScopedTimer() {
		using namespace std::chrono;
		const auto stop = clock_type::now();
		const auto duration = stop - start_;
		const auto ms = duration_cast<milliseconds>(duration).count();
		std::cout << ms << " ms " << function_ << std::endl;
	}

	DISALLOW_COPY_AND_MOVE(ScopedTimer);
	
private:
	const char* function_{};
	const clock_type::time_point start_{};
};