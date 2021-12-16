#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <serverapi.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class ClientAPI  : public ServerAPI
{
public:
  ClientAPI();
  int Authorization(const QString& theLogin, const QString& thePassword) override;
  int Registration(const QString& email, const QString& pass, QString& last_name, const QString& first_name, const QString& middle_name, const QString& phone);
  QJsonDocument GetProductsJS();

};

#endif // CLIENTAPI_H
