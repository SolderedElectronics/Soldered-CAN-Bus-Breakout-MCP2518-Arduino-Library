/*
 * sys.h
 *
 * Created: 02-10-2018 13:07:18
 *  Author: JMR_2
 */

#ifndef SYS_H_
#define SYS_H_

// Auxiliary Macros
#define CONCAT(A, B) A##B
#define PIN(x)       CONCAT(PIN, x)
#define PORT(x)      CONCAT(PORT, x)
#define DDR(x)       CONCAT(DDR, x)

#include <avr/pgmspace.h>

#define FLASH const PROGMEM flash

template <typename T> class flash
{
  private:
    const T data;

  public:
    // normal constructor
    constexpr flash(T _data) : data(_data)
    {
    }
    // default constructor
    constexpr flash() : data(0)
    {
    }

    operator T() const
    {
        switch (sizeof(T))
        {
        case 1:
            return pgm_read_byte(&data);
        case 2:
            return pgm_read_word(&data);
        case 4:
            return pgm_read_dword(&data);
        }
    }
};

#ifndef F_CPU
#define F_CPU 16000000U
#endif

constexpr unsigned int baud(unsigned long b)
{
    return F_CPU / (b * 8.0) - 0.5;
}

namespace SYS
{
void init(void);
void setLED(void);
void clearLED(void);
} // namespace SYS

#endif /* SYS_H_ */