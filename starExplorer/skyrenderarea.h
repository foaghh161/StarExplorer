#ifndef SKYRENDERAREA_H
#define SKYRENDERAREA_H

//#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <math.h>
#include "coordinates.h"
#include <QSqlDatabase>
#include <QShortcut>
#include <QPushButton>
#include <QMouseEvent>
#include <QMatrix>
#include <QSqlQuery>
#include <algorithm>
#include <QGridLayout>

/**
 * @brief The SkyRenderArea class handles the render area used in skyViewGroupBox.
 */
class SkyRenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit SkyRenderArea(QWidget *parent = 0);
    ~SkyRenderArea();

    void updateDotX();
    void updateDotY();
    void summonCoord();
    int getClosestId();
    void setCenterX(double x){centerX = x;}
    void setCenterY(double y){centerY = y;}
    void setCenterZ(double z){centerZ = z;}

signals:
    void idChanged(bool isChanged);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:


public slots:
    void panUpSlot();
    void panDownSlot();
    void panLeftSlot();
    void panRightSlot();
    void resetSlot();

private:
    double centerX;
    double centerY;
    double centerZ;

    double radX = 0;
    double radY = 0;
    double gradient = 3.6*0.0174532925;
    std::vector<Coordinates> coorList;
    QGenericMatrix<4,4, qreal> scaleMatrix;
    QGenericMatrix<4,4, qreal> invScaleMatrix;
    QGenericMatrix<4,4, qreal> translationMatrix;

    int calcClosest(QPoint clickPoint);
    QPoint mousePoint;
    int closestId;

    QShortcut *panUpShortcut;
    QShortcut *panDownShortcut;
    QShortcut *panLeftShortcut;
    QShortcut *panRightShortcut;
    QShortcut *resetShortcut;
    QPushButton *panUpButton;
    QPushButton *panDownButton;
    QPushButton *panLeftButton;
    QPushButton *panRightButton;
    QPushButton *resetButton;
};

#endif // SKYRENDERAREA_H
