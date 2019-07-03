#ifndef TIMEDFILELOGGER_H
#define TIMEDFILELOGGER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/BasicFileLogger.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CTimedFileLogger
//---------------------------------------------------------------------------

class CTimedFileLogger : public NSLibrary::CBasicFileLogger {
public:
  CTimedFileLogger(const std::wstring& fileName = kDefaultFileName);
  static constexpr const wchar_t* kDefaultFileName = L"Log.txt";
private:
  inline void makeFirstEntry();
  inline void makeLogHeader(std::wstring* pLogHeader) const;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TIMEDFILELOGGER_H
