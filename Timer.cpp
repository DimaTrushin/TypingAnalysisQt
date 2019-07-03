//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Timer.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CTimer
//---------------------------------------------------------------------------

CTimer::CTimer() {
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&startingTime);
}
//---------------------------------------------------------------------------

microseconds CTimer::getTime() const {
  LARGE_INTEGER currentTime;
  QueryPerformanceCounter(&currentTime);
  currentTime.QuadPart -= startingTime.QuadPart;
  currentTime.QuadPart *= microsecondsInOneSecond;
  currentTime.QuadPart /= frequency.QuadPart;
  return currentTime.QuadPart;
}
//---------------------------------------------------------------------------

milliseconds CTimer::MicroSecondsToMilliSeconds(microseconds Time) {
  return  static_cast<double>(Time) /
          static_cast<double>(microsecondsInOneMillisecond);
}
//---------------------------------------------------------------------------

seconds CTimer::MicroSecondsToSeconds(microseconds Time) {
  return  static_cast<double>(Time) /
          static_cast<double>(microsecondsInOneSecond);
}
//---------------------------------------------------------------------------

minutes CTimer::MicroSecondsToMinutes(microseconds Time) {
  return  static_cast<double>(Time) /
          static_cast<double>(microsecondsInOneMinute);
}
//---------------------------------------------------------------------------

hours CTimer::MicroSecondsToHours(microseconds Time) {
  return  static_cast<double>(Time) /
          static_cast<double>(microsecondsInOneHour);
}
//---------------------------------------------------------------------------

roundminutes CTimer::MicroSecondsToRoundMinutes(microseconds Time) {
  return static_cast<roundminutes>(Time / microsecondsInOneMinute);
}
//---------------------------------------------------------------------------

roundhours CTimer::MicroSecondsToRoundHours(microseconds Time) {
  return static_cast<roundhours>(Time / microsecondsInOneHour);
}
//---------------------------------------------------------------------------

microseconds CTimer::MillisecondsToMicroseconds(milliseconds Time) {
  return static_cast<microseconds>(Time * microsecondsInOneMillisecond);
}
//---------------------------------------------------------------------------

microseconds CTimer::SecondsToMicroseconds(milliseconds Time) {
  return static_cast<microseconds>(Time * microsecondsInOneSecond);
}
//---------------------------------------------------------------------------

microseconds CTimer::MinutesToMicroseconds(roundminutes Time) {
  return static_cast<microseconds>(Time) * microsecondsInOneMinute;
}
//---------------------------------------------------------------------------

microseconds CTimer::HoursToMicroseconds(roundhours Time) {
  return static_cast<microseconds>(Time) * microsecondsInOneHour;
}
//---------------------------------------------------------------------------

symbolsPerMinute CTimer::convertTimeToSpeed(microseconds Time) {
  return  static_cast<double>(microsecondsInOneMinute) /
          static_cast<double>(Time);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
