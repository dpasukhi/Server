#ifndef MANAGERAPI_H
#define MANAGERAPI_H

#include <serverapi.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class ManagerAPI : public ServerAPI
{
public:
  ManagerAPI();
  int Authorization(const QString& theLogin, const QString& thePassword) override;
  QJsonDocument GetOrdersJS();
};

#endif // MANAGERAPI_H
