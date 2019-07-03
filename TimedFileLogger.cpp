//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TimedFileLogger.h"
#include "TimerAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CTimerdFileLogger
//---------------------------------------------------------------------------

CTimedFileLogger::CTimedFileLogger(const std::wstring& fileName)
  : CBasicFileLogger(fileName) {
  makeFirstEntry();
}
//---------------------------------------------------------------------------

void CTimedFileLogger::makeFirstEntry() {
  std::wstring LogHeader;
  makeLogHeader(&LogHeader);
  Log(LogHeader);
}
//---------------------------------------------------------------------------

void CTimedFileLogger::makeLogHeader(std::wstring* pLogHeader) const {
  std::wstring& LogHeader = *pLogHeader;
  // TO DO
  // must be a unique way to deal with strings
  LogHeader = L"gLog (" +
              std::to_wstring(
                CTimer::MicroSecondsToMilliSeconds(
                  CTimerAccess()->getTime())) +
              L"):\n";
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
