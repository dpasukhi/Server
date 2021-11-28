#include "serverapi.h"

class ServerAPIData : public QSharedData
{
public:

};

ServerAPI::ServerAPI() : data(new ServerAPIData)
{

}

ServerAPI::ServerAPI(const ServerAPI &rhs) : data(rhs.data)
{

}

ServerAPI &ServerAPI::operator=(const ServerAPI &rhs)
{
  if (this != &rhs)
    data.operator=(rhs.data);
  return *this;
}

ServerAPI::~ServerAPI()
{

}
