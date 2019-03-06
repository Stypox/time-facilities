#ifndef _STYPOX_FREQUENCY_H_
#define _STYPOX_FREQUENCY_H_

#include <vector>

#include "clock.h"

namespace stypox {
class FrequencyCount {
	static Clock<> m_clock;

	std::vector<float> m_pings;
	unsigned int m_currentPing;

public:
	FrequencyCount(const int nrPings);

	void ping();

	float frequency();
	float period();
};


class FrequencyTime {
	static Clock<> m_clock;

	std::vector<float> m_pings;
	float m_timeMax;

	void removeOldPings(const float now);

public:
	FrequencyTime(const float timeMax);

	void ping();

	float frequency();
	float period();
};
} // namespace stypox

#endif // _STYPOX_FREQUENCY_H_