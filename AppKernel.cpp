//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "AppKernel.h"
#include <QDebug>
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CAppKernel
//---------------------------------------------------------------------------

void CAppKernel::setTextMode(EOutputMode OutputMode, ETextMode TextMode) {
  qDebug() << "setTextMode";
  if(Kernel_.setTextMode(OutputMode, TextMode))
    // TO DO
    qDebug() << "emit Signal TextMode Changed";
}
//---------------------------------------------------------------------------

void CAppKernel::setShiftMode(ECapitalMode ShiftMode) {
  qDebug() << "setShiftMode";
  if(Kernel_.setShiftMode(ShiftMode))
    // TO DO
    qDebug() << "emit Signal ShiftMode Changed";
}
//---------------------------------------------------------------------------

void CAppKernel::setCapslockMode(ECapitalMode CapslockMode) {
  qDebug() << "setCapslockMode";
  if(Kernel_.setCapslockMode(CapslockMode))
    // TO DO
    qDebug() << "emit Signal CapslockMode Changed";
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
