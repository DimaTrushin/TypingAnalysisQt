#ifndef TIMER_H
#define TIMER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <windows.h> //pch
#include "TimeDefinitions.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CTimer
//---------------------------------------------------------------------------

class CTimer {
public:
  CTimer();

  CTimer(const CTimer&) = delete;
  CTimer(CTimer&&) = delete;
  CTimer& operator=(const CTimer&) = delete;
  CTimer& operator=(CTimer&&) = delete;

  // returns the time in microseconds from the moment of creation of the Timer
  microseconds getTime() const;

  // Conversions from microseconds
  static milliseconds MicroSecondsToMilliSeconds(microseconds Time);
  static seconds MicroSecondsToSeconds(microseconds Time);
  static minutes MicroSecondsToMinutes(microseconds Time);
  static hours MicroSecondsToHours(microseconds Time);
  static roundminutes MicroSecondsToRoundMinutes(microseconds Time);
  static roundhours MicroSecondsToRoundHours(microseconds Time);
  // Conversions to microseconds
  static microseconds MillisecondsToMicroseconds(milliseconds Time);
  static microseconds SecondsToMicroseconds(milliseconds Time);
  static microseconds MinutesToMicroseconds(roundminutes Time);
  static microseconds HoursToMicroseconds(roundhours Time);
  // Conversion time to speed
  static symbolsPerMinute convertTimeToSpeed(microseconds Time);
  // Constants
  static constexpr microseconds microsecondsInOneMillisecond = 1000;
  static constexpr microseconds microsecondsInOneSecond =   1000000;
  static constexpr microseconds microsecondsInOneMinute =  60000000;
  static constexpr microseconds microsecondsInOneHour =  3600000000;

private:
  LARGE_INTEGER startingTime;
  LARGE_INTEGER frequency;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TIMER_H
