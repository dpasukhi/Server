#include "customercontroller.h"
#include <QDir>
#include <QDebug>
#include <global.h>
#include <handlerbd.h>
#include <QJsonObject>

CustomerController::CustomerController()
{

}

void CustomerController::service(HttpRequest& request,
                                 HttpResponse& response)
{
  QByteArray anOP = request.getHeader("Type");
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    return;
  if (anOP == "prod_list")
  {
//    QFile aFile;
//    QString aPath =  QDir::currentPath() +"/../../Server/Server/etc/templates/message.json";
//    aFile.setFileName(aPath);
//    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//      QByteArray myContent = aFile.readAll();
//      response.setHeader("Reply", "accepted");
//      response.write(myContent);
//    }
    QByteArray aMsg = parseProduct();
    response.setHeader("Reply", "accepted");
    response.write(aMsg);
  }
  else if (anOP == "authorization")
  {
    QString aLogin = request.getHeader("Login");
    QString aPassword = request.getHeader("Password");
    if (! aLogin.isEmpty() && !aPassword.isEmpty() &&
        aWorker->checkClient(aLogin, aPassword))
    {
      response.setHeader("Reply", "accepted");
    }
  }
  else if (anOP == "registration")
  {
    HandlerBD::clientTable aClient;
    aClient.email = request.getHeader("Login");
    aClient.pass = request.getHeader("Password");
    aClient.first_name = request.getHeader("Name");
    aClient.middle_name = request.getHeader("MiddleName");
    aClient.last_name = request.getHeader("LastName");
    aClient.phone = request.getHeader("Phone");
    //Client.email = request.getHeader("Email");
    if (aClient.email.isEmpty())
    {
      return;
    }
    aClient.id_client = ClientNewID();
    aWorker->clientTable_insert(aClient);
    response.setHeader("Reply", "accepted");
  }
  else if (anOP == "office_list")
  {
//    QFile aFile;
//    QString aPath =  QDir::currentPath() + "/../../Server/Server/etc/templates/office.json";
//    aFile.setFileName(aPath);
//    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//      QByteArray myContent = aFile.readAll();
//      response.setHeader("Reply", "accepted");
//      response.write(myContent);
//    }
    QByteArray aMsg = parseOffices();
    response.setHeader("Reply", "accepted");
    response.write(aMsg);
  }
  else if (anOP == "order_send")
  {
    QByteArray aMsg = request.getBody();
    OrderSet aSet =  parseOrder(aMsg);
    ContentOrder(aSet, request);
    response.setHeader("Reply", "accepted");
  }
}

QByteArray CustomerController::parseProduct()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    QByteArray();
  QJsonArray jsonArray;
  QVector<HandlerBD::productsTable> aProducts =
      aWorker->productsTable_getAll();
  foreach (const HandlerBD::productsTable & value, aProducts)
  {
    QJsonObject anObj;
    anObj.insert("name", value.pizza_name);
    anObj.insert("description", value.description);
    anObj.insert("price", QString::number(value.cost));
    anObj.insert("id", value.id);
    QJsonValue aValue(anObj);
    jsonArray.append(aValue);
  }
  QJsonObject json;
  json.insert("pizza", jsonArray);
  QJsonDocument aDoc(json);
  return aDoc.toJson();
}

QByteArray CustomerController::parseOffices()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    QByteArray();
  QJsonArray jsonArray;
  QVector<HandlerBD::locationTable> anOffices =
      aWorker->locationTable_getAll();
  foreach (const HandlerBD::locationTable & value, anOffices)
  {
    QJsonObject anObj;
    anObj.insert("name", value.office);
    anObj.insert("adress", value.office);
    anObj.insert("id", value.id_office);
    QJsonValue aValue(anObj);
    jsonArray.append(aValue);
  }
  QJsonObject json;
  json.insert("office", jsonArray);
  QJsonDocument aDoc(json);
  return aDoc.toJson();
}

CustomerController::OrderSet CustomerController::parseOrder(const QByteArray& theJson)
{
  QJsonDocument doc = QJsonDocument::fromJson(theJson);
  CustomerController::OrderSet aSet;
  if (doc.isObject())
  {
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["order"].toArray();
    foreach (const QJsonValue & value, jsonArray)
    {
      if (value.isObject())
      {
        QJsonObject obj = value.toObject();
        aSet.myOrderID.push_back(obj["order_id"].toInt());
        aSet.myOrderAdress = obj["order_adress"].toString();
        aSet.myOrderOfficeID = obj["order_office_id"].toInt();
        aSet.mySumPrice = obj["order_sum_price"].toInt();
        aSet.myOrderCount += 1;
      }
    }
  }
  return aSet;
}

void CustomerController::ContentOrder(const CustomerController::OrderSet& theSet,
                                      HttpRequest& request)
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    return;
  HandlerBD::orderTable anOrder;
  anOrder.id = OrderNewID();
  anOrder.status = "0";
  anOrder.id_client = 1;
  QVector<HandlerBD::clientTable> aClients =
      aWorker->clientTable_getAll();
  QString aLogin = request.getHeader("Login");
  foreach(const HandlerBD::clientTable& aValue, aClients)
  {
    if (aValue.email == aLogin)
    {
      anOrder.id_client = aValue.id_client;
      break;
    }
  }
  anOrder.adress = theSet.myOrderAdress;
  anOrder.id_office = theSet.myOrderOfficeID;
  QDateTime current_date_time =QDateTime::currentDateTime();
  QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
  anOrder.timeStart = current_date;
  aWorker->orderTable_insert(anOrder);
  foreach(const qint32 aValue, theSet.myOrderID)
  {
    HandlerBD::orderCompilationTable aListOrders;
    aListOrders.id = OrderCompilationNewID();
    aListOrders.id_order = anOrder.id;
    aListOrders.id_pizza = aValue;
    aWorker->orderCompilationTable_insert(aListOrders);
  }
  HandlerBD::clientDeliverymanTable aSupport;
  aSupport.id_client = anOrder.id_client;
  aSupport.id_office = anOrder.id_office;
  aSupport.id_order = anOrder.id;
  aWorker->clientDeliverymanTable_insert(aSupport);
}

qint32 CustomerController::ClientNewID()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    return -1;
  QVector<HandlerBD::clientTable> aClients =
      aWorker->clientTable_getAll();
  qint32 anID = aClients.isEmpty() ? 1 : 0;
  qint32 aTempID = 1;
  while (anID == 0)
  {
    foreach(const HandlerBD::clientTable& aValue, aClients)
    {
      if (aTempID == aValue.id_client)
      {
        aTempID++;
      }
      else
      {
        anID = aTempID;
        break;
      }
    }
  }
  return anID;
}

qint32 CustomerController::OrderNewID()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    return -1;
  QVector<HandlerBD::orderTable> anOrders =
      aWorker->orderTable_getAll();
  qint32 anID = anOrders.isEmpty() ? 1 : 0;
  qint32 aTempID = 1;
  while (anID == 0)
  {
    foreach(const HandlerBD::orderTable& aValue, anOrders)
    {
      if (aTempID == aValue.id)
      {
        aTempID++;
      }
      else
      {
        anID = aTempID;
        break;
      }
    }
  }
  return anID;
}

qint32 CustomerController::OrderCompilationNewID()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    return -1;
  QVector<HandlerBD::orderCompilationTable> anOrders =
      aWorker->orderCompilationTable_getAll();
  qint32 anID = anOrders.isEmpty() ? 1 : 0;
  qint32 aTempID = 1;
  while (anID == 0)
  {
    foreach(const HandlerBD::orderCompilationTable& aValue, anOrders)
    {
      if (aTempID == aValue.id)
      {
        aTempID++;
      }
      else
      {
        anID = aTempID;
        break;
      }
    }
  }
  return anID;
}
