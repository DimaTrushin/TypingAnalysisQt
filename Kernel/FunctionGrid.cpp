//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "FunctionGrid.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CFunctionGridBase
//---------------------------------------------------------------------------

CFunctionGridBase::CFunctionGridBase(double start, double step)
  : Start_(start), Step_(step) {
  assert(Step_ > 0);
}
//---------------------------------------------------------------------------

double CFunctionGridBase::getPoint(const const_iterator& position) const {
  return getStart() + static_cast<double>(position - begin()) * getStep();
}
//---------------------------------------------------------------------------

double CFunctionGridBase::getPoint(size_t position) const {
  return getStart() + getStep() * static_cast<double>(position);
}
//---------------------------------------------------------------------------

double CFunctionGridBase::getStart() const {
  return Start_;
}
//---------------------------------------------------------------------------

double CFunctionGridBase::getStep() const {
  return Step_;
}
//---------------------------------------------------------------------------

double CFunctionGridBase::getArea() const {
  if (size() < 2)
    return 0.0;
  double Area = 0.0;
  const_iterator itCurrent = begin();
  const_iterator itNext = itCurrent;
  ++itNext;
  while(itNext != end()) {
    Area += (*itCurrent + *itNext) * getStep() / 2.0;
    ++itCurrent;
    ++itNext;
  }
  return Area;
}
//---------------------------------------------------------------------------

// TO DO
// need to refactor the code of the function it is too huge
// Cannot make it parallel without using concurrent vector since I use push_back
void CFunctionGridBase::fillRoughMaxMinPairContainer(
  CRoughMaxMinPairContainer *target) const {
  target->clear();
  if (size() < 2)
    return;
  // exceptional case: the maximum is the first element
  const_iterator itCurrent = begin();
  const_iterator itNext = itCurrent;
  ++itNext;
  if (isFirstExtremum<EExtremalPointType::Maximum>(*itCurrent, *itNext)) {
    const_iterator itMax = itCurrent;
    const_iterator itMin;
    findNextMin(itCurrent, &itMin);
    if (itMin == end())
      return;
    itCurrent = itMin;
    // Here we must have getPoint(itMax) = 0
    // Therefore I do not subtract Step_ to stay in positive values
    target->
    push_back(CRoughMaxMinPair(
                CInterval(getPoint(itMax), getPoint(itMax) + getStep()),
                CInterval(getPoint(itMin) - getStep(), getPoint(itMin) + getStep())));
  }
  // General case: the maximum is not first
  while (itCurrent != end()) {
    const_iterator itMax;
    findNextMax(itCurrent, &itMax);
    if (itMax == end())
      return;
    itCurrent = itMax;
    const_iterator itMin;
    findNextMin(itCurrent, &itMin);
    if (itMin == end())
      return;
    itCurrent = itMin;
    target->
    push_back(CRoughMaxMinPair(
                CInterval(getPoint(itMax) - getStep(), getPoint(itMax) + getStep()),
                CInterval(getPoint(itMin) - getStep(), getPoint(itMin) + getStep())));
  }
}
//---------------------------------------------------------------------------

CInterval CFunctionGridBase::findRoughRoot() const {
  if (empty())
    return CInterval(0.0, 0.0);
  const_iterator currentRoot = begin();
  for (auto index = begin(); index != end(); ++index)
    if (std::fabs(*currentRoot) > std::fabs(*index))
      currentRoot = index;
  return CInterval(getPoint(currentRoot) - getStep(),
                   getPoint(currentRoot) + getStep());
}
//---------------------------------------------------------------------------

void CFunctionGridBase::findNextMax(const const_iterator& itCurrent,
                                    const_iterator* pItMax) const {
  findNextExtremum<EExtremalPointType::Maximum>(itCurrent, pItMax);
}
//---------------------------------------------------------------------------

void CFunctionGridBase::findNextMin(const const_iterator& itCurrent,
                                    const_iterator* pItMin) const {
  findNextExtremum<EExtremalPointType::Minimum>(itCurrent, pItMin);
}
//---------------------------------------------------------------------------

template<EExtremalPointType PointType>
void CFunctionGridBase::findNextExtremum(
  const const_iterator& itCurrent, const_iterator* pItExtremum) const {
  const_iterator itPrevious = itCurrent;
  const_iterator& itExtremum = *pItExtremum = itPrevious;
  ++itExtremum;
  if (itExtremum == end())
    return;
  const_iterator itNext = itExtremum;
  ++itNext;
  while (itNext != end()) {
    if (isExtremum<PointType>(itExtremum, itPrevious, itNext))
      return;
    ++itPrevious;
    ++itExtremum;
    ++itNext;
  }
  if (!isFirstExtremum<PointType>(*itExtremum, *itPrevious))
    itExtremum = end();
}
//---------------------------------------------------------------------------

template<EExtremalPointType PointType>
bool CFunctionGridBase::isExtremum( const const_iterator& extremum,
                                    const const_iterator& previous,
                                    const const_iterator& next) const {
  return  isFirstExtremum<PointType>(*extremum, *previous) &&
          isFirstExtremum<PointType>(*extremum, *next);
}
//---------------------------------------------------------------------------
// Definition of CFunctionGridBase::CFGParallelFor
//---------------------------------------------------------------------------

void CFunctionGridBase::CFGParallelFor::operator()(
  size_t begin,
  size_t end,
  size_t samples,
  ILoopWorker* pLoopWorker,
  CThreadPool* pPool) {
  size_t chunk = getChunk(begin, end, samples, pPool);
  CParallelFor::operator()(begin, end, chunk, pLoopWorker, pPool);
}
//---------------------------------------------------------------------------

size_t CFunctionGridBase::CFGParallelFor::getChunk(
  size_t begin,
  size_t end,
  size_t samples,
  CThreadPool* pPool) const {
  size_t threadBoundary = (end - begin) / pPool->getThreadMaximum();
  if (samples == 0)
    ++samples;
  size_t empiricalBoundary = (threadCoefficient * (end - begin)) / samples;
  return std::max<size_t>(std::min(threadBoundary, empiricalBoundary), 1);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
