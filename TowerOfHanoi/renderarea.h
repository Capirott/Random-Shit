#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainterPath>
#include "towerofhanoi.h"
#include <QMessageBox>
#include <QPushButton>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea(TowerOfHanoi *, QPushButton*, QPushButton*, QWidget * = 0);
    void setTowerOfHanoi(TowerOfHanoi *obj) { this->obj = obj, update(); }

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void drawDisks(int, QPainter&);
    int calculateIndex(const QPoint&);

protected:
    TowerOfHanoi *obj;
    QPushButton *undo_Button;
    QPushButton *redo_Button;
    QRect disk_Form;
    QPoint position;
    QPoint previousPosition;
    int indexDisk;

};

#endif // RENDERAREA_H
