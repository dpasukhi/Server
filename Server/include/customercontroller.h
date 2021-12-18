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
 };

#endif // CUSTOMERCONTROLLER_H
