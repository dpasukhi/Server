#ifndef DELIVERAPI_H
#define DELIVERAPI_H

#include <serverapi.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class DeliverAPI : public ServerAPI
{
public:
  DeliverAPI();
  int Authorization(const QString& theLogin, const QString& thePassword) override;
  QJsonDocument GetOrdersJS();
};

#endif // DELIVERAPI_H
