#include "delivercontroller.h"
#include <QDir>
#include <QDebug>
#include <global.h>
#include <handlerbd.h>
#include <QJsonObject>

DeliverController::DeliverController()
{

}

void DeliverController::service(HttpRequest& request, HttpResponse& response)
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
        aWorker->checkDeliveryman(aLogin, aPassword))
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
  else if (anOP == "status_send")
  {
    QString anID = request.getHeader("ID");
    qint32 anOrID = anID.toInt();
    QVector<HandlerBD::orderTable> anOrdors = aWorker->orderTable_getAll();
    HandlerBD::orderTable anOreder;
    foreach(const HandlerBD::orderTable& aValue, anOrdors)
    {
      if (aValue.id == anOrID)
      {
        anOreder = aValue;
        break;
      }
    }
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    anOreder.status = "2";
    anOreder.timeEnd = current_date;
    aWorker->orderTable_update(anOreder);
    QVector<HandlerBD::clientDeliverymanTable> aSpec = aWorker->clientDeliverymanTable_getAll();
    QVector<HandlerBD::deliverymanTable> aDelivers =
        aWorker->deliverymanTable_getAll();
    QString aLogin = request.getHeader("Login");
    int ID = 1;
    foreach(const HandlerBD::deliverymanTable& aValue, aDelivers)
    {
      if (aValue.email == aLogin)
      {
        ID = aValue.id_deliver;
        break;
      }
    }
    foreach(HandlerBD::clientDeliverymanTable aValue, aSpec)
    {
      if (aValue.id_order == anID.toInt())
      {
        aValue.id_deliver = ID;
        aWorker->clientDeliverymanTable_update(aValue);
        break;
      }
    }
    response.setHeader("Reply", "accepted");
  }
}

QByteArray DeliverController::parseOrder()
{
  HandlerBD* aWorker = db->GetWorker();
  if (aWorker == nullptr)
    QByteArray();
  QJsonArray jsonArray;
  QVector<HandlerBD::orderTable> anOrdors = aWorker->orderTable_getAll();
  foreach (const HandlerBD::orderTable & value, anOrdors)
  {
    if (value.status == "2")
      continue;
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
    anObj.insert("name", anOf);
    anObj.insert("id_office", value.id_office);
    anObj.insert("office_adress", anOf);
    anObj.insert("order_adress", value.adress);
    anObj.insert("id_order", value.id);
    QJsonValue aValue(anObj);
    jsonArray.append(aValue);
  }
  QJsonObject json;
  json.insert("orders", jsonArray);
  QJsonDocument aDoc(json);
  return aDoc.toJson();
}
