#ifndef INITCOMPLETER_H
#define INITCOMPLETER_H

#include <QObject>

QT_FORWARD_DECLARE_CLASS(DataProviderPool)
QT_FORWARD_DECLARE_CLASS(SeriesStorage)
QT_FORWARD_DECLARE_CLASS(QQmlApplicationEngine)

class InitCompleter : public QObject
{
    Q_OBJECT
public:
    explicit InitCompleter(QQmlApplicationEngine *engine, DataProviderPool *dataProviderPool, SeriesStorage *seriesStorage, const QString &mainFile, const QString &addressString, QObject *parent = nullptr);

    Q_INVOKABLE void completeInitialization(int mode, const QString &address);
    Q_INVOKABLE void setMainWindowProperties();

private:
    QString m_sensorSource;
    QString m_mainFile;
    QString m_addressString;
    DataProviderPool *m_dataProviderPool;
    SeriesStorage *m_seriesStorage;
    QQmlApplicationEngine *m_engine;
};

#endif // INITCOMPLETER_H
