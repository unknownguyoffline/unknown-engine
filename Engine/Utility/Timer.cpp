#include "Timer.hpp"

namespace Unk
{
	void Timer::Start()
	{
		mStart = std::chrono::high_resolution_clock::now();
		mRunning = true;
	}

	float Timer::End()
	{
		if (mRunning == false)
		{
			printf("Error: timer not running\n");
			return 0;
		}

		mRunning = false;
		auto end = std::chrono::high_resolution_clock::now();
		mDuration = end - mStart;
		return GetDuration();
	}

	float Timer::GetDuration()
	{
		return mDuration.count();
	}

	float Timer::GetElapsedTime()
	{
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - mStart;
		return duration.count();
	}

	ScopeProfiler::ScopeProfiler(const std::string& name)
	{
		mTimer.Start();
		mName = name;
	}

	ScopeProfiler::~ScopeProfiler()
	{
		mTimer.End();
		printf("elapsed time: %s %f\n", mName.c_str(), mTimer.GetDuration());
	}
}
