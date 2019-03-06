#ifndef _STYPOX_CLOCK_H_
#define _STYPOX_CLOCK_H_

#include <chrono>

namespace stypox {	
template <typename T = float>
class Clock {
public:
	using type = T;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

public:
	Clock();

	type now();

	type restart();
};


template <typename T = float>
class Chronometer {
public:
	using type = T;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	bool m_stopped;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_pause;

public:
	Chronometer();

	type now();
	bool stopped();
	bool paused();

	type restart();
	type stop();
	type pause();
};


template <typename T>
inline Clock<T>::Clock() :
	m_start{std::chrono::high_resolution_clock::now()} {}

template <typename T>
inline auto Clock<T>::now() -> Clock<T>::type {
	return std::chrono::duration<type>{std::chrono::high_resolution_clock::now() - m_start}.count();
}

template <typename T>
inline auto Clock<T>::restart() -> Clock<T>::type {
	type oldNow = now();
	m_start = std::chrono::high_resolution_clock::now();
	return oldNow;
}



template <typename T>
inline Chronometer<T>::Chronometer() :
	m_start{std::chrono::high_resolution_clock::now()}, m_stopped{false},
	m_pause{std::chrono::seconds{-1}} {}

template <typename T>
inline auto Chronometer<T>::now() -> Chronometer<T>::type {
	using namespace std::chrono;
	if (m_stopped)
		return duration<type>{m_start.time_since_epoch()}.count();
	else if (m_pause < time_point<high_resolution_clock>()) // not paused < 0;
		return duration<type>{high_resolution_clock::now() - m_start}.count();
	else // paused >= 0
		return duration<type>{m_pause.time_since_epoch()}.count();
}
template <typename T>
bool Chronometer<T>::stopped() {
	using namespace std::chrono;
	return m_stopped;
}
template <typename T>
bool Chronometer<T>::paused() {
	using namespace std::chrono;
	return m_pause >= time_point<high_resolution_clock>{}; // >= 0
}

template <typename T>
inline auto Chronometer<T>::restart() -> Chronometer<T>::type {
	using namespace std::chrono;
	type oldNow = now();
	m_start = high_resolution_clock::now();
	m_pause = time_point<high_resolution_clock>{seconds{-1}};
	return oldNow;
}
template <typename T>
inline auto Chronometer<T>::stop() -> Chronometer<T>::type {
	using namespace std::chrono;
	if (!m_stopped) {
		m_start = time_point<high_resolution_clock>{high_resolution_clock::now().time_since_epoch() - m_start.time_since_epoch()};
		m_stopped = true;
	}
	return duration<type>{m_start.time_since_epoch()}.count();
}
template <typename T>
inline auto Chronometer<T>::pause() -> Chronometer<T>::type {
	using namespace std::chrono;
	if (m_pause < time_point<high_resolution_clock>{}) { // not yet paused < 0 -> pause
		m_pause = high_resolution_clock::now();
		return duration<type>{m_pause.time_since_epoch()}.count();
	}
	else { // already paused >= 0 -> set not paused
		m_start = time_point<high_resolution_clock>{high_resolution_clock::now().time_since_epoch() - m_pause.time_since_epoch() + m_start.time_since_epoch()};
		type now = duration<type>{m_pause.time_since_epoch()}.count();
		m_pause = time_point<high_resolution_clock>{seconds{-1}}; // -1 < 0 -> not paused
		return now;
	}
}
} // namespace stypox

#endif // _STYPOX_CLOCK_H_
