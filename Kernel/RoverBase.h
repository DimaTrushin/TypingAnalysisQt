#ifndef ROVERBASE_H
#define ROVERBASE_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <queue> //pch
#include "AnyUIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CFirstPressedHeap
//---------------------------------------------------------------------------


using CFirstPressedHeap = std::priority_queue<
                          CAnyUIterator,
                          std::vector<CAnyUIterator>,
                          CAnyUIterator::CFirstPressedOnTop>;
//---------------------------------------------------------------------------
// Declaration of CRoverBase
//---------------------------------------------------------------------------

class CRoverBase : protected CFirstPressedHeap {
public:
  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  void setNext();
  using CFirstPressedHeap::empty;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // ROVERBASE_H
