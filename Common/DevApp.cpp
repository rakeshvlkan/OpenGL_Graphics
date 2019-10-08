#include "DevApp.h"
#include<Windows.h>
#include <sysinfoapi.h>

DevApp::DevApp()
{
	m_frameCount = 0;
	m_frameTime = 0;
	m_fps = 0;

	m_frameTime = m_startTime = GetTickCount();
}

void DevApp::CalcFPS()
{
	m_frameCount++;
	long long time = GetTickCount();

	if (time - m_frameTime >= 1000) {
		m_frameTime = time;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}
}

void DevApp::RenderFPS()
{
}

float DevApp::GetRunningTime()
{
	float RunningTime = (float)((double)GetTickCount() - (double)m_startTime) / 1000.0f;
	return RunningTime;
}

int DevApp::getFPS()
{
	return m_fps;
}


DevApp::~DevApp()
{
}
