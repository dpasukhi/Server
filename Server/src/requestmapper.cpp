/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include "./include/global.h"
#include "./include/requestmapper.h"
#include "filelogger.h"
#include "staticfilecontroller.h"
#include "./include/dumpcontroller.h"
#include "./include/templatecontroller.h"
#include "./include/formcontroller.h"
#include "./include/fileuploadcontroller.h"
#include "./include/sessioncontroller.h"
#include "./include/logincontroller.h"

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

    if (path.startsWith("/dump"))
    {        
        DumpController().service(request, response);
    }

    else if (path.startsWith("/template"))
    {
        TemplateController().service(request, response);
    }

    else if (path.startsWith("/form"))
    {
        FormController().service(request, response);
    }

    else if (path.startsWith("/file"))
    {
        FileUploadController().service(request, response);
    }

    else if (path.startsWith("/session"))
    {
        SessionController().service(request, response);
    }

    else if (path.startsWith("/login"))
    {
        LoginController().service(request, response);
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
