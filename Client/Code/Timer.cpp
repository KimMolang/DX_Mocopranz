#include "stdafx.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimer)


CTimer::CTimer()
: m_fTime(0.0f)
{
	ZeroMemory(&m_liFrameTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_liFixTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_liLastTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_liCpuTick, sizeof(LARGE_INTEGER));
}

CTimer::~CTimer()
{
}

void CTimer::Init(void)
{
	QueryPerformanceCounter(&m_liFrameTime);
	QueryPerformanceCounter(&m_liFixTime);
	QueryPerformanceCounter(&m_liLastTime);
	QueryPerformanceFrequency(&m_liCpuTick);
}


void CTimer::Update(void)
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