//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "FingerLayout.h"
#include <cassert> //pch
#include <algorithm> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition of CKey
//---------------------------------------------------------------------------

CKey::CKey() : CBase(CVKCode::InvalidCode) {
}
//---------------------------------------------------------------------------

CKey& CKey::operator=(CVKCodeType VKCode) {
  CBase::VKCode_ = VKCode;
  return *this;
}
//---------------------------------------------------------------------------

bool CKey::operator==(const CKey& Key) const {
  return VKCode_ == Key.VKCode_;
}
//---------------------------------------------------------------------------

bool CKey::operator!=(const CKey& Key) const {
  return !(*this == Key);
}
//---------------------------------------------------------------------------

bool CKey::operator<(const CKey& Key) const {
  return VKCode_ < Key.VKCode_;
}
//---------------------------------------------------------------------------
// Definition of CFinger
//---------------------------------------------------------------------------

CFinger::CFinger(CHFType HandFingerFlags)
  : FingerData_(HandFingerFlags) {
  // These asserts check the validity of the flags
  assert((FingerData_ & (8 + 16 + 32 + 64)) == 0);
  assert(((FingerData_ & 4) == 0) | ((FingerData_ & (1 + 2)) == 0));
}

//---------------------------------------------------------------------------

bool CFinger::isLeftHand() const {
  return (FingerData_ & 128) == 0;
}
//---------------------------------------------------------------------------

bool CFinger::isRightHand() const {
  return !isLeftHand();
}
//---------------------------------------------------------------------------

bool CFinger::isThumb() const {
  return ((FingerData_ << 1) >> 1) == CHandFingerFlags::Thumb;
}
//---------------------------------------------------------------------------

bool CFinger::isIndex() const {
  return ((FingerData_ << 1) >> 1) == CHandFingerFlags::Index;
}
//---------------------------------------------------------------------------

bool CFinger::isMiddle() const {
  return ((FingerData_ << 1) >> 1) == CHandFingerFlags::Middle;
}
//---------------------------------------------------------------------------

bool CFinger::isRing() const {
  return ((FingerData_ << 1) >> 1) == CHandFingerFlags::Ring;
}
//---------------------------------------------------------------------------

bool CFinger::isPinky() const {
  return ((FingerData_ << 1) >> 1) == CHandFingerFlags::Pinky;
}
//---------------------------------------------------------------------------

CFinger::CHFType CFinger::getHand() const {
  return FingerData_ & 128;
}
//---------------------------------------------------------------------------

CFinger::CHFType CFinger::getFinger() const {
  return (FingerData_ << 1) >> 1;
}
//---------------------------------------------------------------------------

CFinger::CHFType CFinger::getFingerData() const {
  return FingerData_;
}
//---------------------------------------------------------------------------

void CFinger::changeHandTo(CHFType HandFlag) {
  assert(((HandFlag << 1) >> 1) == 0);
  FingerData_ = ((FingerData_ << 1) >> 1) ^ HandFlag;
}
//---------------------------------------------------------------------------

void CFinger::changeFingerTo(CHFType FingerFlag) {
  assert(FingerFlag <= 4);
  FingerData_ = (FingerData_ & 128) | FingerFlag;
}
//---------------------------------------------------------------------------

void CFinger::setTo(CHFType FingerData) {
  // These asserts check the validity of the flags
  assert((FingerData & (8 + 16 + 32 + 64)) == 0);
  assert(((FingerData & 4) == 0) | ((FingerData & (1 + 2)) == 0));
  FingerData_ = FingerData;
}
//---------------------------------------------------------------------------

void CFinger::getFingerName(std::wstring* pFingerName) const {
  switch (getFinger()) {
  case CHandFingerFlags::Thumb:
    *pFingerName = L"Thumb";
    break;
  case CHandFingerFlags::Index:
    *pFingerName = L"Index";
    break;
  case CHandFingerFlags::Middle:
    *pFingerName = L"Middle";
    break;
  case CHandFingerFlags::Ring:
    *pFingerName = L"Ring";
    break;
  case CHandFingerFlags::Pinky:
    *pFingerName = L"Pinky";
    break;
  default:
    *pFingerName = L"Unknown";
    break;
  }
}
//---------------------------------------------------------------------------

void CFinger::getHandName(std::wstring* pHandName) const {
  if (isLeftHand())
    *pHandName = L"Left Hand";
  else
    *pHandName = L"Right Hand";
}
//---------------------------------------------------------------------------

bool CFinger::operator<(const CFinger& other) const {
  return CDirectOrder()(*this, other);
}
//---------------------------------------------------------------------------
// Definition of CFinger::CThumbFirst
//---------------------------------------------------------------------------

bool CFinger::CThumbFirst::operator()(
  const CFinger& first, const CFinger& second) const {
  return first.isThumb() && !second.isThumb();
}
//---------------------------------------------------------------------------
// Definition of CFinger::CLeftHandFirst
//---------------------------------------------------------------------------

bool CFinger::CLeftHandFirst::operator()(
  const CFinger& first, const CFinger& second) const {
  return first.isLeftHand() && !second.isLeftHand();
}
//---------------------------------------------------------------------------
// Definition of CFinger::CDirectOrder
//---------------------------------------------------------------------------

bool CFinger::CDirectOrder::operator()(
  const CFinger& first, const CFinger& second) const {
  return first.FingerData_ < second.FingerData_;
}
//---------------------------------------------------------------------------
// Definition of CFinger::CReverseOrder
//---------------------------------------------------------------------------

bool CFinger::CReverseOrder::operator()(
  const CFinger& first, const CFinger& second) const {
  return first.FingerData_ > second.FingerData_;
}
//---------------------------------------------------------------------------
// Definition of CFinger::CLeftReverseRightDirect
//---------------------------------------------------------------------------

bool CFinger::CLeftReverseRightDirect::operator()(
  const CFinger& first, const CFinger& second) const {
  if (first.isLeftHand()) {
    if (second.isLeftHand())
      // first - left, second - left
      return CReverseOrder()(first, second);
    else
      // first - left, second - right
      return true;
  } else {
    if (second.isLeftHand())
      // first - right, second - left
      return false;
    else
      // first - right, second - right
      return CDirectOrder()(first, second);
  }
}
//---------------------------------------------------------------------------
// Definition of CFingerWithKeys
//---------------------------------------------------------------------------

bool CFingerWithKeys::isThereKey(const CKey& Key) const {
  return CKeyContainer::count(Key) == 1;
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefault() {
  clear();
  switch (getFingerData()) {
  case CHandFingerFlags::Left | CHandFingerFlags::Thumb:
    setToDefaultLhThumb();
    break;
  case CHandFingerFlags::Left | CHandFingerFlags::Index:
    setToDefaultLhIndex();
    break;
  case CHandFingerFlags::Left | CHandFingerFlags::Middle:
    setToDefaultLhMiddle();
    break;
  case CHandFingerFlags::Left | CHandFingerFlags::Ring:
    setToDefaultLhRing();
    break;
  case CHandFingerFlags::Left | CHandFingerFlags::Pinky:
    setToDefaultLhPinky();
    break;
  case CHandFingerFlags::Right | CHandFingerFlags::Thumb:
    setToDefaultRhThumb();
    break;
  case CHandFingerFlags::Right | CHandFingerFlags::Index:
    setToDefaultRhIndex();
    break;
  case CHandFingerFlags::Right | CHandFingerFlags::Middle:
    setToDefaultRhMiddle();
    break;
  case CHandFingerFlags::Right | CHandFingerFlags::Ring:
    setToDefaultRhRing();
    break;
  case CHandFingerFlags::Right | CHandFingerFlags::Pinky:
    setToDefaultRhPinky();
    break;
  // unknown finger, do nothing
  default:
    break;
  }
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhThumb() {
  // It is commented because logically I want to put a spacebar here
  // but I cannot determine the finger used to press the spacebar
  // Therefore, I have to assign the key to the right Thumb only
  // I left this commented line here to notify the issue
  //CKeyContainer::insert(CVKCode::Spacebar);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhIndex() {
  CKeyContainer::insert(CVKCode::VK_5);
  CKeyContainer::insert(CVKCode::R);
  CKeyContainer::insert(CVKCode::F);
  CKeyContainer::insert(CVKCode::V);
  CKeyContainer::insert(CVKCode::VK_6);
  CKeyContainer::insert(CVKCode::T);
  CKeyContainer::insert(CVKCode::G);
  CKeyContainer::insert(CVKCode::B);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhMiddle() {
  CKeyContainer::insert(CVKCode::VK_4);
  CKeyContainer::insert(CVKCode::E);
  CKeyContainer::insert(CVKCode::D);
  CKeyContainer::insert(CVKCode::C);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhRing() {
  CKeyContainer::insert(CVKCode::VK_3);
  CKeyContainer::insert(CVKCode::W);
  CKeyContainer::insert(CVKCode::S);
  CKeyContainer::insert(CVKCode::X);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhPinky() {
  CKeyContainer::insert(CVKCode::VK_1);
  CKeyContainer::insert(CVKCode::VK_2);
  CKeyContainer::insert(CVKCode::Q);
  CKeyContainer::insert(CVKCode::A);
  CKeyContainer::insert(CVKCode::Z);
  CKeyContainer::insert(CVKCode::LeftShift);
  CKeyContainer::insert(CVKCode::LeftCtrl);
  CKeyContainer::insert(CVKCode::LeftAlt);
  CKeyContainer::insert(CVKCode::Capslock);
  CKeyContainer::insert(CVKCode::Eng_Tilde);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhThumb() {
  CKeyContainer::insert(CVKCode::Spacebar);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhIndex() {
  CKeyContainer::insert(CVKCode::VK_7);
  CKeyContainer::insert(CVKCode::VK_8);
  CKeyContainer::insert(CVKCode::Y);
  CKeyContainer::insert(CVKCode::H);
  CKeyContainer::insert(CVKCode::N);
  CKeyContainer::insert(CVKCode::U);
  CKeyContainer::insert(CVKCode::J);
  CKeyContainer::insert(CVKCode::M);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhMiddle() {
  CKeyContainer::insert(CVKCode::VK_9);
  CKeyContainer::insert(CVKCode::I);
  CKeyContainer::insert(CVKCode::K);
  CKeyContainer::insert(CVKCode::Eng_Comma);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhRing() {
  CKeyContainer::insert(CVKCode::VK_0);
  CKeyContainer::insert(CVKCode::O);
  CKeyContainer::insert(CVKCode::L);
  CKeyContainer::insert(CVKCode::Eng_Period);
}
//---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhPinky() {
  CKeyContainer::insert(CVKCode::P);
  CKeyContainer::insert(CVKCode::Eng_Semicolon);
  CKeyContainer::insert(CVKCode::Eng_Slash_Question);
  CKeyContainer::insert(CVKCode::Eng_Minus);
  CKeyContainer::insert(CVKCode::Eng_Plus);
  CKeyContainer::insert(CVKCode::Eng_Left_Brace);
  CKeyContainer::insert(CVKCode::Eng_Right_Brace);
  CKeyContainer::insert(CVKCode::Eng_Quote);
  CKeyContainer::insert(CVKCode::Backspace);
  CKeyContainer::insert(CVKCode::Eng_Backslash);
  CKeyContainer::insert(CVKCode::Enter);
  CKeyContainer::insert(CVKCode::RightShift);
  CKeyContainer::insert(CVKCode::RightAlt);
  CKeyContainer::insert(CVKCode::RightCtrl);
}
//---------------------------------------------------------------------------
// Definition of CFingerLayout
//---------------------------------------------------------------------------

void CFingerLayout::addFinger(CHFType FingerData) {
  if(isThereFinger(FingerData))
    return;
  emplace_back(FingerData);
}
//---------------------------------------------------------------------------

void CFingerLayout::removeFinger(CHFType FingerData) {
  CFingerIterator index;
  if(findFingerIterator(FingerData, &index))
    erase(index);
}
//---------------------------------------------------------------------------

void CFingerLayout::assignKeyToFinger(const CKey& Key,
                                      const CFingerIterator& index) {
  unAssignKey(Key);
  index->insert(Key);
}
//---------------------------------------------------------------------------

void CFingerLayout::assignKeyToFinger(const CKey& Key,
                                      CHFType FingerData) {
  unAssignKey(Key);
  addFinger(FingerData);
  CFingerIterator index;
  findFingerIterator(FingerData, &index);
  assignKeyToFinger(Key, index);
}
//---------------------------------------------------------------------------

void CFingerLayout::unAssignKey(const CKey& Key) {
  CFingerIterator index;
  if (findFingerIteratorOfKey(Key, &index))
    index->erase(Key);
}
//---------------------------------------------------------------------------

bool CFingerLayout::findFingerIterator(
  CHFType FingerData, CFingerConstIterator* pIndex) const {
  CFingerConstIterator& index = *pIndex;
  index = std::find_if(begin(),
                       end(),
  [FingerData](const CFingerWithKeys& Finger) {
    return Finger.getFingerData() == FingerData;
  });
  if (index == end())
    return false;
  return true;
}
//---------------------------------------------------------------------------

bool CFingerLayout::findFingerIteratorOfKey(
  const CKey& Key, CFingerConstIterator* pIndex) const {
  CFingerConstIterator& index = *pIndex;
  for (index = begin(); index != end(); ++index)
    if (index->isThereKey(Key))
      return true;
  return false;

}
//---------------------------------------------------------------------------

bool CFingerLayout::isThereFinger(CHFType FingerData) const {
  CFingerConstIterator index;
  return findFingerIterator(FingerData, &index);
}
//---------------------------------------------------------------------------

bool CFingerLayout::isKeyAssigned(const CKey& Key) const {
  CFingerConstIterator index;
  return findFingerIteratorOfKey(Key, &index);
}
//---------------------------------------------------------------------------

bool CFingerLayout::isKeyAssignedToFinger(
  const CKey& Key, CHFType FingerData) const {
  CFingerConstIterator index;
  if (!findFingerIteratorOfKey(Key, &index))
    return false;
  if (index->getFingerData() != FingerData)
    return false;
  return true;
}
//---------------------------------------------------------------------------

void CFingerLayout::generateDefaultLayout(CFingerLayout* FingerLayout) {
  FingerLayout->clear();
  // Since there is no way to distinguish left and right thumbs
  // we assume that the space is pressed by the right one.
  // Thus we delete the left thumb from the layout
  addLeftHand(FingerLayout);
  FingerLayout->removeFinger(CHandFingerFlags::Left | CHandFingerFlags::Thumb);
  addRightHand(FingerLayout);
  for (auto& Finger : *FingerLayout)
    Finger.setToDefault();
}
//---------------------------------------------------------------------------

void CFingerLayout::addLeftHand(CFingerLayout* FingerLayout) {
  for(CHFType finger = CHandFingerFlags::Left | CHandFingerFlags::Thumb;
      finger <= (CHandFingerFlags::Left | CHandFingerFlags::Pinky);
      ++finger)
    FingerLayout->emplace_back(finger);
}
//---------------------------------------------------------------------------

void CFingerLayout::addRightHand(CFingerLayout* FingerLayout) {
  for(CHFType finger = CHandFingerFlags::Right | CHandFingerFlags::Thumb;
      finger <= (CHandFingerFlags::Right | CHandFingerFlags::Pinky);
      ++finger)
    FingerLayout->emplace_back(finger);
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
