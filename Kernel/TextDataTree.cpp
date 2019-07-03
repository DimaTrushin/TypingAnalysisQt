//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TextDataTree.h"
#include "TextSymbol.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CTextDataTree
//---------------------------------------------------------------------------

CTextDataTree::CTextDataTree()
  : CBase(CTextData()),
    FinalElement_(beginFromRoot()) {
}
//---------------------------------------------------------------------------

CTextDataTree::CTextDataTree(const CTextDataTree& Tree)
  : CBase(Tree),
    FinalElement_(Tree.FinalElement_) {
  setFinalElementHost();
  setMistakeRoutesHosts();
  //setFinalElement(Tree);
  //reSetMistakeRoutes();
}
//---------------------------------------------------------------------------

CTextDataTree::CTextDataTree(CTextDataTree&& Tree)
  : CBase(std::move(Tree)),
    FinalElement_(std::move(Tree.FinalElement_)) {
  setFinalElementHost();
  setMistakeRoutesHosts();
}
//---------------------------------------------------------------------------

CTextDataTree& CTextDataTree::operator=(const CTextDataTree& Tree) {
  return *this = CTextDataTree(Tree);
}
//---------------------------------------------------------------------------

CTextDataTree& CTextDataTree::operator=(CTextDataTree&& Tree) {
  CBase::operator=(std::move(Tree));
  FinalElement_ = Tree.FinalElement_;
  setFinalElementHost();
  setMistakeRoutesHosts();
  return *this;
}
//---------------------------------------------------------------------------

void CTextDataTree::clear() {
  destroyExceptRoot();
  getRootNode().Data_.MistakeRoutes_.clear();
  FinalElement_ = beginFromRoot();
}
//---------------------------------------------------------------------------

void CTextDataTree::addData(const CTextData& TextData) {
  FinalElement_.addLastChild(TextData);
  ++FinalElement_;
}
//---------------------------------------------------------------------------

void CTextDataTree::addData(CTextData&& TextData) {
  FinalElement_.addLastChild(TextData);
  ++FinalElement_;
}
//---------------------------------------------------------------------------

void CTextDataTree::deleteLastData() {
  if(FinalElement_.isRoot())
    return;
  FinalElement_->setSymbolStatus(ESymbolStatus::DeletedSymbolAccidental);
  --FinalElement_;
}
//---------------------------------------------------------------------------

void CTextDataTree::deleteLastBlock() {
  deleteLastTextDelimiterBlock();
  deleteLastSymbolBlock();
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfPlacesWithDeletion() const {
  if (size() == 1)
    return 0;
  CConstTextIterator index;
  index = beginFromRoot();
  size_t places = 0;
  while (index != FinalElement_) {
    if (index.getNumberOfChildren() > 1)
      places += 1;
    ++index;
  }
  if (index.getNumberOfChildren() > 0)
    places += 1;
  return places;
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfDeletionSeries() const {
  if (size() == 1)
    return 0;
  CConstTextIterator index;
  index = beginFromRoot();
  size_t places = 0;
  while (index != FinalElement_) {
    places += index.getNumberOfChildren() - 1;
    ++index;
  }
  places += index.getNumberOfChildren();
  return places;
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfDeletedSymbols() const {
  size_t numberOfDeletedSymbols = 0;
  for ( CConstTextIterator itCurrentSymbol = beginFromRoot();
        itCurrentSymbol != FinalElement_;
        ++itCurrentSymbol)
    for ( auto child = itCurrentSymbol.FirstChild();
          child != itCurrentSymbol.LastChild();
          ++child)
      numberOfDeletedSymbols += child.getSizeOfSubTree();
  numberOfDeletedSymbols += FinalElement_.getSizeOfSubTree() - 1;
  return numberOfDeletedSymbols;
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfReturnPoints() const {
  if (FinalElement_.isThereChild())
    return beginFromRoot().getNumberOfLeaves();
  return beginFromRoot().getNumberOfLeaves() - 1;
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getTotalNumberOfSymbols() const {
  return size();
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getTextLength(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return getFullTextLength();
  assert(TextMode == ETextMode::Printed);
  return getPrintedTextLength();
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getDeletionSeriesLengthSupremum() const {
  size_t lengthsup = 0;
  for ( CConstTextIterator itCurrentSymbol = beginFromRoot();
        itCurrentSymbol != FinalElement_;
        ++itCurrentSymbol)
    for ( auto child = itCurrentSymbol.FirstChild();
          child != itCurrentSymbol.LastChild();
          ++child)
      lengthsup = std::max(lengthsup, child.getLengthOfSubTree());
  lengthsup = std::max(lengthsup, FinalElement_.getLengthOfSubTree() - 1);
  return lengthsup;
}
//---------------------------------------------------------------------------

// symbols deleted at the end are assumed to be mistakes
size_t CTextDataTree::getNumberOfMistakePlaces() const {
  size_t mistakePlaces = 0;
  for ( CConstTextIterator index = beginFromRoot();
        index != endPrintedText();
        ++index)
    if (!index->MistakeRoutes_.empty())
      ++mistakePlaces;
  return mistakePlaces;
}
//---------------------------------------------------------------------------

// symbols deleted at the end are assumed to be mistakes
size_t CTextDataTree::getNumberOfMistakeRoutes() const {
  size_t mistakes = 0;
  for ( CConstTextIterator index = beginFromRoot();
        index != endPrintedText();
        ++index)
    mistakes += index->MistakeRoutes_.size();
  return mistakes;
}
//---------------------------------------------------------------------------

// symbols deleted at the end are assumed to be mistakes
size_t CTextDataTree::getMistakeRoutesLengthSupremum() const {
  size_t lengthSupremum = 0;
  for ( CConstTextIterator index = beginFromRoot();
        index != endPrintedText();
        ++index)
    for ( auto itMistakeRoute = index->MistakeRoutes_.cbegin();
          itMistakeRoute != index->MistakeRoutes_.end();
          ++itMistakeRoute)
      lengthSupremum = std::max(lengthSupremum,
                                itMistakeRoute->getLengthOfSubTree());
  return lengthSupremum;
}
//---------------------------------------------------------------------------

bool CTextDataTree::isTextEmpty(ETextMode TextMode) const {
  if (getTextLength(TextMode) == 0)
    return true;
  return false;
}
//---------------------------------------------------------------------------

microseconds CTextDataTree::getFirstPressingTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return 0;
  return beginText(TextMode)->getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CTextDataTree::getLastPressingTime(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return getLastFullTextPressingTime();
  assert(TextMode == ETextMode::Printed);
  return getLastPrintedTextPressingTime();
}
//---------------------------------------------------------------------------

microseconds CTextDataTree::getTextDurationTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return 0;
  return getLastPressingTime(TextMode) - getFirstPressingTime(TextMode);
}
//---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator
CTextDataTree::beginText(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return beginFullText();
  assert(TextMode == ETextMode::Printed);
  return beginPrintedText();
}
//---------------------------------------------------------------------------

CTextDataTree::CBasicIterator
CTextDataTree::beginText(ETextMode TextMode) {
  if (TextMode == ETextMode::Full)
    return beginFullText();
  assert(TextMode == ETextMode::Printed);
  return beginPrintedText();
}
//---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator
CTextDataTree::endText(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return endFullText();
  assert(TextMode == ETextMode::Printed);
  return endPrintedText();
}
//---------------------------------------------------------------------------

CTextDataTree::CBasicIterator
CTextDataTree::endText(ETextMode TextMode) {
  if (TextMode == ETextMode::Full)
    return endFullText();
  assert(TextMode == ETextMode::Printed);
  return endPrintedText();
}
//---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator CTextDataTree::beginFromRoot() const {
  return begin();
}
//---------------------------------------------------------------------------

CTextDataTree::CBasicIterator CTextDataTree::beginFromRoot() {
  return begin();
}
//---------------------------------------------------------------------------

void CTextDataTree::setMistakeInformation() {
  setMistakeRoutes();
  setMistakeSymbols();
  setRequiredDeleted();
}
//---------------------------------------------------------------------------

void CTextDataTree::reSetMistakeInformation() {
  clearMistakeRoutes();
  setMistakeInformation();
}
//---------------------------------------------------------------------------

microseconds CTextDataTree::getLastPrintedTextPressingTime() const {
  if (isTextEmpty(ETextMode::Printed))
    return 0;
  return FinalElement_->getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CTextDataTree::getLastFullTextPressingTime() const {
  if (isTextEmpty(ETextMode::Full))
    return 0;
  return (--endPreOrder())->getPressingTime();
}
//---------------------------------------------------------------------------

CTextDataTree::CConstTextIterator CTextDataTree::beginPrintedText() const {
  CConstTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
//---------------------------------------------------------------------------

CTextDataTree::CTextIterator CTextDataTree::beginPrintedText() {
  CTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
//---------------------------------------------------------------------------

CTextDataTree::CConstFullTextIterator CTextDataTree::beginFullText() const {
  CConstFullTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
//---------------------------------------------------------------------------

CTextDataTree::CFullTextIterator CTextDataTree::beginFullText() {
  CFullTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
//---------------------------------------------------------------------------

CTextDataTree::CConstTextIterator CTextDataTree::endPrintedText() const {
  CConstTextIterator TextEnding = FinalElement_;
  return ++TextEnding;
}
//---------------------------------------------------------------------------

CTextDataTree::CTextIterator CTextDataTree::endPrintedText() {
  CTextIterator TextEnding = FinalElement_;
  return ++TextEnding;
}
//---------------------------------------------------------------------------

CTextDataTree::CConstFullTextIterator CTextDataTree::endFullText() const {
  return endPreOrder();
}
//---------------------------------------------------------------------------

CTextDataTree::CFullTextIterator CTextDataTree::endFullText() {
  return endPreOrder();
}
//---------------------------------------------------------------------------

void CTextDataTree::setFinalElement(const CTextDataTree& Tree) {
  size_t difference = Tree.FinalElement_ -
                      CConstTextIterator(Tree.beginFromRoot());
  FinalElement_ = beginFromRoot();
  FinalElement_ += difference;
}
//---------------------------------------------------------------------------

void CTextDataTree::setFinalElementHost() {
  FinalElement_.changeHost(this);
}
//---------------------------------------------------------------------------

void CTextDataTree::setMistakeRoutesHosts() {
  for(CTextIterator currentPosition = beginFromRoot();
      currentPosition != FinalElement_;
      ++currentPosition)
    for (auto& Route : currentPosition->MistakeRoutes_)
      Route.changeHost(this);
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getPrintedTextLength() const {
  return endPrintedText() - beginPrintedText();
}
//---------------------------------------------------------------------------

size_t CTextDataTree::getFullTextLength() const {
  return size() - 1;
}
//---------------------------------------------------------------------------

void CTextDataTree::deleteLastTextDelimiterBlock() {
  while (FinalElement_->isTextDelimiter())
    deleteLastData();
}
//---------------------------------------------------------------------------

void CTextDataTree::deleteLastSymbolBlock() {
  while (FinalElement_->isSymbol())
    deleteLastData();
}
//---------------------------------------------------------------------------

void CTextDataTree::clearMistakeRoutes() {
  for ( CTextIterator Node = beginFromRoot();
        Node != endPrintedText();
        ++Node)
    Node->MistakeRoutes_.clear();
}
//---------------------------------------------------------------------------

void CTextDataTree::reSetMistakeRoutes() {
  clearMistakeRoutes();
  setMistakeRoutes();
}
//---------------------------------------------------------------------------

void CTextDataTree::setMistakeRoutes() {
  for ( CTextIterator currentPosition = beginFromRoot();
        currentPosition != FinalElement_;
        ++currentPosition) {
    reAssignMistakeRoutes(currentPosition);
    assignNewMistakeRoutes(currentPosition);
  }
  assignMistakeRoutesForFinalElement();
}
//---------------------------------------------------------------------------

void CTextDataTree::reAssignMistakeRoutes(
  const CTextIterator& currentPosition) {
  auto itMistakeRoute = currentPosition->MistakeRoutes_.begin();
  CTextIterator next = currentPosition;
  ++next;
  while (itMistakeRoute != currentPosition->MistakeRoutes_.end()) {
    if (next->getSymbol() == (*itMistakeRoute)->getSymbol()) {
      // we did not make a mistake in the next symbol
      // need to pass mistake routes to the node with the next symbol
      if (itMistakeRoute->isThereChild()) {
        // if there are mistake routes
        reAssignChildernTo(*itMistakeRoute, &next);
      }
      // remove itMistakeRoute from the current node of the tree
      itMistakeRoute =
        currentPosition->MistakeRoutes_.erase(itMistakeRoute);
      continue;
    }
    ++itMistakeRoute;
  }
}
//---------------------------------------------------------------------------

void CTextDataTree::assignNewMistakeRoutes(
  const CTextIterator& currentPosition) {
  CTextIterator currentNode(currentPosition);
  auto itMistakeRoute = currentNode.FirstChild();

  CTextIterator nextNode = currentPosition;
  ++nextNode;
  while (itMistakeRoute != currentNode.LastChild()) {
    if (nextNode->getSymbol() == itMistakeRoute->getSymbol()) {
      // If the symbol is the same, we did NOT make a mistake in the next symbol
      // if there are children, send them to the nextNode's MistakeRoutes
      if (itMistakeRoute.isThereChild()) {
        reAssignChildernTo(itMistakeRoute, &nextNode);
      }
    } else {
      // if the symbol is NOT the same, we made a mistake in the next symbol
      // need to write the current route to the MistakeRoutes of the currentNode
      currentPosition->MistakeRoutes_.push_back(itMistakeRoute);
    }
    ++itMistakeRoute;
  }
}
//---------------------------------------------------------------------------

void CTextDataTree::assignMistakeRoutesForFinalElement() {
  if (!FinalElement_.isThereChild())
    return;
  for ( auto itMistakeRoute = FinalElement_.FirstChild();
        itMistakeRoute != FinalElement_.LastChild();
        ++itMistakeRoute)
    FinalElement_->MistakeRoutes_.push_back(itMistakeRoute);
  FinalElement_->MistakeRoutes_.push_back(FinalElement_.LastChild());
}
//---------------------------------------------------------------------------

void CTextDataTree::reAssignChildernTo( const CTextIterator& source,
                                        CTextIterator* target) {
  for ( auto itChild = source.FirstChild();
        itChild != source.LastChild();
        ++itChild)
    (*target)->MistakeRoutes_.push_back(itChild);
  (*target)->MistakeRoutes_.push_back(source.LastChild());
}
//---------------------------------------------------------------------------

void CTextDataTree::setRequiredDeleted() {
  for ( CTextIterator currentPosition = beginFromRoot();
        currentPosition != endPrintedText();
        ++currentPosition)
    for ( auto itMistakeRoute = currentPosition->MistakeRoutes_.begin();
          itMistakeRoute != currentPosition->MistakeRoutes_.end();
          ++itMistakeRoute)
      setRequiredDeletedFrom(*itMistakeRoute);
}
//---------------------------------------------------------------------------

void CTextDataTree::setMistakeSymbols() {
  for ( CTextIterator itCurrentSymbol = beginFromRoot();
        itCurrentSymbol != FinalElement_;
        ++itCurrentSymbol)
    if (!itCurrentSymbol->MistakeRoutes_.empty())
      itCurrentSymbol.LastChild()->setSymbolStatus(ESymbolStatus::MistakeSymbol);
}
//---------------------------------------------------------------------------

void CTextDataTree::setRequiredDeletedFrom(
  const CSiblingIterator& currentNode) {
  currentNode->setSymbolStatus(ESymbolStatus::DeletedSymbolRequired);

  if (!currentNode.isThereChild())
    return;
  for ( auto itChild = currentNode.FirstChild();
        itChild != currentNode.LastChild();
        ++itChild)
    setRequiredDeletedFrom(itChild);
  setRequiredDeletedFrom(currentNode.LastChild());
}
//---------------------------------------------------------------------------
// Definitions of CTextData
//---------------------------------------------------------------------------

CTextData::CTextData()
  : Symbol_(CTextSymbol::RootSymbol),
    ResponseTime_(0),
    pKeyEvent_(nullptr),
    SymbolStatus_(ESymbolStatus::RootSymbol) {
}
//---------------------------------------------------------------------------

CTextData::CTextData( wchar_t Symbol,
                      microseconds ResponseTime,
                      const CKeyEvent* pKeyEvent,
                      ESymbolStatus SymbolStatus)
  : Symbol_(Symbol),
    ResponseTime_(ResponseTime),
    pKeyEvent_(pKeyEvent),
    SymbolStatus_(SymbolStatus) {
}
//---------------------------------------------------------------------------

bool CTextData::isAffectedByShift() const {
  return isSymbol();
}
//---------------------------------------------------------------------------

bool CTextData::isAffectedByCapsLock() const {
  return isAffectedByShift();
}
//---------------------------------------------------------------------------

bool CTextData::isTextDelimiter() const {
  return  (pKeyEvent_ != nullptr) &&
          (pKeyEvent_->isSpacebar() || pKeyEvent_->isEnter());
}
//---------------------------------------------------------------------------

bool CTextData::isSymbol() const {
  return (pKeyEvent_ != nullptr) && pKeyEvent_->isSymbolKey();
}
//---------------------------------------------------------------------------

bool CTextData::isAnyDeleted() const {
  return  SymbolStatus_ == ESymbolStatus::DeletedSymbolAccidental ||
          SymbolStatus_ == ESymbolStatus::DeletedSymbolRequired;
}
//---------------------------------------------------------------------------

bool CTextData::isAnyPrinted() const {
  return  SymbolStatus_ == ESymbolStatus::TextSymbol ||
          SymbolStatus_ == ESymbolStatus::MistakeSymbol;
}
//---------------------------------------------------------------------------

microseconds CTextData::getPressingTime() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CTextData::getReleasingTime() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getReleasingTime();
}
//---------------------------------------------------------------------------

microseconds CTextData::getResponseTime() const {
  return ResponseTime_;
}
//---------------------------------------------------------------------------

microseconds CTextData::getDurationTime() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getDurationTime();
}
//---------------------------------------------------------------------------

wchar_t CTextData::getSymbol() const {
  return Symbol_;
}
//---------------------------------------------------------------------------

ESymbolStatus CTextData::getSymbolStatus() const {
  return SymbolStatus_;
}
//---------------------------------------------------------------------------

void CTextData::setSymbolStatus(ESymbolStatus newStatus) {
  SymbolStatus_ = newStatus;
}
//---------------------------------------------------------------------------

CTextData::CVKCodeType CTextData::getVKCode() const {
  if (pKeyEvent_ == nullptr)
    return NSKeyboard::CVKCode::InvalidCode;
  return pKeyEvent_->getVKCode();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
