#ifndef SESSIONITERATOR_H
#define SESSIONITERATOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "StringFormat.h"
#include "SessionToTreeConverter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSessionIterator
//---------------------------------------------------------------------------

class CSessionIterator {
  using CVKCode = NSKeyboard::CVKCode;
  using CVKCodeType = CVKCode::CVKCodeType;
public:
  CSessionIterator(const CSession& Session);
  ~CSessionIterator() = default;

  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  CVKCodeType getVKCode() const;
  bool isValid() const;
  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  void setNext();
  microseconds getPhysicalResponseTime() const;
private:
  void releaseBefore(microseconds Time);
  void pressCurrentKeyOnKeyboardState(
    const CSession::const_iterator& KeyIterator);

  const CSession* pSession_;
  CSession::const_iterator CurrentPosition_;
  CPressedKeys PressedKeys_;
  NSKeyboard::CKeyboardState CurrentKeyboardState_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SESSIONITERATOR_H
