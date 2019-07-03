#ifndef SESSIONTOTREECONVERTER_H
#define SESSIONTOTREECONVERTER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/VectorHeapWithAccess.h"
// TO DO
// included into header because of dependent declaration of interators
// that is CSession::const_iterator and CSession::iterator
#include "Session.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Forward Declaration
//---------------------------------------------------------------------------

class CTextDataTree;
//---------------------------------------------------------------------------
// Declaration of CPressedKeysHeap
//---------------------------------------------------------------------------

using CPressedKeysHeap = NSLibrary::CVectorHeapWithAccess<
                         CSession::const_iterator,
                         CSession::CFirstReleasedOnTop>;
//---------------------------------------------------------------------------
// Declaration of CPressedKeys
//---------------------------------------------------------------------------

class CPressedKeys : protected CPressedKeysHeap {
  using CBase = CPressedKeysHeap;
public:
  CPressedKeys();
  void releaseBefore( microseconds Time,
                      NSKeyboard::CKeyboardState* KeyboardState);
  using CBase::push_heap;
  using CBase::begin;
  using CBase::end;
  using CBase::clear;
private:
  inline bool isTopAlreadyReleased(microseconds Time) const;
  static constexpr const size_t kDefaultReserveSize = 10;
};
//---------------------------------------------------------------------------
// Declaration of CSessionToTreeConverter
//---------------------------------------------------------------------------

class CSessionToTreeConverter {
public:
  void convert( const CSession& source,
                CTextDataTree* target);

private:
  void initializeConverter(const CSession& Session);
  void initializeKeyboard(const CSession& Session);
  void releaseBefore(microseconds Time);

  wchar_t getSymbol(const CSession::const_iterator& index) const;

  void handleBackspace(CTextDataTree* target) const;
  void handleSymbol(const CSession& source,
                    const CSession::const_iterator& KeyIterator,
                    CTextDataTree* target) const;
  bool isAnyCtrlPressed() const;
  void changeCurrentKeyboardState(const CSession::const_iterator& KeyIterator);
  CPressedKeys PressedKeys;
  NSKeyboard::CKeyboardState CurrentKeyboardState;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SESSIONTOTREECONVERTER_H
