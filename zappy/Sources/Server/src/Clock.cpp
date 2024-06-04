#include "Clock.hpp"

Clock::Clock()
{
	m_DeltaTime = 0;
	m_ElapsedTime = 0;
	m_TotalTime = 0;
}

Clock::~Clock()
{

}

void Clock::Before()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurrentTime - m_LastTime).count() / 1000.0f;
	m_LastTime = m_CurrentTime;
}

void Clock::After()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	m_ElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_CurrentTime).count() / 1000.0f;
	m_TotalTime += m_ElapsedTime;
}

float Clock::GetDeltaTime() const
{
	return m_DeltaTime;
}

float Clock::GetElapsedTime() const
{
	return m_ElapsedTime;
}
