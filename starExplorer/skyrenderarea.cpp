#include "skyrenderarea.h"

SkyRenderArea::SkyRenderArea(QWidget *parent) : QWidget(parent)
{
    scaleMatrix(0,0) = 41; // start zoom in scale x
    scaleMatrix(1,1) = 41; // start zoom in scale y
    scaleMatrix(2,2) = 41; // scale z
    scaleMatrix(3,3) = 1; // w

    translationMatrix.setToIdentity();

    summonCoord();
    for(unsigned int i=0; i<coorList.size(); i++){
        translationMatrix(3,0) = -centerX;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*translationMatrix);
        translationMatrix(3,0) = 0;
        translationMatrix(3,1) = -centerY;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*translationMatrix);
        translationMatrix(3,1) = 0;
        translationMatrix(3,2) = -centerZ;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*translationMatrix);;
        translationMatrix(3,2) = 0;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*scaleMatrix);
    }

    setBackgroundRole(QPalette::Background);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::black);
    setPalette(pal);

    setMouseTracking(true);

    panUpShortcut = new QShortcut(QKeySequence(Qt::Key_Up), this);
    panDownShortcut = new QShortcut(QKeySequence(Qt::Key_Down), this);
    panLeftShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    panRightShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);
    resetShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);

    panUpButton = new QPushButton(QString::fromUtf8("\u2191"));
    panDownButton = new QPushButton(QString::fromUtf8("\u2193"));
    panLeftButton = new QPushButton(QString::fromUtf8("\u2190"));
    panRightButton = new QPushButton(QString::fromUtf8("\u2192"));
    resetButton = new QPushButton(QString::fromUtf8("\u2302"));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    QHBoxLayout *topHLayout = new QHBoxLayout;
    topHLayout->addStretch();
    topHLayout->addWidget(panUpButton);
    topHLayout->addWidget(resetButton);
    mainLayout->addLayout(topHLayout);
    QHBoxLayout *midHLayout = new QHBoxLayout;
    midHLayout->addStretch();
    midHLayout->addWidget(panLeftButton);
    midHLayout->addWidget(panDownButton);
    midHLayout->addWidget(panRightButton);
    mainLayout->addLayout(midHLayout);

    setLayout(mainLayout);

    connect(panUpShortcut, SIGNAL(activated()), this, SLOT(panUpSlot()));
    connect(panDownShortcut, SIGNAL(activated()), this, SLOT(panDownSlot()));
    connect(panLeftShortcut, SIGNAL(activated()), this, SLOT(panLeftSlot()));
    connect(panRightShortcut, SIGNAL(activated()), this, SLOT(panRightSlot()));
    connect(resetShortcut, SIGNAL(activated()), this, SLOT(resetSlot()));

    connect(panUpButton, SIGNAL(clicked(bool)), this, SLOT(panUpSlot()));
    connect(panDownButton, SIGNAL(clicked(bool)), this, SLOT(panDownSlot()));
    connect(panLeftButton, SIGNAL(clicked(bool)), this, SLOT(panLeftSlot()));
    connect(panRightButton, SIGNAL(clicked(bool)), this, SLOT(panRightSlot()));

    connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetSlot()));
}

int SkyRenderArea::getClosestId()
{
    return closestId;
}

void SkyRenderArea::summonCoord()
{
    QSqlQuery query;
    query.exec("SELECT x, y, z, id, spect FROM star");
    query.next();
    while(query.next()){
        double X = query.value(0).toDouble();
        double Y = query.value(1).toDouble();
        double Z = query.value(2).toDouble();
        int id = query.value(3).toInt();
        starColor color;
        if(query.value(4).toString() == ""){
            color = purple;
        } else if (query.value(4).toString().at(0) == "O") {
            color = blue;
        } else if (query.value(4).toString().at(0) == "B") {
            color = lightBlue;
        } else if (query.value(4).toString().at(0) == "A") {
            color = white;
        } else if (query.value(4).toString().at(0) == "F") {
            color = lightYellow;
        } else if (query.value(4).toString().at(0) == "G") {
            color = yellow;
        } else if (query.value(4).toString().at(0) == "K") {
            color = lightOrange;
        } else if (query.value(4).toString().at(0) == "M") {
            color = orange;
        } else {
            color = purple;
        }
        Coordinates add(id,X,Y,Z,color);
        coorList.push_back(add);
    }
}


SkyRenderArea::~SkyRenderArea()
{

}

bool myCompare(Coordinates i, Coordinates j){
    return (i.getNewZ() < j.getNewZ());
}

void SkyRenderArea::paintEvent(QPaintEvent * /* event */){

    QPainter painter(this);
    painter.translate(width()/2, height()/2);
    sort(coorList.begin(), coorList.end(), myCompare);
    for(unsigned int i = 0; i<coorList.size(); i++){
        if(coorList.at(i).getNewX() < width()/2 && coorList.at(i).getNewX() > -width()/2 &&
                coorList.at(i).getNewY() < height()/2 && coorList.at(i).getNewY() > -height()/2)
        {
            int sizeX = 16;
            int sizeY = 16;
            if(coorList.at(i).getNewZ() < centerZ){
                if(coorList.at(i).getNewZ() < centerZ-10){sizeX = sizeY = 15;}
                if(coorList.at(i).getNewZ() < centerZ-20){sizeX = sizeY = 14;}
                if(coorList.at(i).getNewZ() < centerZ-30){sizeX = sizeY = 13;}
                if(coorList.at(i).getNewZ() < centerZ-40){sizeX = sizeY = 12;}
                if(coorList.at(i).getNewZ() < centerZ-50){sizeX = sizeY = 11;}
                if(coorList.at(i).getNewZ() < centerZ-60){sizeX = sizeY = 10;}
                if(coorList.at(i).getNewZ() < centerZ-70){sizeX = sizeY = 9;}
                if(coorList.at(i).getNewZ() < centerZ-80){sizeX = sizeY = 8;}
                if(coorList.at(i).getNewZ() < centerZ-90){sizeX = sizeY = 7;}
                if(coorList.at(i).getNewZ() < centerZ-100){sizeX = sizeY = 6;}
                switch(coorList.at(i).getColor())
                {
                case blue:
                    painter.setBrush(QBrush(QColor(0,102,153)));
                    painter.setPen(QPen(QColor(0,102,153)));
                    break;
                case lightBlue:
                    painter.setBrush(QBrush(QColor(102,255,255)));
                    painter.setPen(QPen(QColor(102,255,255)));
                    break;
                case white:
                    painter.setBrush(QBrush(QColor(255,255,255)));
                    painter.setPen(QPen(QColor(255,255,255)));
                    break;
                case lightYellow:
                    painter.setBrush(QBrush(QColor(255,255,153)));
                    painter.setPen(QPen(QColor(255,255,153)));
                    break;
                case yellow:
                    painter.setBrush(QBrush(QColor(255,255,0)));
                    painter.setPen(QPen(QColor(255,255,0)));
                    break;
                case lightOrange:
                    painter.setBrush(QBrush(QColor(255,133,51)));
                    painter.setPen(QPen(QColor(255,133,51)));
                    break;
                case orange:
                    painter.setBrush(QBrush(QColor(230,46,0)));
                    painter.setPen(QPen(QColor(230,46,0)));
                    break;
                case purple:
                    painter.setBrush(QBrush(QColor(255,0,255)));
                    painter.setPen(QPen(QColor(255,0,255)));
                    break;
                }
                painter.drawEllipse(coorList.at(i).getNewX(), coorList.at(i).getNewY(),
                                    sizeX, sizeY);
            }
            painter.setBrush(Qt::NoBrush);
        }
    }
}

void SkyRenderArea::mousePressEvent(QMouseEvent *event)
{
    mousePoint = event->pos();
    // Translate origo to center
    mousePoint.setX(mousePoint.x() - width()/2);
    mousePoint.setY((mousePoint.y() - height()/2)*-1);
    qDebug() << "MousePoint: " << mousePoint;
    if(event->button() == Qt::LeftButton)
    {
        closestId = calcClosest(mousePoint);
        emit idChanged(true);
    }
}

void SkyRenderArea::updateDotX(){
    double cosa1 = qCos(radX);
    double sina1 = qSin(radX);
    QGenericMatrix<4,4,qreal> rotx;
    //Matrix3x3 rotX = (1,     0,      0,  0,
    //                  0, cosa1, -sina1,  0,
    //                  0, sina1,  cosa1,  0,
    //                  0,     0,      0,  1);
    rotx(0,0) = (1);
    rotx(1,1) = cosa1;
    rotx(1,2) = -sina1;
    rotx(2,1) = sina1;
    rotx(2,2) = cosa1;
    rotx(3,3) = 1;
    for(unsigned int i = 0; i<coorList.size(); i++){
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*rotx);
    }
    update();
}

void SkyRenderArea::updateDotY(){
    double cosa2 = qCos(radY);
    double sina2 = qSin(radY);
    QGenericMatrix<4,4,qreal> roty;
    //    QMatrix3x3 rotY = (cosa2, 0, sina2, 0,
    //                           0, 1,     0, 0,
    //                      -sina2, 0, cosa2, 0,
    //                           0, 0,     0, 1);
    roty(0,0) = cosa2;
    roty(0,2) = sina2;
    roty(1,1) = 1;
    roty(2,0) = -sina2;
    roty(2,2) = cosa2;
    roty(3,3) = 1;
    for(unsigned int i = 0; i<coorList.size(); i++){
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*roty);
    }
    update();
}


void SkyRenderArea::panUpSlot()
{
    radX = -1.8*0.0174532925;
    updateDotX();
}

void SkyRenderArea::panDownSlot()
{
    radX = +1.8*0.0174532925;
    updateDotX();
}

void SkyRenderArea::panLeftSlot()
{
    radY = +1.8*0.0174532925;
    updateDotY();
}

void SkyRenderArea::panRightSlot()
{
    radY = -1.8*0.0174532925;
    updateDotY();
}

void SkyRenderArea::resetSlot()
{
    for(unsigned int i = 0; i < coorList.size(); i++)
    {
        coorList[i].setNewX(coorList[i].getOrignialX());
        coorList[i].setNewY(coorList[i].getOrignialY());
        coorList[i].setNewZ(coorList[i].getOrignialZ());
        QGenericMatrix<4,1, qreal> tempMatrix = coorList[i].getNewMatrix();
        tempMatrix(0,3) = 1;
        coorList[i].setNewMatrix(tempMatrix);
        translationMatrix(3,0) = -centerX;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*translationMatrix);
        translationMatrix(3,0) = 0;
        translationMatrix(3,1) = -centerY;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*translationMatrix);
        translationMatrix(3,1) = 0;
        translationMatrix(3,2) = -centerZ;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*translationMatrix);;
        translationMatrix(3,2) = 0;
        coorList.at(i).setNewMatrix(coorList.at(i).getNewMatrix()*scaleMatrix);
    }
    update();

}

int SkyRenderArea::calcClosest(QPoint clickPoint)
{
    double closestDist = 100000000;
    int closestID;
    int debugI;
    for(unsigned int i = 0; i < coorList.size(); i++){
        int x = coorList.at(i).getNewX();
        int y = coorList.at(i).getNewY();
        if(coorList.at(i).getNewZ() < centerZ)
        {
            double dist = sqrt(pow((clickPoint.x()-x),2)+pow((clickPoint.y()-y),2));
            if(closestDist > dist){
                closestDist = dist;
                closestID = coorList.at(i).getID();
                debugI = i;
            }
        }
    }
    qDebug() << "NewX: "<< coorList.at(debugI).getNewX()<<"O: "<<coorList.at(debugI).getOrignialX();
    qDebug() << "NewY: "<< coorList.at(debugI).getNewY()<<"O: "<<coorList.at(debugI).getOrignialY();
    qDebug() << "NewZ: "<< coorList.at(debugI).getNewZ()<<"O: "<<coorList.at(debugI).getOrignialZ();
    return closestID;


}
