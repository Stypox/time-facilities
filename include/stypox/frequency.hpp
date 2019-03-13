#ifndef _STYPOX_FREQUENCY_HPP_
#define _STYPOX_FREQUENCY_HPP_

#include <vector>

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