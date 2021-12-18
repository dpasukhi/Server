#include <QCoreApplication>
#include "global.h"
#include "requestmapper.h"
#include <filelogger.h>
#include <staticfilecontroller.h>
#include <managercontroller.h>
#include <delivercontroller.h>
#include <customercontroller.h>'

RequestMapper::RequestMapper(QObject* parent)
  :HttpRequestHandler(parent)
{
  qDebug("RequestMapper: created");
}


RequestMapper::~RequestMapper()
{
  qDebug("RequestMapper: deleted");
}


void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
  QByteArray path=request.getPath();
  qDebug("RequestMapper: path=%s",path.data());

  // For the following pathes, each request gets its own new instance of the related controller.

  if (path.startsWith("/customer"))
  {
    CustomerController().service(request, response);
  }
  else if (path.startsWith("/manager"))
  {
    ManagerController().service(request, response);
  }
  else if (path.startsWith("/deliver"))
  {
    DeliverController().service(request, response);
  }
  // All other pathes are mapped to the static file controller.
  // In this case, a single instance is used for multiple requests.
  else
  {
    staticFileController->service(request, response);
  }

  qDebug("RequestMapper: finished request");

  // Clear the log buffer
  if (logger)
  {
    logger->clear();
  }
}
