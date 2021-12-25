#ifndef DELIVERCONTROLLER_H
#define DELIVERCONTROLLER_H

#include <httprequesthandler.h>
#include <QObject>

using namespace stefanfrings;

class DeliverController : public HttpRequestHandler
{
  Q_OBJECT
  Q_DISABLE_COPY(DeliverController)
 public:

   /** Constructor */
   DeliverController();

   /** Generates the response */
   void service(HttpRequest& request, HttpResponse& response);

   QByteArray parseOrder();

 };

#endif // DELIVERCONTROLLER_H
