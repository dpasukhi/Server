#include "customercontroller.h"
#include <QDir>
#include <QDebug>

CustomerController::CustomerController()
{

}

void CustomerController::service(HttpRequest& request,
                                 HttpResponse& response)
{
  QByteArray anOP = request.getHeader("Type");
  if (anOP == "prod_list")
  {
    QFile aFile;
    QString aPath =  QDir::currentPath() +"/../../Server/Server/etc/templates/message.json";
    aFile.setFileName(aPath);
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QByteArray myContent = aFile.readAll();
      response.setHeader("Reply", "accepted");
      response.write(myContent);
    }
  }
  else if (anOP == "authorization")
  {
    response.setHeader("Reply", "accepted");
  }
  else if (anOP == "order_list")
  {
    response.setHeader("Reply", "accepted");
  }
  else if (anOP == "registration")
  {
    response.setHeader("Reply", "accepted");
  }
  else if (anOP == "office_list")
  {
    QFile aFile;
    QString aPath =  QDir::currentPath() + "/../../Server/Server/etc/templates/office.json";
    aFile.setFileName(aPath);
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QByteArray myContent = aFile.readAll();
      response.setHeader("Reply", "accepted");
      response.write(myContent);
    }
  }
  else if (anOP == "order_send")
  {
    response.setHeader("Reply", "accepted");
  }
}

bool CustomerController::authorization(const QString& theLogin,
                                       const QString& thePassword)
{
  return true;
}

bool CustomerController::registration(const QString&theName,
                                      const QString& theMiddleName,
                                      const QString& theLastName,
                                      const QString& thePhone,
                                      const QString& theEmail,
                                      const QString& theLogin,
                                      const QString& thePassword)
{
  return true;
}

bool CustomerController::requestProducts()
{
  return true;
}

bool CustomerController::requestProducts(const QString& thePath)
{
  return true;
}

bool CustomerController::requestOffices()
{
  return true;
}

bool CustomerController::requestOffices(const QString& thePath)
{
  return true;
}

void CustomerController::parseProduct(const QByteArray& theArray)
{
}

void CustomerController::parseOffices(const QByteArray& theArray)
{

}

void CustomerController::parseOrder(const QByteArray& theArray)
{

}
