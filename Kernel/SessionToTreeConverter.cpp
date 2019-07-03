//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "SessionToTreeConverter.h"
#include "TextDataTree.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CPressedKeys
//---------------------------------------------------------------------------

CPressedKeys::CPressedKeys() {
  CBase::reserve(kDefaultReserveSize);
}
//---------------------------------------------------------------------------
void CPressedKeys::releaseBefore( microseconds Time,
                                  NSKeyboard::CKeyboardState* KeyboardState) {
  while (isTopAlreadyReleased(Time)) {
    KeyboardState->ReleaseKey(top()->getVKCode());
    pop_heap();
  }
}
//---------------------------------------------------------------------------

bool CPressedKeys::isTopAlreadyReleased(microseconds Time) const {
  return !empty() && top()->getReleasingTime() <= Time;
}
//---------------------------------------------------------------------------
// Definitions of CSessionToTreeConverter
//---------------------------------------------------------------------------

void CSessionToTreeConverter::convert(const CSession& source,
                                      CTextDataTree* target) {
  initializeConverter(source);
  target->clear();

  for ( auto currentKey = source.begin();
        currentKey != source.end();
        ++currentKey) {
    releaseBefore(currentKey->getPressingTime());
    PressedKeys.push_heap(currentKey);

    if (currentKey->isSymbolOrSpace() ||
        currentKey->isEnter())
      handleSymbol(source, currentKey, target);

    if (currentKey->isBackspace())
      handleBackspace(target);
    // I am ignoring the dead keys now!

    changeCurrentKeyboardState(currentKey);
  }
  target->setMistakeInformation();
}
//---------------------------------------------------------------------------

void CSessionToTreeConverter::initializeConverter(
  const CSession& Session) {
  initializeKeyboard(Session);
  PressedKeys.clear();
}
//---------------------------------------------------------------------------

void CSessionToTreeConverter::initializeKeyboard(
  const CSession& Session) {
  CurrentKeyboardState.setKeyboardState(Session.getKeyboardState());
}
//---------------------------------------------------------------------------

void CSessionToTreeConverter::releaseBefore(microseconds Time) {
  PressedKeys.releaseBefore(Time, &CurrentKeyboardState);
}
//---------------------------------------------------------------------------

// This function takes into account the current keyboard state
wchar_t CSessionToTreeConverter::getSymbol(
  const CSession::const_iterator& index) const {
  return index->getKeySymbol(CurrentKeyboardState);
}
//---------------------------------------------------------------------------

void CSessionToTreeConverter::handleBackspace(CTextDataTree* target) const {
  if (isAnyCtrlPressed())
    target->deleteLastBlock();
  else
    target->deleteLastData();
}
//---------------------------------------------------------------------------

void CSessionToTreeConverter::handleSymbol(
  const CSession& source,
  const CSession::const_iterator& KeyIterator,
  CTextDataTree* target) const {
  target->addData(CTextData(getSymbol(KeyIterator),
                            source.getResponseTime(KeyIterator),
                            &(*KeyIterator)));
}
//---------------------------------------------------------------------------

bool CSessionToTreeConverter::isAnyCtrlPressed() const {
  for (const auto& pressedKey : PressedKeys)
    if (pressedKey->isAnyCtrl())
      return true;
  return false;
}
//---------------------------------------------------------------------------

void CSessionToTreeConverter::changeCurrentKeyboardState(
  const CSession::const_iterator& KeyIterator) {
  CurrentKeyboardState.PressKey(KeyIterator->getVKCode());
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
