#ifndef SYMBOLITERATOR_H
#define SYMBOLITERATOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TextDataTree.h"
#include "StringFormat.h"
#include "Keyboard/VKCode.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Enum
//---------------------------------------------------------------------------

enum class ESymbolIteratorStart : unsigned char {
  FromRoot, FromTextBegin
};
//---------------------------------------------------------------------------
// Declaration of CSymbolIterator
//---------------------------------------------------------------------------

class CSymbolIterator {
  using CVKCode = NSKeyboard::CVKCode;
  using CCKCodeType = CVKCode::CVKCodeType;
public:
  CSymbolIterator(const CTextDataTree& TextTree,
                  ETextMode mode,
                  ESymbolIteratorStart BeginFrom);
  ~CSymbolIterator() = default;

  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  CCKCodeType getVKCode() const;
  bool isValid() const;
  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  void setNext();
  microseconds getPhysicalResponseTime() const;

  ESymbolStatus getSymbolStatus() const;

private:
  inline void setNextFull();
  inline void setNextNonFull();

  // TO DO
  // These functions should probably return size_t values
  // since the values are never negative
  // plus it becomes compatible with the data type of any container size
  inline unsigned int getDepth() const;
  inline unsigned int getAccidentalDeletedDepth() const;
  inline unsigned int getAccidentalDeletedDepth(
    const CTextDataTree::CConstBasicIterator& Position) const;
  inline unsigned int getRequiredDeletedDepth() const;
  inline unsigned int getRequiredDeletedDepth(
    const CTextDataTree::CConstBasicIterator& Position) const;
  inline unsigned int getMistakeDepth() const;

  inline CTextDataTree::CConstBasicIterator getParentPosition(
    const CTextDataTree::CConstBasicIterator& Position) const;

  // Iterator settings
  const CTextDataTree* pHostTree_;
  ETextMode IteratorMode_;

  CTextDataTree::CConstBasicIterator CurrentPosition_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SYMBOLITERATOR_H
