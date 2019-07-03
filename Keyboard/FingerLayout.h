#ifndef FINGERLAYOUT_H
#define FINGERLAYOUT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <string> //pch
#include <list> //pch
#include <set> //pch
#include "KeyPolicies.h"
#include "Library/LexSumCompare.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CHandFingerFlags
//---------------------------------------------------------------------------

class CHandFingerFlags {
public:
  using CHFType = unsigned char;
  enum : CHFType {
    Left = 0,
    Right = 128,
    Thumb = 0,
    Index = 1,
    Middle = 2,
    Ring = 3,
    Pinky = 4
  };
};
//---------------------------------------------------------------------------
// Declaration of CKey
//---------------------------------------------------------------------------

class CKey : public CKeyVKCodeBase {
  using CBase = CKeyVKCodeBase;
public:
  CKey();
  using CBase::CBase;

  CKey& operator=(CVKCodeType VKCode);
  bool operator==(const CKey& Key) const;
  bool operator!=(const CKey& Key) const;
  bool operator<(const CKey& Key) const;
};
//---------------------------------------------------------------------------
// Declaration CFinger
//---------------------------------------------------------------------------

// TO DO
// Make a separate h/cpp file pair with CFinger class
class CFinger {
public:
  using CHFType = CHandFingerFlags::CHFType;
  CFinger(CHFType HandFingerFlags = kDefaultHandFingerFlag);

  bool isLeftHand() const;
  bool isRightHand() const;
  bool isThumb() const;
  bool isIndex() const;
  bool isMiddle() const;
  bool isRing() const;
  bool isPinky() const;

  CHFType getHand() const;
  CHFType getFinger() const;
  CHFType getFingerData() const;

  void changeHandTo(CHFType HandFlag);
  void changeFingerTo(CHFType FingerFlag);
  void setTo(CHFType FingerData);

  // TO DO
  // These funcitons should depend on a Localizator object
  void getFingerName(std::wstring* pFingerName) const;
  void getHandName(std::wstring* pHandName) const;

  // coincides with CDirectOrder
  bool operator<(const CFinger& other) const;
  //---------------------------------------------------------------------------
  // Declaration CFinger::CThumbFirst
  //---------------------------------------------------------------------------

  class CThumbFirst {
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  //---------------------------------------------------------------------------
  // Declaration CFinger::CLeftHandFirst
  //---------------------------------------------------------------------------

  class CLeftHandFirst {
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  //---------------------------------------------------------------------------
  // Declaration CFinger::CDirectOrder
  //---------------------------------------------------------------------------

  class CDirectOrder {
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  //---------------------------------------------------------------------------
  // Declaration CFinger::CReverseOrder
  //---------------------------------------------------------------------------

  class CReverseOrder {
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  //---------------------------------------------------------------------------
  // Declaration CFinger::CLeftReverseRightDirect
  //---------------------------------------------------------------------------

  class CLeftReverseRightDirect {
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  using CThumbOrder = NSLibrary::CLexSumCompare<CThumbFirst, CLeftHandFirst>;
  using CStandardFingerOrder =
    NSLibrary::CLexSumCompare<CThumbOrder, CLeftReverseRightDirect>;

  //---------------------------------------------------------------------------
private:
  // underlying type is unsigned char
  // Higher bit: left hand - 0, right hand - 1
  // Fingers:
  // thumb - 0, index - 1, middle - 2, ring - 3, pinky - 4
  CHFType FingerData_;
  static constexpr CHFType kDefaultHandFingerFlag =
    CHandFingerFlags::Left | CHandFingerFlags::Thumb;
};
//---------------------------------------------------------------------------
// Declaration of CFingerWithKeys
//---------------------------------------------------------------------------

// TO DO
// rewrite
// I should make the CKeyContainer part of the class
// to be a member instead of the base class
class CFingerWithKeys : public CFinger, public std::set<CKey> {
public:
  using CKeyContainer = std::set<CKey>;
  //using CKeyIterator = CKeyContainer::iterator;
  //using CKeyConstIterator = CKeyContainer::const_iterator;

  using CFinger::CFinger;

  bool isThereKey(const CKey& Key) const;
  void setToDefault();
private:
  // this functions do not check if a key is already in the key list
  void setToDefaultLhThumb();
  void setToDefaultLhIndex();
  void setToDefaultLhMiddle();
  void setToDefaultLhRing();
  void setToDefaultLhPinky();
  void setToDefaultRhThumb();
  void setToDefaultRhIndex();
  void setToDefaultRhMiddle();
  void setToDefaultRhRing();
  void setToDefaultRhPinky();
};
//---------------------------------------------------------------------------
// Declaration of CFingerLayout
//---------------------------------------------------------------------------

class CFingerLayout : public std::list<CFingerWithKeys> {
public:
  using CHFType = CFingerWithKeys::CHFType;
  using CFingerContainer = std::list<CFingerWithKeys>;
  using CFingerIterator = typename CFingerContainer::iterator;
  using CFingerConstIterator = typename CFingerContainer::const_iterator;
  using CKeyContainer = typename CFingerWithKeys::CKeyContainer;

  void addFinger(CHFType FingerData);
  void removeFinger(CHFType FingerData);
  void assignKeyToFinger(const CKey& Key,
                         const CFingerIterator& index);
  void assignKeyToFinger(const CKey& Key, CHFType FingerData);
  void unAssignKey(const CKey& Key);
  bool findFingerIterator(CHFType FingerData,
                          CFingerConstIterator* pIndex) const;
  bool findFingerIteratorOfKey(const CKey& Key,
                               CFingerConstIterator* pIndex) const;
  bool isThereFinger(CHFType FingerData) const;
  bool isKeyAssigned(const CKey& Key) const;
  bool isKeyAssignedToFinger(const CKey& Key, CHFType FingerData) const;

  static void generateDefaultLayout(CFingerLayout* FingerLayout);
private:
  // this functions do not check if a finger is already in the finger list
  static void addLeftHand(CFingerLayout* FingerLayout);
  static void addRightHand(CFingerLayout* FingerLayout);
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // FINGERLAYOUT_H
