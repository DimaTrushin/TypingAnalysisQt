#ifndef APPSTATUSREADER_H
#define APPSTATUSREADER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QObject>
#include "Library/Signals.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CAppStatusR
//---------------------------------------------------------------------------

class CAppStatusReader : public QObject {
  Q_OBJECT
public:
  using CSignalType = NSLibrary::CSignal<void (bool)>;
  using CConnection = NSLibrary::CConnection;

  explicit CAppStatusReader(QObject *parent = nullptr);

  template<class TObject, class TMethod>
  CConnection connectObjectMethod(TObject* pObject, TMethod&& Method);
signals:
public slots:
  void onAppActivation(Qt::ApplicationState State);
private:
  void connectToAppStatus();
  CSignalType AppActivated_;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CAppStatusR
//---------------------------------------------------------------------------

template<class TObject, class TMethod>
CAppStatusReader::CConnection
CAppStatusReader::connectObjectMethod(TObject* pObject, TMethod&& Method) {
  return AppActivated_.connectMethod(pObject, std::forward<TMethod>(Method));
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPSTATUSREADER_H
