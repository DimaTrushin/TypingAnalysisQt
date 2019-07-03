//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "BasicFileLogger.h"
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CBasicFileLogger
//---------------------------------------------------------------------------

CBasicFileLogger::CBasicFileLogger(const std::wstring& fileName)
  : oFileStream_( fileName,
                  std::wofstream::out | std::wofstream::app) {
  assert(isDefined());
}
//---------------------------------------------------------------------------

void CBasicFileLogger::Log(const std::wstring& Text) {
  assert(isDefined());
  std::lock_guard<std::mutex> blocker(guardian_);
  oFileStream_ << Text;
}
//---------------------------------------------------------------------------

bool CBasicFileLogger::isDefined() const {
  return oFileStream_.is_open();
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
