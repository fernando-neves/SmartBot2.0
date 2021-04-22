#ifndef TIMER_CHRONOMETER_H
#define TIMER_CHRONOMETER_H

/* THIS PROJECT INCLUDES */
#include <helper/singleton.h>

/* C++ INCLUDES */
#include <chrono>

namespace wpp
{
    namespace time_ns
    {
        class timer_chronometer
        {
            std::chrono::high_resolution_clock::time_point start_time;
        public:
            timer_chronometer()
            {
                reset();
            }

            uint64_t elapsed_minutes() const
            {
                return (uint32_t)(std::chrono::duration_cast<std::chrono::minutes>(
                    std::chrono::high_resolution_clock::now() - start_time)).count();

            }

            uint64_t elapsed_seconds() const
            {
                return (uint32_t)(std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::high_resolution_clock::now() - start_time)).count();
            }

            uint64_t elapsed_milliseconds() const
            {
                return (uint32_t)(std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - start_time)).count();
            }

            uint64_t elapsed_microseconds() const
            {
                return (uint32_t)(std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start_time)).count();
            }

            void reset()
            {
                start_time = std::chrono::high_resolution_clock::now();
            }

            void sub_time(const int64_t time)
            {
                start_time = start_time - std::chrono::milliseconds(time);
            }

            int32_t time_left_from_milliseconds(const uint32_t milliseconds) const
            {

                return (int32_t)milliseconds - (int32_t)elapsed_milliseconds();
            }
        };
    }
}
#endif // TIMER_CHRONOMETER_H
