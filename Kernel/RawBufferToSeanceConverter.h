#ifndef RAWBUFFERTOSEANCECONVERTER_H
#define RAWBUFFERTOSEANCECONVERTER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <list> //pch
// TO DO
// rewrite
// This include is not longer needed since I do not use the iterators!
// included into header because of dependent declaration of interators
// that is CSession::const_iterator and CSession::iterator
#include "Seance.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CKeysBeingPressed
//---------------------------------------------------------------------------

class CKeysBeingPressed : public std::list<CKeyEvent*> {
public:
  using CBase = std::list<CKeyEvent*>;
  using CVKCodeType =  NSKeyboard::CVKCode::CVKCodeType;
  bool findIteratorOfEvent(CVKCodeType VKey, const_iterator* pIndex) const;
};
//---------------------------------------------------------------------------
// Declaration of CRawBufferToSeanceConverter
//---------------------------------------------------------------------------

class CRawBufferToSeanceConverter {
  using CRawBuffer = NSKeyboard::CRawEventContainer;
  using CRawKey = NSKeyboard::CRawKey;
public:
  CRawBufferToSeanceConverter() = default;
  CRawBufferToSeanceConverter(microseconds SessionTimeLimit);
  void convert(CRawBuffer* pBuffer, CSeance* pSeance);
protected:
private:
  void setInternalResources(CRawBuffer* pBuffer, CSeance* pSeance);
  void prepareFirstSession();
  void handleRawEvent(const CRawKey& RawEvent);
  bool needNewSession(const CRawKey& RawEvent) const;
  void prepareNewSession();
  void releaseAllKeysInCurrentKeyboard();
  void handlePressing(const CRawKey& RawEvent);
  void handleKeyHolding(const CRawKey& RawEvent,
                        const CKeysBeingPressed::iterator& index);
  void handleKeyPressing(const CRawKey& RawEvent);

  void handleReleasing(const CRawKey& RawEvent);
  void handleKeyReleasing(microseconds ReleasingTime,
                          const CKeysBeingPressed::iterator& index);
  void releaseAllRemainingKeys();
  void releaseAtGivenTime(microseconds ReleasingTime,
                          CKeysBeingPressed* pKeysBeingPressed);
  const CSession& CurrentSession() const;
  CSession& CurrentSession();
  void removeEmptyOutput();
  void flushBuffer();


  CRawBuffer* pBuffer_ = nullptr;
  CSeance* pSeance_ = nullptr;
  NSKeyboard::CKeyboardState CurrentKeyboardState_;

  CKeysBeingPressed PressedKeys_;
  microseconds SessionTimeLimit_ = kSessionTimeLimit;

  // Time between sessions is 5 seconds
  static constexpr const microseconds kSessionTimeLimit = 5000000;
  // If, by any reason, we have unreleased keys in a session,
  // and we cannot determine when to release them
  // we release the keys after 40 milliseconds
  static constexpr const microseconds kStandardHoldingTime = 40000;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // RAWBUFFERTOSEANCECONVERTER_H
