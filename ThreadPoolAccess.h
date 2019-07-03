#ifndef THREADPOOLACCESS_H
#define THREADPOOLACCESS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ThreadPool.h"
#include "Library/AnyGlobalAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CMainThreadPool
//---------------------------------------------------------------------------

class CMainThreadPool {};
//---------------------------------------------------------------------------
// Declaration of CThreadPoolAccessible
//---------------------------------------------------------------------------

class CThreadPoolAccessible
  : public NSLibrary::CAnyGlobalAccessible<CThreadPool, CMainThreadPool> {
};
//---------------------------------------------------------------------------
// Declaration of CThreadPoolAccess
//---------------------------------------------------------------------------

class CThreadPoolAccess
  : public NSLibrary::CAnyGlobalAccess<CThreadPool, CMainThreadPool> {
};
//---------------------------------------------------------------------------
// Declaration of CThreadPoolInitializer
//---------------------------------------------------------------------------

class CThreadPoolInitializer
  : public NSLibrary::CAnyGlobalInitializer<CThreadPool, CMainThreadPool> {
  using CBase = NSLibrary::CAnyGlobalInitializer<CThreadPool, CMainThreadPool>;
public:
  using CBase::CBase;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // THREADPOOLACCESS_H
