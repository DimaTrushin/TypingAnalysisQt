//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "CapitalWithDependenciesFiller.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition CCapitalWithDependenciesBeingPressed
//---------------------------------------------------------------------------

void CCapitalWithDependenciesBeingPressed::increasePrintedDependencies() {
  for (auto& Key : *this)
    Key->increasePrintedDependencies();
}
//---------------------------------------------------------------------------

void CCapitalWithDependenciesBeingPressed::increaseDeletedDependencies() {
  for (auto& Key : *this)
    Key->increaseDeletedDependencies();
}
//---------------------------------------------------------------------------
// Definition CShiftsWithDependenciesFiller
//---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::fill(
  const CSession& Session,
  const CTextDataTree& TextTree,
  CShiftsData* pShifts) {
  if (!initialize(Session, TextTree, pShifts))
    return;

  while (isThereSymbolAndShift(TextTree, pShifts)) {
    setPressedShifts(pShifts);
    if (itCurrentSymbol_->isAffectedByShift())
      updateDependencies();
    ++itCurrentSymbol_;
  }
}
//---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::fillWithoutDependencies(
  const CSession& Session, CShiftsData* pShifts) {
  pShifts->clear();
  for(auto itSymbol = Session.begin();
      itSymbol != Session.end();
      ++itSymbol)
    if (itSymbol->isAnyShift())
      pShifts->push_back(itSymbol);
}
//---------------------------------------------------------------------------

bool CShiftsWithDependenciesFiller::isThereSymbolAndShift(
  const CTextDataTree& TextTree, CShiftsData* pShifts) const {
  return itCurrentSymbol_ != TextTree.endText(ETextMode::Full) &&
         (!PressedShifts_.empty() || itNextShift_ != pShifts->end());
}
//---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::updateDependencies() {
  if (itCurrentSymbol_->isAnyPrinted())
    PressedShifts_.increasePrintedDependencies();
  else if (itCurrentSymbol_->isAnyDeleted())
    PressedShifts_.increaseDeletedDependencies();
  else
    // We are in the root!
    return;
}
//---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::setPressedShifts(CShiftsData* pShifts) {
  pressCurrentShifts(pShifts);
  removeReleasedShifts();
}
//---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::pressCurrentShifts(CShiftsData* pShifts) {
  while(itNextShift_ != pShifts->end() &&
        !(itNextShift_->
          getIterator()->
          isPressedAfter(itCurrentSymbol_->getPressingTime()))) {
    PressedShifts_.push_back(itNextShift_);
    ++itNextShift_;
  }
}
//---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::removeReleasedShifts() {
  auto itPressedShift = PressedShifts_.begin();
  while (itPressedShift != PressedShifts_.end()) {
    if ((*itPressedShift)->
        getIterator()->
        isReleasedBefore(itCurrentSymbol_->getPressingTime())) {
      itPressedShift = PressedShifts_.erase(itPressedShift);
      continue;
    }
    ++itPressedShift;
  }
}
//---------------------------------------------------------------------------

bool CShiftsWithDependenciesFiller::initialize(
  const CSession& Session,
  const CTextDataTree& TextTree,
  CShiftsData* pShifts) {
  fillWithoutDependencies(Session, pShifts);
  if (pShifts->empty())
    return false;
  // Now there are shifts
  itCurrentSymbol_ = TextTree.beginText(ETextMode::Full);
  itNextShift_ = pShifts->begin();
  if (!PressedShifts_.empty())
    PressedShifts_.clear();
  return true;
}
//---------------------------------------------------------------------------
// Definition CCapslocksWithDependenciesFiller
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::fill(
  const CSession& Session,
  const CTextDataTree& TextTree,
  CCapslocksData* pCapslocks) {
  if (!initialize(Session, TextTree, pCapslocks))
    return;
  while ( itCurrentSymbol_ != TextTree.endText(ETextMode::Full) &&
          itCurrentCapslock_ != pCapslocks->end()) {
    setNearestCapslock(pCapslocks);
    if (itCurrentSymbol_->isAffectedByCapsLock())
      updateDependencies();
    ++itCurrentSymbol_;
  }
  correctDependencies(pCapslocks);
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::correctDependencies(
  CCapslocksData* pCapslocks) {
  correctDependencies(ETextMode::Full, pCapslocks);
  correctDependencies(ETextMode::Printed, pCapslocks);
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::correctDependencies(
  ETextMode TextMode, CCapslocksData* pCapslocks) {
  auto itCapslock = pCapslocks->begin();
  while (itCapslock != pCapslocks->end()) {
    correctDependenciesOfOneCapslock(TextMode, itCapslock, pCapslocks);
    ++itCapslock;
  }
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::correctDependenciesOfOneCapslock(
  ETextMode TextMode,
  CCapslocksData::iterator itCapslock,
  CCapslocksData* pCapslocks) {
  if (needToUseCorrector(TextMode, itCapslock, pCapslocks)) {

    CCorrector CapslockCorrector(itCapslock);
    CapslockCorrector.setToCorrectionPlace(TextMode, pCapslocks);
    if (!CapslockCorrector.needCorrection())
      return;

    unsigned int NumberOfDependencies =
      itCapslock->getNumberOfDependentKeys(TextMode);
    itCapslock->setNumberOfDependentKeys(TextMode, 0);
    if (CapslockCorrector.getPosition() != pCapslocks->end())
      CapslockCorrector.
      getPosition()->
      increaseNumberOfDependentKeysBy(TextMode, NumberOfDependencies);
  }
}
//---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::needToUseCorrector(
  ETextMode TextMode,
  CCapslocksData::iterator itCapslock,
  CCapslocksData* pCapslocks) const {
  if (itCapslock->getNumberOfDependentKeys(TextMode) == 0)
    return false;
  if (itCapslock == pCapslocks->begin())
    return false;
  auto itPrevious = itCapslock;
  --itPrevious;
  if (itPrevious->getNumberOfDependentKeys(TextMode) == 0)
    return true;
  return false;
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::setNearestCapslock(
  CCapslocksData* pCapslocks) {
  auto itNextCapslock = itCurrentCapslock_;
  ++itNextCapslock;
  while (true) {
    if (itNextCapslock == pCapslocks->end())
      return;
    if (itNextCapslock->
        getIterator()->
        isPressedAfter(itCurrentSymbol_->getPressingTime()))
      return;
    itCurrentCapslock_ = itNextCapslock;
    ++itNextCapslock;
  }
}
//---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::initialize(
  const CSession& Session,
  const CTextDataTree& TextTree,
  CCapslocksData* pCapslocks) {
  fillWithoutDependencies(Session, pCapslocks);
  if (pCapslocks->empty())
    return false;
  itCurrentSymbol_ = TextTree.beginText(ETextMode::Full);
  itCurrentCapslock_ = pCapslocks->begin();
  moveCurrentSymbolAfterCurrentCapslock(TextTree);
  return true;
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::
moveCurrentSymbolAfterCurrentCapslock(const CTextDataTree& TextTree) {
  while(itCurrentSymbol_ != TextTree.endText(ETextMode::Full) &&
        itCurrentCapslock_->
        getIterator()->
        isPressedAfter(itCurrentSymbol_->getPressingTime())) {
    ++itCurrentSymbol_;
  }
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::updateDependencies() {
  if (itCurrentSymbol_->isAnyPrinted())
    itCurrentCapslock_->increasePrintedDependencies();
  else if (itCurrentSymbol_->isAnyDeleted())
    itCurrentCapslock_->increaseDeletedDependencies();
  else
    // We are in the root!
    return;
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::fillWithoutDependencies(
  const CSession& Session, CCapslocksData* pCapslocks) {
  pCapslocks->clear();
  auto itSymbol = Session.cbegin();
  while (itSymbol != Session.end()) {
    if (itSymbol->isCapslock())
      pCapslocks->push_back(itSymbol);
    ++itSymbol;
  }
}
//---------------------------------------------------------------------------
// Definitions of CCapslocksWithDependenciesFiller::CCorrector
//---------------------------------------------------------------------------

CCapslocksWithDependenciesFiller::CCorrector::CCorrector(
  const CCapslocksData::iterator& itInitialPosition)
  : itCorrectionPosition_(itInitialPosition),
    NumberOfSkippedCapslocks_(0) {
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::
CCorrector::setToCorrectionPlace(
  ETextMode TextMode, CCapslocksData* pCapitals) {
  if (itCorrectionPosition_ == pCapitals->begin())
    return;
  moveLeft();

  while (itCorrectionPosition_ != pCapitals->begin()) {
    if(!needToMove(TextMode))
      return;
    moveLeft();
  }

  if(needToMove(TextMode))
    makeExceptionalMoveLeft(pCapitals);
}
//---------------------------------------------------------------------------

CCapslocksData::iterator&
CCapslocksWithDependenciesFiller::CCorrector::getPosition() {
  return itCorrectionPosition_;
}
//---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::CCorrector::needCorrection() const {
  return (NumberOfSkippedCapslocks_ % 2) == 0;
}
//---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::
CCorrector::needToMove(ETextMode TextMode) const {
  if (itCorrectionPosition_->getNumberOfDependentKeys(TextMode) == 0)
    return true;
  return false;
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::CCorrector::moveLeft() {
  --itCorrectionPosition_;
  ++NumberOfSkippedCapslocks_;
}
//---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::CCorrector::makeExceptionalMoveLeft(
  CCapslocksData* pCapitals) {
  itCorrectionPosition_ = pCapitals->end();
  ++NumberOfSkippedCapslocks_;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
