#include "../include/stypox/frequency.h"

#include <algorithm>

namespace stypox {
Clock<> FrequencyCount::m_clock{};
Clock<> FrequencyTime::m_clock{};

FrequencyCount::FrequencyCount(const int nrPings) :
	m_pings(nrPings, 0.0f), m_currentPing{0} {}

void FrequencyCount::ping() {
	m_pings[m_currentPing] = m_clock.now();

	++m_currentPing;
	if (m_currentPing == m_pings.size())
		m_currentPing = 0;
}

float FrequencyCount::frequency() {
	if (m_currentPing == 0)
		return (m_pings.size()-1) / (m_pings.back() - m_pings.front());
	else
		return (m_pings.size()-1) / (m_pings[m_currentPing-1] - m_pings[m_currentPing]);
}
float FrequencyCount::period() {
	return 1.0f / frequency();
}



void FrequencyTime::removeOldPings(const float now) {
	auto firstValid = std::find_if(m_pings.begin(), m_pings.end(), [this, now](float ping){ return ping + m_timeMax > now; });
	m_pings.erase(m_pings.begin(), firstValid);
}

FrequencyTime::FrequencyTime(const float timeMax) :
	m_timeMax{timeMax} {}

void FrequencyTime::ping() {
	float now = m_clock.now();
	m_pings.push_back(now);
	removeOldPings(now);
}

float FrequencyTime::frequency() {
	removeOldPings(m_clock.now());
	if (m_pings.size() < 2)
		return 0.0f;
	
	return (m_pings.size()-1) / (m_pings.back() - m_pings.front());
}
float FrequencyTime::period() {
	removeOldPings(m_clock.now());
	if (m_pings.size() < 2)
		return std::numeric_limits<float>::max();

	return (m_pings.back() - m_pings.front()) / (m_pings.size()-1);
}
} // namespace stypox