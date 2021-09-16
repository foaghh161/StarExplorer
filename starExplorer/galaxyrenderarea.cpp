/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "galaxyrenderarea.h"

#ifndef TRANSLATION_DIST
#define TRANSLATION_DIST 10
#endif // TRANSLATION_DIST
#ifndef SCALE_FACTOR
#define SCALE_FACTOR 1.25
#endif // SCALE_FACTOR

GalaxyRenderArea::GalaxyRenderArea(QWidget *parent): QWidget(parent)
{
    closestId = 0;
    scaleMatrix(0,0) = SCALE_FACTOR; // scale x
    scaleMatrix(1,1) = SCALE_FACTOR; // scale y
    scaleMatrix(2,2) = 1; // scale z
    scaleMatrix(3,3) = 1; // w

    invScaleMatrix(0,0) = 1/scaleMatrix(0,0);
    invScaleMatrix(1,1) = 1/scaleMatrix(1,1);
    invScaleMatrix(2,2) = 1/scaleMatrix(2,2);
    invScaleMatrix(3,3) = 1/scaleMatrix(3,3);

    translationMatrix.setToIdentity();

    retrieveCoords();

    // TESTFUNCTION();

    setBackgroundRole(QPalette::Background);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::black);
    setPalette(pal);

    setMouseTracking(true);

    zoomInShortcut = new QShortcut(QKeySequence(tr("+")), this);
    zoomOutShortcut = new QShortcut(QKeySequence(tr("-")), this);
    panUpShortcut = new QShortcut(QKeySequence(Qt::Key_Up), this);
    panDownShortcut = new QShortcut(QKeySequence(Qt::Key_Down), this);
    panLeftShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    panRightShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);

    zoomInButton = new QPushButton("+");
    zoomOutButton = new QPushButton("-");
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
    topHLayout->addWidget(zoomInButton);
    mainLayout->addLayout(topHLayout);
    QHBoxLayout *midHLayout = new QHBoxLayout;
    midHLayout->addStretch();
    midHLayout->addWidget(panLeftButton);
    midHLayout->addWidget(resetButton);
    midHLayout->addWidget(panRightButton);
    mainLayout->addLayout(midHLayout);
    QHBoxLayout *botHLayout = new QHBoxLayout;
    botHLayout->addStretch();
    botHLayout->addWidget(panDownButton);
    botHLayout->addWidget(zoomOutButton);
    mainLayout->addLayout(botHLayout);

    setLayout(mainLayout);

    connect(zoomInShortcut, SIGNAL(activated()), this, SLOT(zoomInSlot()));
    connect(zoomOutShortcut, SIGNAL(activated()), this, SLOT(zoomOutSlot()));
    connect(panUpShortcut, SIGNAL(activated()), this, SLOT(panUpSlot()));
    connect(panDownShortcut, SIGNAL(activated()), this, SLOT(panDownSlot()));
    connect(panLeftShortcut, SIGNAL(activated()), this, SLOT(panLeftSlot()));
    connect(panRightShortcut, SIGNAL(activated()), this, SLOT(panRightSlot()));

    connect(zoomInButton, SIGNAL(clicked(bool)), this, SLOT(zoomInSlot()));
    connect(zoomOutButton, SIGNAL(clicked(bool)), this, SLOT(zoomOutSlot()));
    connect(panUpButton, SIGNAL(clicked(bool)), this, SLOT(panUpSlot()));
    connect(panDownButton, SIGNAL(clicked(bool)), this, SLOT(panDownSlot()));
    connect(panLeftButton, SIGNAL(clicked(bool)), this, SLOT(panLeftSlot()));
    connect(panRightButton, SIGNAL(clicked(bool)), this, SLOT(panRightSlot()));

    connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetSlot()));




}

int GalaxyRenderArea::getClosestId()
{
    return closestId;
}

QSize GalaxyRenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize GalaxyRenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void GalaxyRenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.translate(width()/2, height()/2);
    painter.scale(1,-1);

    for(unsigned int i =0; i< stars.size(); i++)
    {
        if(stars.at(i).getNewX() < width()/2 && stars.at(i).getNewX() > -width()/2 &&
                stars.at(i).getNewY() < height()/2 && stars.at(i).getNewY() > -height()/2)
        {
            switch(stars.at(i).getColor())
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
            int sizeX = 5;
            int sizeY = 5;
            if(stars.at(i).getID()==50742)
            {
                painter.setBrush(QBrush(QColor(0,255,0)));
                painter.setPen(QPen(QColor(0,255,0)));
                sizeX = sizeY = 10;
            }
            painter.drawEllipse(stars.at(i).getNewX(),stars.at(i).getNewY(),sizeX,sizeY);
        }
    }
    painter.setBrush(QBrush(Qt::red));
    painter.setBrush(Qt::NoBrush);
}

void GalaxyRenderArea::mousePressEvent(QMouseEvent *event)
{
    mousePoint = event->pos();
    // Translate origo to center
    mousePoint.setX(mousePoint.x() - width()/2);
    mousePoint.setY((mousePoint.y() - height()/2)*-1);//Invert y-axis (y+ is up, x+ is right)
    if(event->button() == Qt::LeftButton)
    {
        closestId = calcClosest(mousePoint);
        emit idChanged(true);


    }
}

void GalaxyRenderArea:: zoomInSlot()
{
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewMatrix(stars[i].getNewMatrix()*scaleMatrix);
    }
    update();
}

void GalaxyRenderArea::zoomOutSlot()
{
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewMatrix(stars[i].getNewMatrix()*invScaleMatrix);
    }
    update();
}

void GalaxyRenderArea::panUpSlot()
{
    translationMatrix(3,1) = -TRANSLATION_DIST;
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewMatrix(stars[i].getNewMatrix()*translationMatrix);
    }
    update();
    translationMatrix(3,1) = 0;
}

void GalaxyRenderArea::panDownSlot()
{
    translationMatrix(3,1) = TRANSLATION_DIST;
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewMatrix(stars[i].getNewMatrix()*translationMatrix);
    }
    update();
    translationMatrix(3,1) = 0;
}

void GalaxyRenderArea::panLeftSlot()
{
    translationMatrix(3,0) = TRANSLATION_DIST;
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewMatrix(stars[i].getNewMatrix()*translationMatrix);
    }
    update();
    translationMatrix(3,0) = 0;
}

void GalaxyRenderArea::panRightSlot()
{
    translationMatrix(3,0) = -TRANSLATION_DIST;
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewMatrix(stars[i].getNewMatrix()*translationMatrix);
    }
    update();
    translationMatrix(3,0) = 0;
}

void GalaxyRenderArea::resetSlot()
{
    for(unsigned int i = 0; i < stars.size(); i++)
    {
        stars[i].setNewX(stars[i].getOrignialX());
        stars[i].setNewY(stars[i].getOrignialY());
        stars[i].setNewZ(stars[i].getOrignialZ());
    }
    update();
}

void GalaxyRenderArea::retrieveCoords()
{
    QSqlQuery q;
    q.prepare("select id,x,y,z,spect from star");
    if(q.exec())
    {
        while(q.next())
        {
            starColor color;
            if(q.value(4).toString() == ""){
                color = purple;
            } else if (q.value(4).toString().at(0) == "O") {
                color = blue;
            } else if (q.value(4).toString().at(0) == "B") {
                color = lightBlue;
            } else if (q.value(4).toString().at(0) == "A") {
                color = white;
            } else if (q.value(4).toString().at(0) == "F") {
                color = lightYellow;
            } else if (q.value(4).toString().at(0) == "G") {
                color = yellow;
            } else if (q.value(4).toString().at(0) == "K") {
                color = lightOrange;
            } else if (q.value(4).toString().at(0) == "M") {
                color = orange;
            } else {
                color = purple;
            }
            stars.push_back(Coordinates(q.value(0).toInt(),
                                        q.value(1).toDouble(),
                                        q.value(2).toDouble(),
                                        q.value(3).toDouble(),
                                        color));
        }
    }
}

int GalaxyRenderArea::calcClosest(QPoint clickPoint)
{
    double closestDist = 100000000;
    int closestID;
    for(unsigned int i = 0; i < stars.size(); i++){
        int x = stars.at(i).getNewX();
        int y = stars.at(i).getNewY();
        double dist = sqrt(pow((clickPoint.x()-x),2)+pow((clickPoint.y()-y),2));
        if(closestDist > dist){
            closestDist = dist;
            closestID = stars.at(i).getID();
        }
    }
    return closestID;


}
//////////////////////////////////////////////////////////////////
////////////////////////////// TEST //////////////////////////////
//////////////////////////////////////////////////////////////////
void GalaxyRenderArea::TESTFUNCTION()
{

    int testVar = 1;
    panUpSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewY()-(stars[i].getOrignialY()-TRANSLATION_DIST)) > 0.0001)
        {
            qDebug() << "PanUpTest Failed " <<i;
            qDebug() << stars[i].getNewY() <<" : "<< stars[i].getOrignialY()-TRANSLATION_DIST;
            testVar = 0;
        }
    }
    panDownSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewY()-stars[i].getOrignialY()) > 0.0001)
        {
            qDebug() << "PanDownTest Failed " <<i;
            qDebug() << stars[i].getNewY() <<" : "<< stars[i].getOrignialY();
            testVar = 0;
        }}
    panLeftSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewX()-(stars[i].getOrignialX()+TRANSLATION_DIST)) > 0.0001)
        {
            qDebug() << "PanLeftTest Failed " <<i;
            qDebug() << stars[i].getNewX() <<" : "<< stars[i].getOrignialX()+TRANSLATION_DIST;
            testVar = 0;
        }}
    panRightSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewX()-stars[i].getOrignialX()) > 0.0001)
        {
            qDebug() << "PanRightTest Failed " <<i;
            qDebug() << stars[i].getNewX() <<" : "<< stars[i].getOrignialX();
            qDebug() << stars[i].getNewX() - stars[i].getOrignialX();
            testVar = 0;
        }}
    zoomInSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewX()-stars[i].getOrignialX()*SCALE_FACTOR) > 0.0001 &&
                abs(stars[i].getNewY()-stars[i].getOrignialY()*SCALE_FACTOR) > 0.0001)
        {
            qDebug() << "ZoomInTest1 Failed "<<i;
            qDebug() << stars[i].getNewX() <<" : "<< stars[i].getOrignialX()*SCALE_FACTOR;
            qDebug() << stars[i].getNewY() <<" : "<< stars[i].getOrignialY()*SCALE_FACTOR;
            testVar = 0;
        }}
    zoomInSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewX()-stars[i].getOrignialX()*SCALE_FACTOR*SCALE_FACTOR) > 0.0001 &&
                abs(stars[i].getNewY()-stars[i].getOrignialY()*SCALE_FACTOR*SCALE_FACTOR) > 0.0001)
        {
            qDebug() << "ZoomInTest2 Failed "<<i;
            qDebug() << stars[i].getNewX() <<" : "<< stars[i].getOrignialX()*SCALE_FACTOR*SCALE_FACTOR;
            qDebug() << stars[i].getNewY() <<" : "<< stars[i].getOrignialY()*SCALE_FACTOR*SCALE_FACTOR;
            testVar = 0;
        }}
    zoomOutSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewX()-stars[i].getOrignialX()*SCALE_FACTOR) > 0.0001 &&
                abs(stars[i].getNewY()-stars[i].getOrignialY()*SCALE_FACTOR) > 0.0001)
        {
            qDebug() << "ZoomOutTest1 Failed "<<i;
            qDebug() << stars[i].getNewX() <<" : "<< stars[i].getOrignialX()*SCALE_FACTOR;
            qDebug() << stars[i].getNewY() <<" : "<< stars[i].getOrignialY()*SCALE_FACTOR;
            testVar = 0;
        }}
    zoomOutSlot();
    for(unsigned int i=0; i < stars.size(); i++){ // Test all stars
        if(abs(stars[i].getNewX()-stars[i].getOrignialX()) > 0.0001 &&
                abs(stars[i].getNewY()-stars[i].getOrignialY()) > 0.0001)
        {
            qDebug() << "ZoomOutTest2 Failed "<<i;
            qDebug() << stars[i].getNewX() <<" : "<< stars[i].getOrignialX();
            qDebug() << stars[i].getNewY() <<" : "<< stars[i].getOrignialY();
            testVar = 0;
        }
    }
    if(testVar)
    {
        qDebug() << "***************\n"
                    "TEST SUCCESSFUL\n"
                    "***************\n";
    }

}
