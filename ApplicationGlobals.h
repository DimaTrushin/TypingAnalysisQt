#ifndef APPLICATIONGLOBALS_H
#define APPLICATIONGLOBALS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Qt/MainWindow.h"
#include "TimerAccess.h"
#include "ThreadPoolAccess.h"
//---------------------------------------------------------------------------
namespace NSApplication {

//---------------------------------------------------------------------------
// Declaration of CApplicationGlobals
//---------------------------------------------------------------------------

class CApplicationGlobals : public NSQt::CMainWindow {
  Q_OBJECT
  using CBase = NSQt::CMainWindow;
public:
  CApplicationGlobals();
private:
  CTimerInitializer MainTimer;
  CThreadPoolInitializer MainThreadPool;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPLICATIONGLOBALS_H
