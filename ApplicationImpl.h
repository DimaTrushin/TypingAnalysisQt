#ifndef APPLICATIONIMPL_H
#define APPLICATIONIMPL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationLocals.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CApplication
//---------------------------------------------------------------------------

class CApplicationImpl : public CApplicationLocals {
  Q_OBJECT
  using CBase = CApplicationLocals;
public:
  CApplicationImpl();
  ~CApplicationImpl() = default;
private:
  void hookApplicationToCallback();
  void substituteApplicationCallback();
  static CApplicationImpl* getApplicationPtr(HWND hWnd);
  static LRESULT CALLBACK StaticApplicationCallback(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
  static WNDPROC StandardApplicationCallback;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPLICATIONIMPL_H
