#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QLineEdit>
#include <stdio.h>



QT_BEGIN_NAMESPACE
class QSqlDatabase;
class QSqlQuery;
class QSqlError;
class QLineEdit;
QT_END_NAMESPACE

class database
{
    QSqlDatabase db;
public:
    database();
    /**
     * @brief database::insertStar
     * "INSERT INTO" sql function
     * @param table, string of table name
     * @param values, string of values
     */
    void insertStar(QString table, QMap<QString, QLineEdit*>* values);
    /**
     * @brief database::insertPlanet
     * "INSERT INTO" sql function
     * @param table
     * @param values
     */
    void insertPlanet(QString table, QMap<QString, QLineEdit*>* values);
    /**
     * @brief database::deleteRow
     * Delete row with given id
     * @param table
     * @param id
     */
    void deleteRow(QString table, int id);
    /**
     * @brief updateTable
     * update table with a given condition
     * @param table
     * @param id
     * @param cond
     */
    void updateTable(QString table,int id,QString cond);

};

#endif // DB_H
