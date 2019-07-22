#ifndef THREADPOOL_H
#define THREADPOOL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <Windows.h> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Declaration of IWorker
//---------------------------------------------------------------------------------

class IWorker {
public:
  virtual ~IWorker() = default;
  virtual void execute() = 0;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolBase
//---------------------------------------------------------------------------------

class CThreadPoolBase {
public:
  CThreadPoolBase();
  CThreadPoolBase(const CThreadPoolBase&) = delete;
  CThreadPoolBase& operator=(const CThreadPoolBase&) = delete;
protected:
  ~CThreadPoolBase();
  PTP_POOL Pool_;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithEnvironmentBase
//---------------------------------------------------------------------------------

class CThreadPoolwithEnvironmentBase {
public:
  CThreadPoolwithEnvironmentBase();
  CThreadPoolwithEnvironmentBase(
    const CThreadPoolwithEnvironmentBase&) = delete;
  CThreadPoolwithEnvironmentBase& operator=(
    const CThreadPoolwithEnvironmentBase&) = delete;
protected:
  ~CThreadPoolwithEnvironmentBase();
  TP_CALLBACK_ENVIRON Environment_;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithEnvironment
//---------------------------------------------------------------------------------

class CThreadPoolwithEnvironment : protected CThreadPoolBase,
  protected CThreadPoolwithEnvironmentBase {
public:
  CThreadPoolwithEnvironment();
protected:
  ~CThreadPoolwithEnvironment();
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithCleanupGroupBase
//---------------------------------------------------------------------------------

class CThreadPoolwithCleanupGroupBase {
public:
  CThreadPoolwithCleanupGroupBase();
  CThreadPoolwithCleanupGroupBase(
    const CThreadPoolwithCleanupGroupBase&) = delete;
  CThreadPoolwithCleanupGroupBase& operator=(
    const CThreadPoolwithCleanupGroupBase&) = delete;
protected:
  ~CThreadPoolwithCleanupGroupBase();
  PTP_CLEANUP_GROUP CleanupGroup_;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithCleanupGroup
//---------------------------------------------------------------------------------

class CThreadPoolwithCleanupGroup : protected CThreadPoolwithCleanupGroupBase,
  protected CThreadPoolwithEnvironment {
public:
  CThreadPoolwithCleanupGroup();
protected:
  ~CThreadPoolwithCleanupGroup();
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPool
//---------------------------------------------------------------------------------

class CThreadPool : protected CThreadPoolwithCleanupGroup {
public:
  CThreadPool();
  CThreadPool(size_t MaximalNumberOfThreads,
              size_t MinimalNumberOfThreads);
  ~CThreadPool();
  void submit(IWorker* pWorker);
  void wait();

  void setNumberOfThreads(size_t maximum, size_t minimum);
  size_t getThreadMaximum() const;
  size_t getThreadMinimum() const;
protected:
  static constexpr size_t kDefaultMaximalNumberOfThreads = 4;
  static constexpr size_t kDefaultMinimalNumberOfThreads = 1;
  static constexpr size_t kDefaultNumberOfThreads =
    kDefaultMaximalNumberOfThreads;
private:
  static size_t getOptimalAmountOfThreads();
  void initialize();
  size_t ThreadMaximum_;
  size_t ThreadMinimum_;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // THREADPOOL_H
