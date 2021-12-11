#include "managerapi.h"

ManagerAPI::ManagerAPI()
{

}

int ManagerAPI::Authorization(const QString& theLogin, const QString& thePassword)
{
  return -1;
}

QJsonDocument ManagerAPI::GetOrdersJS()
{
  return QJsonDocument();
}
