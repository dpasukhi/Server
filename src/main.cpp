#include <QCoreApplication>

static const QString ORGANIZATION_NAME("UNN");
static const QString ORGANIZATION_DOMAIN("pizza.ru");
static const QString APPLICATION_NAME("Pizza for you Server");
static const QString SETTINGS_TRAY("settings/tray");

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
  QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
  QCoreApplication::setApplicationName(APPLICATION_NAME);

  QCoreApplication a(argc, argv);

  return a.exec();
}
