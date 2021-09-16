#ifndef COORDINATES_H
#define COORDINATES_H

#include <QGenericMatrix>

/**
 * @brief The starColor enum is the color a star can be.
 */
enum starColor {
    blue,
    lightBlue,
    white,
    lightYellow,
    yellow,
    lightOrange,
    orange,
    purple  // Used when no color data available.
};

/**
 * @brief The Coordinates class holds the simple data for a star, used when drawing
 * in renderareas.
 */
class Coordinates{
private:
    QGenericMatrix<4,1, qreal> original;
    QGenericMatrix<4,1, qreal> updated;
    int id;
    starColor color;
public:
    double getNewX(){return updated(0,0);}
    double getNewY(){return updated(0,1);}
    double getNewZ(){return updated(0,2);}
    int getID(){return id;}
    starColor getColor(){return color;}
    double getOrignialX(){return original(0,0);}
    double getOrignialY(){return original(0,1);}
    double getOrignialZ(){return original(0,2);}
    QGenericMatrix<4,1, qreal> getNewMatrix(){return updated;}

    void setNewX(double x){updated(0,0) = x;}
    void setNewY(double y){updated(0,1) = y;}
    void setNewZ(double z){updated(0,2) = z;}
    void setNewMatrix(QGenericMatrix<4,1, qreal> newMat){updated = newMat;}
    Coordinates();
    Coordinates(int ID, double x, double y, double z, starColor col){
        id = ID;
        original(0,0) = updated(0,0) = x;
        original(0,1) = updated(0,1) = y;
        original(0,2) = updated(0,2) = z;
        original(0,3) = updated(0,3) = 1; // w
        color = col;

    }
};

#endif // COORDINATES_H
