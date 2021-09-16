#ifndef PLANET_H
#define PLANET_H

#include <QApplication>
#include "star.h"

/**
 * @brief The planet class
 */
class planet
{
private:
    QMap<QString,QString> planetMap;


public:
    planet();
    QList<QString> planetList;
    QString getVar(QString key) const;
    void setVar(QString key,QString val);
};

#endif // PLANET_H
