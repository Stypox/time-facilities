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
	return m_pings.size() / (m_pings[m_currentPing - 1 /* <-- problem when = 0 */] - m_pings[m_currentPing]);
}
float FrequencyCount::seconds() {
	return (m_pings[m_currentPing - 1 /* <-- problem when = 0 */] - m_pings[m_currentPing]) / m_pings.size();
}



void FrequencyTime::removeOldPings() {
	float now = m_clock.now();
	auto firstValid = std::find_if(m_pings.begin(), m_pings.end(), [this, now](float ping){ return ping + m_timeMax > now; });
	if (firstValid != m_pings.end())
		m_pings.erase(m_pings.begin(), firstValid);
}

FrequencyTime::FrequencyTime(const float timeMax) :
	m_timeMax{timeMax} {}

void FrequencyTime::ping() {
	m_pings.push_back(m_clock.now());
	removeOldPings();
}

float FrequencyTime::frequency() {
	removeOldPings();
	if (m_pings.size() < 2)
		return 0.0f;
	
	return m_pings.size() / (m_pings.back() - m_pings.front());
}
float FrequencyTime::seconds() {
	removeOldPings();
	if (m_pings.size() < 2)
		return std::numeric_limits<float>::max();

	return (m_pings.back() - m_pings.front()) / m_pings.size();
}
} // namespace stypox