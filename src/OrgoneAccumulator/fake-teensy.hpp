#pragma once

#include <cinttypes>

using boolean = bool;

class Bounce
{
public:
   Bounce(uint8_t pin, unsigned long /*interval_millis*/)
   {
      this->pin = pin;
   }
   // Updates the pin
   // Returns 1 if the state changed
   // Returns 0 if the state did not change
   int update()
   {
      return {};
   }
   
   // The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.
   bool risingEdge()
   {
      return {};
   }
   // The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off.
   bool fallingEdge()
   {
      return {};
   }

protected:
   uint8_t state = 0;
   uint8_t pin = 0;
   uint8_t stateChanged = 0;
};


class IntervalTimer
{
public:
   IntervalTimer() = default;
   ~IntervalTimer() = default;
   
   bool begin(void (* funct)(), unsigned int microseconds)
   {
      return true;
   }
   
   void end()
   {
   }
};

struct EEPROMClass
{
   
   uint8_t read(int idx)
   { return 1; }
   void write(int idx, uint8_t val)
   { }
   void update(int idx, uint8_t val)
   { }
};

static EEPROMClass EEPROM __attribute__ ((unused));

struct SerialClass
{
   void begin(int)
   { }
   int available()
   { return 0; }
   void read()
   { }
   void write(int)
   { }
};

static SerialClass Serial __attribute__ ((unused));

void yield(void)
{ }

void delay(uint32_t msec)
{ }

const static uint8_t A0  = 0;
const static uint8_t A1  = 1;
const static uint8_t A2  = 2;
const static uint8_t A3  = 3;
const static uint8_t A4  = 4;
const static uint8_t A5  = 5;
const static uint8_t A6  = 6;
const static uint8_t A7  = 7;
const static uint8_t A8  = 8;
const static uint8_t A9  = 9;
const static uint8_t A10 = 10;
const static uint8_t A11 = 11;
const static uint8_t A12 = 12;
const static uint8_t A13 = 13;
const static uint8_t A14 = 14;
const static uint8_t A15 = 15;
const static uint8_t A16 = 16;
const static uint8_t A17 = 17;

const static uint8_t HIGH           = 1;
const static uint8_t LOW            = 0;
const static uint8_t INPUT          = 0;
const static uint8_t OUTPUT         = 1;
const static uint8_t INPUT_PULLUP   = 2;
const static uint8_t INPUT_PULLDOWN = 3;
const static uint8_t CHANGE         = 4;
const static uint8_t EXTERNAL       = 5;

void pinMode(uint8_t pin, uint8_t mode)
{ }
void analogWrite(uint8_t pin, int val)
{ }
uint32_t analogWriteRes(uint32_t bits)
{ return {}; }

int analogRead(uint8_t pin)
{ return {}; }
void analogReference(uint8_t type)
{ }

void digitalWrite(uint8_t pin, uint8_t val)
{ }
uint8_t digitalRead(uint8_t pin)
{ return {}; }
static inline uint8_t digitalReadFast(uint8_t pin)
{ return {}; }
static inline void digitalWriteFast(uint8_t pin, uint8_t val)
{ }

static inline void analogReadResolution(unsigned int bits)
{ }
void analogReadAveraging(unsigned int num)
{ }
static inline uint32_t analogWriteResolution(uint32_t bits)
{ return {}; }
void analogWriteFrequency(uint8_t pin, float frequency)
{ }

void attachInterrupt(uint8_t pin, void (* function)(void), int mode)
{ }

#define PORT_PCR_MUX(n)         ((uint32_t)(((n) & 7) << 8))   // Pin Mux Control
#define PORT_PCR_PE         ((uint32_t)0x00000002)      // Pull Enable
#define portConfigRegister(pin) ((volatile uint32_t *)(pin))

#define abs(x) ({ \
  typeof(x) _x = (x); \
  (_x > 0) ? _x : -_x; \
})

#define constrain(amt, low, high) ({ \
  typeof(amt) _amt = (amt); \
  typeof(low) _low = (low); \
  typeof(high) _high = (high); \
  (_amt < _low) ? _low : ((_amt > _high) ? _high : _amt); \
})

#include <utility>
// https://forum.pjrc.com/threads/44596-Teensyduino-1-37-Beta-2-(Arduino-1-8-3-support)?p=145150&viewfull=1#post145150
template <class A, class B>
constexpr auto min(A&& a, B&& b) -> decltype(a < b ? std::forward<A>(a) : std::forward<B>(b))
{
   return a < b ? std::forward<A>(a) : std::forward<B>(b);
}
template <class A, class B>
constexpr auto max(A&& a, B&& b) -> decltype(a < b ? std::forward<A>(a) : std::forward<B>(b))
{
   return a >= b ? std::forward<A>(a) : std::forward<B>(b);
}

static uint32_t seed;

void randomSeed(uint32_t newseed)
{
   if (newseed > 0)
      seed = newseed;
}

void srandom(unsigned int newseed)
{
   seed = newseed;
}

int32_t random(void)
{
   int32_t hi, lo, x;
   
   // the algorithm used in avr-libc 1.6.4
   x = seed;
   if (x == 0)
      x = 123459876;
   hi = x / 127773;
   lo = x % 127773;
   x  = 16807 * lo - 2836 * hi;
   if (x < 0)
      x += 0x7FFFFFFF;
   seed = x;
   return x;
}

uint32_t random(uint32_t howbig)
{
   if (howbig == 0)
      return 0;
   return random() % howbig;
}

int32_t random(int32_t howsmall, int32_t howbig)
{
   if (howsmall >= howbig)
      return howsmall;
   int32_t diff = howbig - howsmall;
   return random(diff) + howsmall;
}

//using boolean = bool;

#include <type_traits>
// when the input number is an integer type, do all math as 32 bit signed long
template <class T, class A, class B, class C, class D>
long map(T _x, A _in_min, B _in_max, C _out_min, D _out_max, typename std::enable_if<std::is_integral<T>::value>::type* = 0)
{
   long x = _x, in_min = _in_min, in_max = _in_max, out_min = _out_min, out_max = _out_max;
   // Arduino's traditional algorithm
   //return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
   // st42's suggestion: https://github.com/arduino/Arduino/issues/2466#issuecomment-69873889
   // more conversation:
   // https://forum.pjrc.com/threads/44503-map()-function-improvements
   if ((in_max - in_min) > (out_max - out_min))
   {
      return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
   }
   else
   {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
   }
}
// when the input is a float or double, do all math using the input's type
template <class T, class A, class B, class C, class D>
T map(T x, A in_min, B in_max, C out_min, D out_max, typename std::enable_if<std::is_floating_point<T>::value>::type* = 0)
{
   return (x - (T)in_min) * ((T)out_max - (T)out_min) / ((T)in_max - (T)in_min) + (T)out_min;
}

#define FASTRUN

static inline uint32_t millis(void)
{ return {}; }

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
