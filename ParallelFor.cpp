//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ParallelFor.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Definition LoopWorker
//---------------------------------------------------------------------------------

LoopWorker::LoopWorker(size_t Begin, size_t End, ILoopWorker* pLoopWorker)
  : begin_(Begin),
    end_(End),
    ptrLoopWorker_(pLoopWorker) {
}
//---------------------------------------------------------------------------------

void LoopWorker::execute() {
  for (size_t index = begin_; index < end_; ++index)
    ptrLoopWorker_->execute(index);
}
//---------------------------------------------------------------------------------
// Definition CParallelFor
//---------------------------------------------------------------------------------

void CParallelFor::operator() (size_t begin,
                               size_t end,
                               size_t chunk,
                               ILoopWorker* pLoopWorker,
                               CThreadPool* pPool) {
  makeLoopWorkers(begin, end, chunk, pLoopWorker);
  submitLoopWorkers(pPool);
  pPool->wait();
}
//---------------------------------------------------------------------------------

void CParallelFor::makeLoopWorkers(size_t begin,
                                   size_t end,
                                   size_t chunk,
                                   ILoopWorker* pLoopWorker) {
  LoopWorkers_.clear();
  size_t numberOfFullChunks = (end - begin) / chunk;
  size_t numberOfChunks = numberOfFullChunks;
  if ((end - begin) % chunk != 0)
    ++numberOfChunks;
  LoopWorkers_.reserve(numberOfChunks);

  for (size_t index = 0; index < numberOfFullChunks; ++index) {
    size_t chunkStart = begin + index * chunk;
    size_t chunkEnd = chunkStart + chunk;
    LoopWorkers_.emplace_back(LoopWorker(chunkStart,
                                         chunkEnd,
                                         pLoopWorker));
  }
  if (numberOfFullChunks != numberOfChunks)
    LoopWorkers_.emplace_back(LoopWorker(begin + numberOfFullChunks * chunk,
                                         end,
                                         pLoopWorker));
}
//---------------------------------------------------------------------------------

void CParallelFor::submitLoopWorkers(CThreadPool* pPool) {
  for (auto& loopWorker : LoopWorkers_)
    pPool->submit(&loopWorker);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
