#ifndef DB_CTRL_H
#define DB_CTRL_H



#include <QObject>
#include <QString>
#include <QtSql>

class DbController : public QObject
{
    Q_OBJECT
public:
    explicit DbController(QObject*);
    ~DbController();
    bool checkIfTableExists(QString);
    bool checkIfConnected();

public slots:
    void connectToServerRequested(QString, QString, QString, int, QString, QString, QString, bool);
    void disconnectFromServerRequested();
    void selectTableRequested(QString);
    void getTablesNamesRequested();

signals:
    void serverConnected();
    void serverErrorWithConnection(QString);
    void serverDisconnected();
    void tableSelected(QSqlQueryModel*);
    void gotTablesNames(QStringList);

private:
    bool connectToServerMSSQL(QString, QString, int, QString, QString, QString);
    bool connectToServerMSSQL(QString, QString, int, QString);
    bool connectToServerMySQL(QString, int, QString, QString, QString);
    void disconnectFromServer();
    QSqlQueryModel* selectTable(QString);
    QSqlError       getLastError();

    QSqlDatabase db;
    static const QString connection_string_sqlauth;
    static const QString connection_string_winauth;
};

#endif // DB_CONTROLLER_H
