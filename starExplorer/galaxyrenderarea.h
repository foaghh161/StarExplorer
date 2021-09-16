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

#ifndef GALAXYRENDERAREA_H
#define GALAXYRENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QToolButton>
#include <QShortcut>
#include <QGenericMatrix>
#include <QSql>
#include <QSqlQuery>
#include <QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include <QGridLayout>
#include <vector>
#include "coordinates.h"

class GalaxyRenderArea : public QWidget
{
    Q_OBJECT

public:

    GalaxyRenderArea(QWidget *parent = 0);

    int getClosestId();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

signals:

    /**
     * @brief idChanged
     * Is emitted when a new star is choosen.
     * @param isChanged
     */
    void idChanged(bool isChanged);

public slots:

    /**
     * @brief zoomInSlot
     *  Zooms in by matrix multiplication with scaleMatrix and the updated
     *  matrix in the stars vector.
     */
    void zoomInSlot();

    /**
     * @brief zoomOutSlot
     *  Zooms out by matrix multiplication with invScaleMatrix and the updated
     *  matrix in the stars vector.
     */
    void zoomOutSlot();

    /**
     * @brief panUpSlot
     * Translates all coordinates down to move the "camera" up.
     */
    void panUpSlot();

    /**
     * @brief panDownSlot
     * Translates all coordinates up to move the "camera" down.
     */
    void panDownSlot();

    /**
     * @brief panLeftSlot
     * Translates all coordinates right to move the "camera" left.
     */
    void panLeftSlot();

    /**
     * @brief panRightSlot
     * Translates all coordinates left to move the "camera" right.
     */
    void panRightSlot();

    /**
     * @brief resetSlot
     * Set the updated matrix to the original matrix to reset the view.
     */
    void resetSlot();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGenericMatrix<4,4, qreal> scaleMatrix;
    QGenericMatrix<4,4, qreal> invScaleMatrix;
    QGenericMatrix<4,4, qreal> translationMatrix;

    std::vector<Coordinates> stars;

    QPen pen;
    QBrush brush;
    QPoint mousePoint;
    int closestId;

    QShortcut *zoomInShortcut;
    QShortcut *zoomOutShortcut;
    QShortcut *panUpShortcut;
    QShortcut *panDownShortcut;
    QShortcut *panLeftShortcut;
    QShortcut *panRightShortcut;

    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *panUpButton;
    QPushButton *panDownButton;
    QPushButton *panLeftButton;
    QPushButton *panRightButton;
    QPushButton *resetButton;

    /**
     * @brief retrieveCoords
     *  Queries the database and sets up the stars vector with retrived data
     *  Also determines color by string comparison on spect column.
     */
    void retrieveCoords();

    /**
     * @brief calcClosest
     * Finds the closest star to the input param by looping through all stars
     * and calculating the distance.
     * @param clickPoint
     * @return int the id of the closest star
     */
    int calcClosest(QPoint clickPoint);

    /**
     * @brief TESTFUNCTION
     * Tests pan up, down, left, right and zoom in and out slots.
     * Uses tolerance of 0.0001 to account for double precision loss
     */
    void TESTFUNCTION();
};


#endif // GALAXYRENDERAREA_H
