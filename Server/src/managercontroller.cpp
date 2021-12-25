#include "managercontroller.h"
#include <QDir>
#include <QDebug>
#include <global.h>
#include <handlerbd.h>
#include <QJsonObject>

ManagerController::ManagerController()
{

}

void ManagerController::service(HttpRequest& request, HttpResponse& response)
{
  QByteArray anOP = request.getHeader("Type");
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    return;
  if (anOP == "authorization")
  {
    QString aLogin = request.getHeader("Login");
    QString aPassword = request.getHeader("Password");
    if (! aLogin.isEmpty() && !aPassword.isEmpty() &&
        aWorker->checkClient(aLogin, aPassword))
    {
      response.setHeader("Reply", "accepted");
    }
  }
  else if (anOP == "order_list")
  {
    QByteArray aMsg = parseOrder();
    response.setHeader("Reply", "accepted");
    response.write(aMsg);
  }
  else if (anOP == "order_remove")
  {
    QString anID = request.getHeader("ID");
    QVector<HandlerBD::orderTable> anOrdors = aWorker->orderTable_getAll();
    HandlerBD::orderTable anOreder;
    foreach(const HandlerBD::orderTable& aValue, anOrdors)
    {
      if (aValue.id == anID.toInt())
      {
        anOreder = aValue;
        aWorker->orderTable_delete(anOreder);
        break;
      }
    }
    QVector<HandlerBD::clientDeliverymanTable> aSpec = aWorker->clientDeliverymanTable_getAll();
    foreach(HandlerBD::clientDeliverymanTable aValue, aSpec)
    {
      if (aValue.id_order == anID.toInt())
      {
        aWorker->clientDeliverymanTable_delete(aValue);
        break;
      }
    }
    response.setHeader("Reply", "accepted");
  }
}

QByteArray ManagerController::parseOrder()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    QByteArray();
  QJsonArray jsonArray;
  QVector<HandlerBD::orderTable> anOrdors = aWorker->orderTable_getAll();
  foreach (const HandlerBD::orderTable & value, anOrdors)
  {
    QJsonObject anObj;
    QVector<HandlerBD::locationTable> anoffices = aWorker->locationTable_getAll();
    QString anOf("Offic 1");
    foreach(const HandlerBD::locationTable aSubValue, anoffices)
    {
      if (aSubValue.id_office == value.id_office)
      {
        anOf = aSubValue.office;
        break;
      }
    }
    qint32 delID = 1, custID = 1;
    QVector<HandlerBD::clientDeliverymanTable> aSpec = aWorker->clientDeliverymanTable_getAll();
    foreach(HandlerBD::clientDeliverymanTable aValue, aSpec)
    {
      if (aValue.id_order == value.id)
      {
        delID = aValue.id_deliver;
        custID = aValue.id_client;
        break;
      }
    }
    QVector<HandlerBD::deliverymanTable> aDelivers =
        aWorker->deliverymanTable_getAll();
    QString delName = "Name";
    foreach(const HandlerBD::deliverymanTable& aValue, aDelivers)
    {
      if (aValue.id_deliver == delID)
      {
        delName = aValue.first_name +  " " + aValue.last_name;
        break;
      }
    }
    QVector<HandlerBD::clientTable> aCleints =
        aWorker->clientTable_getAll();
    QString cliName = "Name";
    foreach(const HandlerBD::clientTable& aValue, aCleints)
    {
      if (aValue.id_client == custID)
      {
        cliName = aValue.first_name +  " " + aValue.last_name;
        break;
      }
    }
    anObj.insert("name", anOf);
    anObj.insert("id_order", value.id);
    anObj.insert("office_adress", anOf);
    anObj.insert("order_adress", value.adress);
    anObj.insert("data_order", anOf);
    anObj.insert("name_deliver", delName);
    anObj.insert("name_client", cliName);
    QJsonValue aValue(anObj);
    jsonArray.append(aValue);
  }
  QJsonObject json;
  json.insert("orders", jsonArray);
  QJsonDocument aDoc(json);
  return aDoc.toJson();
}
