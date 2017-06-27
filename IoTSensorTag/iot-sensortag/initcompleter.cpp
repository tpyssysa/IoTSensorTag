#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "initcompleter.h"
#include "dataproviderpool.h"
#include "seriesstorage.h"
#include "demodataproviderpool.h"
#include "mockdataproviderpool.h"

InitCompleter::InitCompleter(QQmlApplicationEngine *engine, DataProviderPool *dataProviderPool, SeriesStorage *seriesStorage, const QString &mainFile, const QString &addressString, QObject *parent)
    : QObject(parent),
      m_mainFile(mainFile),
      m_addressString(addressString),
      m_dataProviderPool(dataProviderPool),
      m_seriesStorage(seriesStorage),
      m_engine(engine)
{
}

void InitCompleter::completeInitialization(int mode, const QString &address)
{
    if (1 == mode) {
        m_dataProviderPool = new DemoDataProviderPool;
        // List of devices used in Embedded World
        static_cast<SensorTagDataProviderPool*>(m_dataProviderPool)->setMacFilterList(QStringList() << address);
    }
    else {
        m_dataProviderPool = new MockDataProviderPool;
    }
    m_seriesStorage->setDataProviderPool(m_dataProviderPool);

    qmlRegisterType<SensorTagDataProvider>("SensorTag.DataProvider", 1, 0, "SensorTagData");
    qmlRegisterType<SensorTagDataProvider>("SensorTag.DataProvider", 1, 0, "ProviderState");
    qmlRegisterType<DataProviderPool>("SensorTag.DataProvider", 1, 0, "DataProviderPool");
    qmlRegisterType<SeriesStorage>("SensorTag.SeriesStorage", 1, 0, "SeriesStorage");
}

void InitCompleter::setMainWindowProperties()
{
    QObject *root = m_engine->rootObjects()[0];
    QQuickItem *item = root->findChild<QQuickItem *>("appMainWindow");
    if (item) {
        item->setProperty("dataProviderPool", QVariant::fromValue(m_dataProviderPool));
        item->setProperty("contentFile", m_mainFile);
        item->setProperty("seriesStorage", QVariant::fromValue(m_seriesStorage));
        item->setProperty("addresses", m_addressString);
    }
}
