#ifndef DEVAPP_H
#define DEVAPP_H

class DevApp
{
protected:
	DevApp();
	~DevApp();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

	int getFPS();

private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
	int m_fps;
};

#endif

