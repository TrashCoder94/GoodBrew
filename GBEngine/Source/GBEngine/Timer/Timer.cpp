#include "gbpch.h"
#include "Timer.h"

namespace GB
{
	Timer::Timer(const float targetTime, const int handle) : 
		m_CurrentTime(targetTime),
		m_Handle(handle),
		m_Function()
	{}
	
	Timer::~Timer()
	{}
}