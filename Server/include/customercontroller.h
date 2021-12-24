#ifndef CUSTOMERCONTROLLER_H
#define CUSTOMERCONTROLLER_H

#include <QObject>
#include <httprequesthandler.h>

using namespace stefanfrings;

class CustomerController : public HttpRequestHandler
{
  Q_OBJECT
  Q_DISABLE_COPY(CustomerController)
 public:

   /** Constructor */
   CustomerController();

  /** Generates the response */
  void service(HttpRequest& request, HttpResponse& response);

  bool authorization(const QString& theLogin,
                     const QString& thePassword);

  bool registration(const QString& theName,
                    const QString& theMiddleName,
                    const QString& theLastName,
                    const QString& thePhone,
                    const QString& theEmail,
                    const QString& theLogin,
                    const QString& thePassword);

  bool requestProducts();

  bool requestProducts(const QString& thePath);

  bool requestOffices();

  bool requestOffices(const QString& thePath);


  void parseProduct(const QByteArray& theArray);

  void parseOffices(const QByteArray& theArray);

  void parseOrder(const QByteArray& theArray);

private:

 };

#endif // CUSTOMERCONTROLLER_H
