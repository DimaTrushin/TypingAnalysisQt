//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "RoverBase.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CRoverBase
//---------------------------------------------------------------------------

ETextFormat CRoverBase::getTextFormat() const {
  return top()->getTextFormat();
}
//---------------------------------------------------------------------------

CFormatStructure CRoverBase::getTextFormatStructure() const {
  return top()->getTextFormatStructure();
}
//---------------------------------------------------------------------------

wchar_t CRoverBase::getSymbol() const {
  return top()->getSymbol();
}
//---------------------------------------------------------------------------

void CRoverBase::setNext() {
  auto currentIterator = std::move(top());
  pop();
  currentIterator->setNext();
  if (currentIterator->isValid())
    push(currentIterator);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
