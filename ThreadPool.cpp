//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ThreadPool.h"
#include <exception> //pch
#include <cassert> //pch
#include <thread> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Definition of CallBack Functions
//---------------------------------------------------------------------------------

VOID CALLBACK WorkerCallback( PTP_CALLBACK_INSTANCE,
                              PVOID Parameter,
                              PTP_WORK Work) {
  IWorker* pWorker = static_cast<IWorker*>(Parameter);
  pWorker->execute();
  // TO DO
  // not sure about using this function here
  CloseThreadpoolWork(Work);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolBase
//---------------------------------------------------------------------------------

CThreadPoolBase::CThreadPoolBase()
  : Pool_(CreateThreadpool(nullptr)) {
  if (Pool_ == nullptr)
    throw std::exception ("CreateThreadpool fails\n");
}
//---------------------------------------------------------------------------------

CThreadPoolBase::~CThreadPoolBase() {
  assert(Pool_ != nullptr);
  CloseThreadpool(Pool_);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithEnvironmentBase
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironmentBase::CThreadPoolwithEnvironmentBase() {
  InitializeThreadpoolEnvironment(&Environment_);
}
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironmentBase::~CThreadPoolwithEnvironmentBase() {
  DestroyThreadpoolEnvironment(&Environment_);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithEnvironment
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironment::CThreadPoolwithEnvironment() {
  SetThreadpoolCallbackPool(&Environment_, Pool_);
}
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironment::~CThreadPoolwithEnvironment() {
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithCleanupGroupBase
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroupBase::CThreadPoolwithCleanupGroupBase()
  : CleanupGroup_(CreateThreadpoolCleanupGroup()) {
  if (CleanupGroup_ == nullptr)
    throw std::exception("CreateThreadpoolCleanupGroup fails\n");
}
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroupBase::~CThreadPoolwithCleanupGroupBase() {
  assert(CleanupGroup_ != nullptr);
  CloseThreadpoolCleanupGroup(CleanupGroup_);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithCleanupGroup
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroup::CThreadPoolwithCleanupGroup() {
  SetThreadpoolCallbackCleanupGroup(&Environment_, CleanupGroup_, nullptr);
}
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroup::~CThreadPoolwithCleanupGroup() {
  assert(CleanupGroup_ != nullptr);
  // If this part of CThreadPool is destroyed, there must be no
  // tasks running. Hence, we do not wait any running tasks.
  CloseThreadpoolCleanupGroupMembers(CleanupGroup_, true, nullptr);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPool
//---------------------------------------------------------------------------------

CThreadPool::CThreadPool()
  : ThreadMaximum_(getOptimalAmountOfThreads()),
    ThreadMinimum_(getOptimalAmountOfThreads()) {
  initialize();
}
//---------------------------------------------------------------------------------

CThreadPool::CThreadPool(size_t MaximalNumberOfThreads,
                         size_t MinimalNumberOfThreads)
  : ThreadMaximum_(MaximalNumberOfThreads),
    ThreadMinimum_(MinimalNumberOfThreads) {
  initialize();
}
//---------------------------------------------------------------------------------

CThreadPool::~CThreadPool() {
  assert(CleanupGroup_ != nullptr);
  // If we destroy CThreadPool, we wait until all running tasks
  // are over.
  CloseThreadpoolCleanupGroupMembers(CleanupGroup_, false, nullptr);
}
//---------------------------------------------------------------------------------

void CThreadPool::submit(IWorker* pWorker) {
  PTP_WORK work = CreateThreadpoolWork( WorkerCallback,
                                        pWorker,
                                        &Environment_);
  if (work == nullptr)
    throw std::exception("CreateThreadpoolWork fails\n");
  SubmitThreadpoolWork(work);
}
//---------------------------------------------------------------------------------

void CThreadPool::wait() {
  CloseThreadpoolCleanupGroupMembers(CleanupGroup_, false, nullptr);
}
//---------------------------------------------------------------------------------

void CThreadPool::setNumberOfThreads(size_t maximum, size_t minimum) {
  assert(maximum >= minimum);
  assert(maximum > 0);
  SetThreadpoolThreadMaximum(Pool_, maximum);
  ThreadMaximum_ = maximum;
  BOOL result = SetThreadpoolThreadMinimum(Pool_, minimum);
  if (result == FALSE)
    throw std::exception("SetThreadpoolThreadMinimum failed\n");
  ThreadMinimum_ = minimum;
}
//---------------------------------------------------------------------------

size_t CThreadPool::getThreadMaximum() const {
  return ThreadMaximum_;
}
//---------------------------------------------------------------------------

size_t CThreadPool::getThreadMinimum() const {
  return ThreadMinimum_;
}
//---------------------------------------------------------------------------

size_t CThreadPool::getOptimalAmountOfThreads() {
  size_t numberOfThreads = std::thread::hardware_concurrency();
  if (numberOfThreads == 0)
    numberOfThreads = kDefaultNumberOfThreads;
  return numberOfThreads;
}
//---------------------------------------------------------------------------

void CThreadPool::initialize() {
  assert(ThreadMaximum_ >= ThreadMinimum_);
  assert(ThreadMaximum_ > 0);
  SetThreadpoolThreadMaximum(Pool_, ThreadMaximum_);
  BOOL result = SetThreadpoolThreadMinimum(Pool_, ThreadMinimum_);
  if (result == FALSE)
    throw std::exception("SetThreadpoolThreadMinimum failed\n");
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
