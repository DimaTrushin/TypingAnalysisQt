//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QButtonGroup>
#include "TextModeReader.h"
#include "Kernel/TextMode.h"
#include <QDebug>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CTextModeReader
//---------------------------------------------------------------------------

CTextModeReader::CTextModeReader(QButtonGroup* pTextMode,
                                 QButtonGroup* pShiftsMode,
                                 QButtonGroup* pCapslocksMode) {
  if(!QObject::connect(pTextMode,
                       QOverload<int>::of(&QButtonGroup::buttonClicked),
                       this,
                       &CTextModeReader::onTextModeButtonClicked))
    throw std::exception("Cannot connect TextMode ButtonGroup to TextModeReader!");
  if(!QObject::connect(pShiftsMode,
                       QOverload<int>::of(&QButtonGroup::buttonClicked),
                       this,
                       &CTextModeReader::onShiftModeButtonClicked))
    throw std::exception("Cannot connect ShiftsMode ButtonGroup to TextModeReader!");
  if(!QObject::connect(pCapslocksMode,
                       QOverload<int>::of(&QButtonGroup::buttonClicked),
                       this,
                       &CTextModeReader::onCapslockModeButtonClicked))
    throw std::exception("Cannot connect CapslocksMode ButtonGroup to TextModeReader!");
}
//---------------------------------------------------------------------------

void CTextModeReader::onTextModeButtonClicked(int buttonID) {
  switch (buttonID) {
  case 0:
    qDebug() << "raw";
    // in the Raw mode the second argument MUST BE ignored
    onTextModeSelect_(NSKernel::EOutputMode::Raw, NSKernel::ETextMode::Full);
    break;
  case 1:
    qDebug() << "full";
    onTextModeSelect_(NSKernel::EOutputMode::Text, NSKernel::ETextMode::Full);
    break;
  case 2:
    qDebug() << "printed";
    onTextModeSelect_(NSKernel::EOutputMode::Text, NSKernel::ETextMode::Printed);
    break;
  default:
    // Unknown state of the checked button
    assert(false);
    break;
  }
}
//---------------------------------------------------------------------------

void CTextModeReader::onShiftModeButtonClicked(int buttonID) {
  switch (buttonID) {
  case 0:
    qDebug() << "shifts non";
    onShiftModeSelect_(NSKernel::ECapitalMode::Non);
    break;
  case 1:
    qDebug() << "shifts all";
    onShiftModeSelect_(NSKernel::ECapitalMode::All);
    break;
  case 2:
    qDebug() << "shifts essential";
    onShiftModeSelect_(NSKernel::ECapitalMode::Essential);
    break;
  default:
    // Unknown state of the checked button
    assert(false);
    break;
  }
}
//---------------------------------------------------------------------------

void CTextModeReader::onCapslockModeButtonClicked(int buttonID) {
  switch (buttonID) {
  case 0:
    qDebug() << "capslocks non";
    onCapslockModeSelect_(NSKernel::ECapitalMode::Non);
    break;
  case 1:
    qDebug() << "capslocks all";
    onCapslockModeSelect_(NSKernel::ECapitalMode::All);
    break;
  case 2:
    qDebug() << "capslocks essential";
    onCapslockModeSelect_(NSKernel::ECapitalMode::Essential);
    break;
  default:
    // Unknown state of the checked button
    assert(false);
    break;
  }
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
