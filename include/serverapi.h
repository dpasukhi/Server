#ifndef SERVERAPI_H
#define SERVERAPI_H

#include <QObject>
#include <QSharedDataPointer>

class ServerAPIData;

class ServerAPI
{
  Q_OBJECT
public:
  ServerAPI();
  ServerAPI(const ServerAPI &);
  ServerAPI &operator=(const ServerAPI &);
  ~ServerAPI();

private:
  QSharedDataPointer<ServerAPIData> data;
};

#endif // SERVERAPI_H
