#ifndef _STYPOX_FREQUENCY_H_
#define _STYPOX_FREQUENCY_H_

#include <vector>

#include "clock.h"

namespace stypox {
class FrequencyCount {
	std::vector<float> m_pings;
	unsigned int m_currentPing;

public:
	FrequencyCount(const int nrPings);

	void ping();

	float frequency();
	float period();
};


class FrequencyTime {
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