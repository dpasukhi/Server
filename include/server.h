#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <qtservice.h>

class Server : public QObject
{
  Q_OBJECT
public:
  explicit Server(QObject *parent = nullptr);

signals:

};

#endif // SERVER_H
