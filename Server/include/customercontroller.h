#ifndef CUSTOMERCONTROLLER_H
#define CUSTOMERCONTROLLER_H

#include <QObject>
#include <httprequesthandler.h>

using namespace stefanfrings;

class CustomerController : public HttpRequestHandler
{
  Q_OBJECT
  Q_DISABLE_COPY(CustomerController)

private:

  struct OrderSet
  {
    qint32 myOrderCount;
    qint32 myOrderOfficeID;
    qint32 mySumPrice;
    QString myOrderAdress;
    QVector <qint32> myOrderID;
  };
 public:

   /** Constructor */
   CustomerController();

  /** Generates the response */
  void service(HttpRequest& request, HttpResponse& response);

  QByteArray parseProduct();

  QByteArray parseOffices();

  OrderSet parseOrder(const QByteArray& theJson);

  void ContentOrder(const OrderSet& theSet, HttpRequest& request);

  qint32 ClientNewID();

  qint32 OrderNewID();

  qint32 OrderCompilationNewID();

 };

#endif // CUSTOMERCONTROLLER_H
