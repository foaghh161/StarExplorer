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

#include "systemrenderarea.h"

SystemRenderArea::SystemRenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Background);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::black);
    setPalette(pal);
}


void SystemRenderArea::paintEvent(QPaintEvent * /* event */)
{
    painter = new QPainter(this);
    painter->drawRect(QRect(0, 0, width() - 1, height() - 1));
    painter->setPen(palette().dark().color());
    painter->setBrush(Qt::NoBrush);

    // center origin (0,0) to middle of widget
    painter->translate(width()/2, height()/2);

    // draw center star
    stellarPositions.clear();

    painter->setBrush(getTypeColor());
    painter->setPen(getTypeColor());
    int starSize = width()/10;
    // shadows
    // painter->setOpacity(0.6);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    drawStar(starSize,getTypeColor());

    //add position of star into vector with positions of stellar bodies
    QVector<int> POS;
    POS.push_back(0);
    POS.push_back(0);
    stellarPositions.push_back(POS);

    //SETTINGS
    int vectorSize = 0; //amount of planets/stars
    vectorSize = currentPlanetIds.size();

    int planetsize;
    if(vectorSize % 2 == 0 && vectorSize > 0){//if we have even number of stellar bodies the painter will do fine
        planetsize = ((width()-(starSize*2))/vectorSize);
    }else{ //uneven amount of stellar bodies, then we have to force painter to consider as even to paint one more on one side just instead of split a body in half
        planetsize = ((width()-(starSize*2))/(vectorSize+1));
    }

    int drawPlanetSize = starSize/3;

    int startx = -1*((width())/2+1); //furthest to the left after translation (where to start painting stellar bodies)
    int insideStarPush = 0; //amount to add to x-coordinate in stellar bodies which are going to be to the right of the center star
    for (int i = 0; i < vectorSize;i++){
        int tempx = startx + i*planetsize + planetsize/2;
        while(tempx+insideStarPush <= starSize+(planetsize/2) && tempx+insideStarPush >= -starSize-(planetsize/2)){
            insideStarPush += 1;
        }

        if(currentPlanetIds.at(i) >= 3718 && currentPlanetIds.at(i) <= 3726){ //Our solar system
            QColor col;
            if(currentPlanetIds.at(i) == 3718){
                col.setRgb(169,169,169);
                drawPlanet(-starSize-50,0,col,starSize/25,i); // Merc
            }
            if(currentPlanetIds.at(i) == 3719){
                col.setRgb(255,250,205);
                drawPlanet(-starSize-100,0,col,starSize/15,i); //Venus
            }
            if(currentPlanetIds.at(i) == 3720){
                col.setRgb(135,150,250);
                drawPlanet(-starSize-150,0,col,starSize/15,i);  //Earth
            }
            if(currentPlanetIds.at(i) == 3721){
                col.setRgb(155,0,0);
                drawPlanet(-starSize-200,0,col,starSize/18,i);  //Mars
            }
            if(currentPlanetIds.at(i) == 3722){
                col.setRgb(139,0,0);
                drawPlanet(-starSize-300,0,col,starSize/5,i);   //Jupiter
            }
            if(currentPlanetIds.at(i) == 3723){
                col.setRgb(255,255,51);
                drawPlanet(-starSize-400,0,col,starSize/8,i);//Saturnus
            }
            if(currentPlanetIds.at(i) == 3724){
                col.setRgb(173,216,230);
                drawPlanet(-starSize-450,0,col,starSize/11,i);//Uranus
            }
            if(currentPlanetIds.at(i) == 3725){
                col.setRgb(30,144,255);
                drawPlanet(-starSize-500,0,col,starSize/11,i);//Neptune
            }
            if(currentPlanetIds.at(i) == 3726){
                col.setRgb(169,169,169);
                drawPlanet(-starSize-550,0,col,starSize/35,i);  //Pluto
            }
        }
        else {
            drawPlanet(tempx+insideStarPush,0,Qt::red,drawPlanetSize,i);
        }
    }
}

void SystemRenderArea::drawStar(int size, QColor col){
    size = size*50; //how big the star should be halfway through the layers
    painter->setBrush(QBrush(col));
    painter->setPen(QPen(col));
    painter->drawEllipse(QPoint(0,0),size/1000,size/1000);
    for(double i = 1; i < 1000;i++){

        painter->setOpacity(i/1000);    //1,0.9...0.1
        painter->drawEllipse(QPoint(0,0),size/i,size/i);
    }
    painter->setOpacity(1); //reset
}

void SystemRenderArea::drawPlanet(int x, int y, QColor col, int pSize,int i){
    QVector<int> tmppos;
    painter->setBrush(QBrush(col));
    painter->setPen((QPen(col)));

    tmppos.push_back((x)); //x coord
    tmppos.push_back(y);   //y coord
    tmppos.push_back(currentPlanetIds.at(i));
    stellarPositions.push_back(tmppos);

    painter->setOpacity(1);
    painter->drawEllipse(QPoint(x,y),pSize,pSize);
}

int SystemRenderArea::calcDist(int x1,int y1,int x2,int y2){
    return qSqrt(qPow(x1-x2,2) + qPow(y1-y2,2)); //distance between two points
}

void SystemRenderArea::mousePressEvent(QMouseEvent *ev) {
    int x = ev->x();
    int y = ev->y();
    qDebug() << x << "," << y;

    int currentStellarSize = (width()/10)/3; //radie of current stellar body
    int starSize = width()/10;

    if(calcDist(x,y,(width()/2),(height()/2)) <= starSize){ //Clicked inside the center star
        qDebug() << "Clicked inside the center star";
        curPlanetId = -1;
        emit systemLabelChanged(true);
        return;
    }

    for (int i = 1;i<stellarPositions.size();i++){//iterate through all stellar bodies and check if clicked within the area of any of them
        QVector<int> curpos;
        qDebug() << "size of stellarPositions: " << stellarPositions.size();
        int tmpx = stellarPositions.at(i).at(0);
        int tmpy = stellarPositions.at(i).at(1);
        qDebug() << "tmpx,tmpy: " << tmpx << "," << tmpy;
        qDebug() << "i = " << i;


        if(calcDist(tmpx,tmpy,x-(width()/2),y-(height()/2)) <= currentStellarSize){ //Clicked inside a stellar body that is not the center star
            qDebug() << "Clicked inside stellar body " << i << ":" << curPlanetId;
            curPlanetId = stellarPositions.at(i).at(2);
            emit systemLabelChanged(true);
            return;
        }
    }
    qDebug() << "Clicked on nothing";
    curPlanetId = -2;
    emit systemLabelChanged(true);
}


void SystemRenderArea::setStarType(QString t){
    starType = t;
}
QColor SystemRenderArea::getTypeColor(){
    QColor q;
    if(starType == "No record"){
        q.setRgb(255,0,255);   //purple
        return q;
    }

    if(starType.startsWith("O")){
        q.setRgb(0,102,153);
        q.setRgb(0,102,153);     //Dark blue
        return q;
    }

    if(starType.startsWith("B")){
        q.setRgb(0,135,190);    //Light blue
        return q;
    }
    if(starType.startsWith("A")){   //White
        q.setRgb(255,255,255);
        return q;
    }
    if(starType.startsWith("F")){
        q.setRgb(255,255,153);  //Light yellow
        return q;
    }
    if(starType.startsWith("G")){
        q.setRgb(255,255,0);   //Yellow
        return q;
    }
    if(starType.startsWith("K")){
        q.setRgb(255,133,51);     //Light red
        return q;
    }
    if(starType.startsWith("M")){
        q.setRgb(230,46,0);     //Red
        return q;
    }
    else{
        q.setRgb(255,255,0);
        return q;
    }
}


void SystemRenderArea::setPlanetIds(QVector<int> v){
    currentPlanetIds = v;
}

int SystemRenderArea::getPlanetId(){
    return curPlanetId;
}
