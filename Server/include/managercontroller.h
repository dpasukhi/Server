#ifndef MANAGERCONTROLLER_H
#define MANAGERCONTROLLER_H

#include <httprequesthandler.h>
#include <QObject>
using namespace stefanfrings;
class ManagerController : public HttpRequestHandler
{
  Q_OBJECT
  Q_DISABLE_COPY(ManagerController)
 public:

   /** Constructor */
   ManagerController();

   /** Generates the response */
   void service(HttpRequest& request, HttpResponse& response);
 };

#endif // MANAGERCONTROLLER_H
