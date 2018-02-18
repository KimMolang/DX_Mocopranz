#pragma once

BEGIN(Engine)


class ENGINE_DLL Timer
{
	DECLARE_SINGLETON(Timer)

private :
	LARGE_INTEGER		m_liFrameTime;
	LARGE_INTEGER		m_liFixTime;
	LARGE_INTEGER		m_liLastTime;
	LARGE_INTEGER		m_liCpuTick;

	float				m_fTime;


public :
	void	Init();
	void	Update();

	float	GetTime() { return m_fTime;  }


public:
	Timer();
	~Timer();
};


END