#include "stdafx.h"
#include "Timer.h"

BEGIN(Engine)
IMPLEMENT_SINGLETON(Timer)


Timer::Timer()
: m_fTime(0.f)
{
	ZeroMemory(&m_liFrameTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_liFixTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_liLastTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_liCpuTick, sizeof(LARGE_INTEGER));
}

Timer::~Timer()
{
}

void Timer::Init(void)
{
	QueryPerformanceCounter(&m_liFrameTime);
	QueryPerformanceCounter(&m_liFixTime);
	QueryPerformanceCounter(&m_liLastTime);
	QueryPerformanceFrequency(&m_liCpuTick);
}


void Timer::Update(void)
{
	QueryPerformanceCounter(&m_liFrameTime);

	if (m_liFrameTime.QuadPart - m_liLastTime.QuadPart > m_liCpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_liCpuTick);
		m_liLastTime.QuadPart = m_liFrameTime.QuadPart;
	}

	m_fTime = float(m_liFrameTime.QuadPart - m_liFixTime.QuadPart) / m_liCpuTick.QuadPart;

	m_liFixTime = m_liFrameTime;
}


END