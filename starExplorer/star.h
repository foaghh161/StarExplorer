#ifndef STAR_H
#define STAR_H
#include "db.h"
#include <QApplication>
#include <QSql>
#include <QSqlQuery>
#include <QDebug>
#include <QLabel>
#include "planet.h"
#include <QVector>

QT_BEGIN_NAMESPACE
class planet;
QT_END_NAMESPACE

/**
 * @brief The star class
 */
class star{
private:
    //[Variable map]
    QMap<QString,QString> varMap;
    QList<QString> varKeys;
    QVector<planet> planetVector;

public:
    star();
    ~star();

    // [get/set]
    QString getVar(QString key);
    void findPlanets();
    void setVar(QString key,QString val);

    QVector<int> getCurrentPlanetIds();
    void findStarByName(QString s);
    void findStarById(int id);
    QString getPlanetLabelString(int id);
};
#endif // STAR_H
