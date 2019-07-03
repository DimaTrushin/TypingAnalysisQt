//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "LowLevelKeyboard.h"
#include <exception> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definitions of CSafeRawBuffer
//---------------------------------------------------------------------------

CSafeRawBuffer::CSafeRawBuffer()
  : pBuffer_(nullptr),
    size_(0) {
}
//---------------------------------------------------------------------------

CSafeRawBuffer::CSafeRawBuffer(size_t Size)
  : pBuffer_(new BYTE[Size]),
    size_(Size) {
  if (!isDefined())
    throw std::exception("Cannot create space for Raw Input!\n");
}
//---------------------------------------------------------------------------

CSafeRawBuffer::~CSafeRawBuffer() {
  clear();
}
//---------------------------------------------------------------------------

CSafeRawBuffer::CSafeRawBuffer(CSafeRawBuffer&& other)
  : pBuffer_(other.pBuffer_),
    size_(other.size_) {
  other.pBuffer_ = nullptr;
  other.size_ = 0;
}
//---------------------------------------------------------------------------

CSafeRawBuffer& CSafeRawBuffer::operator=(CSafeRawBuffer&& other) {
  delete[] pBuffer_;
  pBuffer_ = other.pBuffer_;
  size_ = other.size_;
  other.pBuffer_ = nullptr;
  other.size_ = 0;
  return *this;
}
//---------------------------------------------------------------------------

RAWINPUT* CSafeRawBuffer::getPRAWINPUT() {
  return (RAWINPUT*)pBuffer_;
}
//---------------------------------------------------------------------------

RAWINPUT& CSafeRawBuffer::getRAWINPUT() {
  return *((RAWINPUT*)pBuffer_);
}
//---------------------------------------------------------------------------

const RAWINPUT& CSafeRawBuffer::getRAWINPUT() const {
  return *((RAWINPUT*)pBuffer_);
}
//---------------------------------------------------------------------------

LPBYTE CSafeRawBuffer::getBuffer() const {
  return pBuffer_;
}
//---------------------------------------------------------------------------

bool CSafeRawBuffer::isDefined() const {
  if (pBuffer_ == nullptr)
    return false;
  return true;
}
//---------------------------------------------------------------------------

size_t CSafeRawBuffer::getSize() const {
  return size_;
}
//---------------------------------------------------------------------------

void CSafeRawBuffer::resizeIfSmaller(size_t newSize) {
  if (isDefined())
    if (newSize <= size_)
      return;
  *this = CSafeRawBuffer(newSize);
}
//---------------------------------------------------------------------------

void CSafeRawBuffer::clear() {
  delete[] pBuffer_;
}
//---------------------------------------------------------------------------
// Definitions of CLowLevelKeyboard
//---------------------------------------------------------------------------

CLowLevelKeyboard::CLowLevelKeyboard(HWND ReceiverHandle) {
  Initialize(ReceiverHandle);
}
//---------------------------------------------------------------------------

CLowLevelKeyboard::~CLowLevelKeyboard() {
  shutdownDevice();
}
//---------------------------------------------------------------------------

const RAWKEYBOARD& CLowLevelKeyboard::getRawInputData(LPARAM lParam) const {
  RawInputBuffer_.resizeIfSmaller(getRawDataSize(lParam));
  readRawInputData(lParam);
  return RawInputBuffer_.getRAWINPUT().data.keyboard;
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::Initialize(HWND ReceiverHandle) {
  setDeviceClassToKeyboardClass();
  setDeviceToKeyboard();
  setToCollectEverything();
  setReceiver(ReceiverHandle);
  registerDevice();
}
//---------------------------------------------------------------------------

size_t CLowLevelKeyboard::getRawDataSize(LPARAM lParam) const {
  size_t dwSize;
  GetRawInputData((HRAWINPUT)lParam,
                  RID_INPUT,
                  nullptr,
                  &dwSize,
                  sizeof(RAWINPUTHEADER));
  return dwSize;
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::readRawInputData( LPARAM lParam) const {
  size_t bufferSize = RawInputBuffer_.getSize();
  if (GetRawInputData((HRAWINPUT)lParam,
                      RID_INPUT,
                      RawInputBuffer_.getBuffer(),
                      &bufferSize,
                      sizeof(RAWINPUTHEADER)) != bufferSize)
    throw std::exception("GetRawInputData does not return correct size !\n");
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::setDeviceClassToKeyboardClass() {
  lowLevelDevice_.usUsagePage = 0x01;
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::setDeviceToKeyboard() {
  lowLevelDevice_.usUsage = 0x06;
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::setToCollectEverything() {
  lowLevelDevice_.dwFlags = RIDEV_INPUTSINK;
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::setToRemove() {
  lowLevelDevice_.dwFlags = RIDEV_REMOVE;
  setReceiver(nullptr);
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::setReceiver(HWND ReceiverHandle) {
  lowLevelDevice_.hwndTarget = ReceiverHandle;
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::registerDevice() {
  if (RegisterRawInputDevices(&lowLevelDevice_,
                              1,
                              sizeof(lowLevelDevice_))
      == FALSE)
    throw std::exception("Cannot initialize keyboard!\n");
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::shutdownDevice() {
  setDeviceClassToKeyboardClass();
  setDeviceToKeyboard();
  setToRemove();
  removeDevice();
}
//---------------------------------------------------------------------------

void CLowLevelKeyboard::removeDevice() {
  if (RegisterRawInputDevices(&lowLevelDevice_,
                              1,
                              sizeof(lowLevelDevice_))
      == FALSE)
    throw std::exception("Cannot shutdown keyboard!\n");
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
