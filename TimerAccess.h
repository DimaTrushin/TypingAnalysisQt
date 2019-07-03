#ifndef TIMERACCESS_H
#define TIMERACCESS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Timer.h"
#include "Library/AnyGlobalAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CMainTimer
//---------------------------------------------------------------------------

class CMainTimer {};
//---------------------------------------------------------------------------
// Declaration of CTimerAccessible
//---------------------------------------------------------------------------

class CTimerAccessible
  : public NSLibrary::CAnyGlobalAccessible<CTimer, CMainTimer> {
};
//---------------------------------------------------------------------------
// Declaration of CTimerAccess
//---------------------------------------------------------------------------

class CTimerAccess
  : public NSLibrary::CAnyGlobalAccess<CTimer, CMainTimer> {
};
//---------------------------------------------------------------------------
// Declaration of CTimerInitializer
//---------------------------------------------------------------------------

class CTimerInitializer
  : public NSLibrary::CAnyGlobalInitializer<CTimer, CMainTimer> {
  using CBase = NSLibrary::CAnyGlobalInitializer<CTimer, CMainTimer>;
public:
  using CBase::CBase;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TIMERACCESS_H
