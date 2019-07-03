#ifndef LOWLEVELKEYBOARD_H
#define LOWLEVELKEYBOARD_H

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <windows.h> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CSafeRawBuffer
//---------------------------------------------------------------------------

class CSafeRawBuffer {
public:
  CSafeRawBuffer();
  CSafeRawBuffer(size_t Size);
  ~CSafeRawBuffer();
  CSafeRawBuffer(const CSafeRawBuffer&) = delete;
  CSafeRawBuffer(CSafeRawBuffer&& other);
  CSafeRawBuffer& operator=(const CSafeRawBuffer&) = delete;
  CSafeRawBuffer& operator=(CSafeRawBuffer&& other);

  inline RAWINPUT* getPRAWINPUT();
  inline RAWINPUT& getRAWINPUT();
  inline const RAWINPUT& getRAWINPUT() const;
  inline LPBYTE getBuffer() const;
  inline bool isDefined() const;
  inline size_t getSize() const;
  // resize does not make the buffer smaller!!!
  inline void resizeIfSmaller(size_t newSize);
  inline void clear();

private:
  LPBYTE pBuffer_;
  size_t size_;
};
//---------------------------------------------------------------------------
// Declaration of CLowLevelKeyboard
//---------------------------------------------------------------------------
// Class interacts with Raw Input using Windows API

class CLowLevelKeyboard {
public:
  //CLowLevelKeyboard() = default;
  CLowLevelKeyboard(HWND ReceiverHandle);
  ~CLowLevelKeyboard();
  const RAWKEYBOARD& getRawInputData(LPARAM lParam) const;

  CLowLevelKeyboard(const CLowLevelKeyboard&) = delete;
  CLowLevelKeyboard(CLowLevelKeyboard&&) = delete;
  CLowLevelKeyboard& operator=(const CLowLevelKeyboard&) = delete;
  CLowLevelKeyboard& operator=(CLowLevelKeyboard&&) = delete;

private:
  inline void Initialize(HWND ReceiverHandle);

  inline size_t getRawDataSize(LPARAM lParam) const;
  inline void readRawInputData(LPARAM lParam) const;
  inline void setDeviceClassToKeyboardClass();
  inline void setDeviceToKeyboard();
  inline void setToCollectEverything();
  inline void setToRemove();
  inline void setReceiver(HWND ReceiverHandle);
  inline void registerDevice();
  inline void shutdownDevice();
  inline void removeDevice();

  RAWINPUTDEVICE lowLevelDevice_;
  mutable CSafeRawBuffer RawInputBuffer_;
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // LOWLEVELKEYBOARD_H
