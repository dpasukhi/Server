#include "clientapi.h"

ClientAPI::ClientAPI()
{

}

int ClientAPI::Authorization(const QString& theLogin, const QString& thePassword)
{
  return -1;
}

int ClientAPI::Registration(const QString& email, const QString& pass, QString& last_name, const QString& first_name, const QString& middle_name, const QString& phone)
{
  return -1;
}

QJsonDocument ClientAPI::GetProductsJS()
{
  return QJsonDocument();
}
