#pragma once

#include <chrono>

class Clock
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_CurrentTime;
	float m_DeltaTime;
	float m_ElapsedTime;
	float m_TotalTime;

public:
	Clock();
	~Clock();

	void After();
	void Before();

	float GetDeltaTime() const;
	float GetElapsedTime() const;
};
