//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "AppStatusReader.h"
#include <QApplication>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CAppStatusR
//---------------------------------------------------------------------------

CAppStatusReader::CAppStatusReader(QObject *parent)
  : QObject(parent) {
  connectToAppStatus();
}
//---------------------------------------------------------------------------

void CAppStatusReader::onAppActivation(Qt::ApplicationState State) {
  if (State == Qt::ApplicationActive) {
    AppActivated_(true);
    return;
  }
  if (State == Qt::ApplicationInactive || State == Qt::ApplicationHidden) {
    AppActivated_(false);
    return;
  }
}
//---------------------------------------------------------------------------

void CAppStatusReader::connectToAppStatus() {
  if (!QObject::connect(qApp,
                        &QApplication::applicationStateChanged,
                        this,
                        &CAppStatusReader::onAppActivation))
    throw std::exception("Cannot connect AppStatusReader to Application Status!\n");
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
