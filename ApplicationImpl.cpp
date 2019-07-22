//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationImpl.h"
//#include <QDebug>
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CApplication::StandardApplicationCallback
//---------------------------------------------------------------------------

WNDPROC CApplicationImpl::StandardApplicationCallback = nullptr;
//---------------------------------------------------------------------------
// Definition of CApplication
//---------------------------------------------------------------------------

CApplicationImpl::CApplicationImpl()
  : CBase() {
  hookApplicationToCallback();
  substituteApplicationCallback();
}
//---------------------------------------------------------------------------

void CApplicationImpl::hookApplicationToCallback() {
  SetWindowLongPtr(getHandle(), GWLP_USERDATA, (LONG_PTR)this);
}
//---------------------------------------------------------------------------

void CApplicationImpl::substituteApplicationCallback() {
  StandardApplicationCallback =
    (WNDPROC)SetWindowLongPtrA(getHandle(),
                               GWLP_WNDPROC,
                               (LONG_PTR)StaticApplicationCallback);
}
//---------------------------------------------------------------------------

CApplicationImpl* CApplicationImpl::getApplicationPtr(HWND hWnd) {
  return
    reinterpret_cast<CApplicationImpl*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}
//---------------------------------------------------------------------------

LRESULT CALLBACK CApplicationImpl::StaticApplicationCallback(
  HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static CApplicationImpl* pApplication = getApplicationPtr(hWnd);
  if (message == WM_INPUT)
    pApplication->handleInput(lParam);

  return CallWindowProc( StandardApplicationCallback,
                         hWnd,
                         message,
                         wParam,
                         lParam);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
