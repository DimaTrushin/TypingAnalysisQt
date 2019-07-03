#ifndef BASICFILELOGGER_H
#define BASICFILELOGGER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <string> //pch
#include <mutex> //pch
#include <boost/filesystem/fstream.hpp> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CBasicFileLogger
//---------------------------------------------------------------------------

class CBasicFileLogger {
public:
  CBasicFileLogger(const std::wstring& fileName);
  void Log(const std::wstring& Text);
protected:
  bool isDefined() const;
private:
  std::mutex guardian_;
  boost::filesystem::wofstream oFileStream_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // BASICFILELOGGER_H
