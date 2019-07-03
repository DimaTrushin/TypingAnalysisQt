#ifndef TEXTMODEREADER_H
#define TEXTMODEREADER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QObject>
#include "Library/Signals.h"
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

class QButtonGroup;
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

enum class ETextMode : unsigned char;
enum class EOutputMode : unsigned char;
enum class ECapitalMode : unsigned char;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------

namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CTextModeReader
//---------------------------------------------------------------------------

class CTextModeReader : public QObject {
  Q_OBJECT
  using EOutputMode = NSKernel::EOutputMode;
  using ETextMode = NSKernel::ETextMode;
  using ECapitalMode = NSKernel::ECapitalMode;
  using CTextModeSignal = NSLibrary::CSignal<void(EOutputMode, ETextMode)>;
  using CCapitalsModeSignal = NSLibrary::CSignal<void(ECapitalMode)>;
  using CConnection = NSLibrary::CConnection;
public:
  CTextModeReader(QButtonGroup* pTextMode,
                  QButtonGroup* pShiftsMode,
                  QButtonGroup* pCapslocksMode);
  template<class TObject, class TMethod>
  CConnection connectTextModeSelect(TObject* pObject, TMethod&& Method);
  template<class TObject, class TMethod>
  CConnection connectShiftModeSelect(TObject* pObject, TMethod&& Method);
  template<class TObject, class TMethod>
  CConnection connectCapslockModeSelect(TObject* pObject, TMethod&& Method);

public slots:
  void onTextModeButtonClicked(int buttonID);
  void onShiftModeButtonClicked(int buttonID);
  void onCapslockModeButtonClicked(int buttonID);
private:
  CTextModeSignal onTextModeSelect_;
  CCapitalsModeSignal onShiftModeSelect_;
  CCapitalsModeSignal onCapslockModeSelect_;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CTextModeReader
//---------------------------------------------------------------------------

template<class TObject, class TMethod>
CTextModeReader::CConnection
CTextModeReader::connectTextModeSelect(
  TObject* pObject, TMethod&& Method) {
  return onTextModeSelect_.connectMethod(pObject,
                                         std::forward<TMethod>(Method));
}
//---------------------------------------------------------------------------

template<class TObject, class TMethod>
CTextModeReader::CConnection
CTextModeReader::connectShiftModeSelect(
  TObject* pObject, TMethod&& Method) {
  return onShiftModeSelect_.connectMethod(pObject,
                                          std::forward<TMethod>(Method));
}
//---------------------------------------------------------------------------

template<class TObject, class TMethod>
CTextModeReader::CConnection
CTextModeReader::connectCapslockModeSelect(
  TObject* pObject, TMethod&& Method) {
  return
    onCapslockModeSelect_.connectMethod(pObject,
                                        std::forward<TMethod>(Method));
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TEXTMODEREADER_H
