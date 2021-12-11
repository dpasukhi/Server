#ifndef SERVERAPI_H
#define SERVERAPI_H

#include <QObject>

class ServerAPI
{
public:
  virtual int Authorization(const QString& theLogin, const QString& thePassword) = 0;
};

#endif // SERVERAPI_H
