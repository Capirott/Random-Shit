#include "renderarea.h"
#include <iostream>

#define NUMBER_MAX_DISKS 7

RenderArea::RenderArea(TowerOfHanoi *obj, QPushButton *undo, QPushButton *redo, QWidget *parent)
    : QWidget(parent), obj(obj), undo_Button(undo), redo_Button(redo)
{
    setMouseTracking(true);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    position = QPoint(0,0);
//    undo_Button->setDisabled(true);
//    redo_Button->setDisabled(true);
    indexDisk = -1;
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor("#102372")));
    int w = width();
    int h = height();
    int horizontalSpacer = w / 4;
    painter.drawRect(0, h * 0.90, w, h * 0.10); // ~ Ground
    for (int i = 1; i < 4; ++i)
    {
        painter.drawRect(i * horizontalSpacer - w * 0.015 / 2, h * 0.1, w * 0.015, h * 0.8);
        drawDisks(i - 1, painter);
    }
    painter.save();
    if (indexDisk != -1)
    {
        int w = width();
        int h = height();
        int diskW = w / 50;
        int diskH = h * 0.1;
        char tmp = obj->getTopTower(indexDisk);
        QRect disk(0, 0, (tmp) * diskW, diskH);
        painter.setBrush(Qt::transparent);
        painter.setOpacity(0.5);
        for (int i = 1; i < 4; ++i)
        {
            if (obj->is_TowerEmpty(i - 1) || obj->getTopTower(i - 1) > obj->getTopTower(indexDisk))
                painter.drawRect((i) * horizontalSpacer - (NUMBER_MAX_DISKS) * diskW / 2, h * 0.1,(NUMBER_MAX_DISKS) * diskW, h * 0.8);
        }
        painter.setOpacity(1);
        painter.setBrush(Qt::green);
        painter.translate(position);
        painter.drawRect(disk);
        painter.translate(-position);
    }
    painter.restore();
    painter.drawText(QRectF(0, 0, width() - 50, height() - 50), QString("Moves: " + QString::number(obj->getN_Moves()) + "\nMin: " + QString::number(pow(2, obj->getN_Disk()) - 1)));
}

void RenderArea::mousePressEvent(QMouseEvent *e)
{
    if (indexDisk != -1 || obj->tower3IsComplete())
        return;
    int index = calculateIndex(e->pos());
    if (index != -1)
    {
        indexDisk = index;
        previousPosition = e->pos();
        update();
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *e)
{

    if (indexDisk != -1)
    {
        position += e->pos() - previousPosition;
        previousPosition = e->pos();
        update();
    }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *e)
{
    if (indexDisk != -1)
    {
        position += e->pos() - previousPosition;
        int index = calculateIndex(e->pos());
        int tmp = indexDisk;
        indexDisk = -1;
        if (index != -1)
        {
            obj->moveDisk(tmp, index);
            if (obj->tower3IsComplete())
                QMessageBox::information(this, tr("Game over"), tr("Congratulations, you win!"));
            }
        }
        update();
}

void RenderArea::drawDisks(int index, QPainter &painter)
{
    int w = width();
    int h = height();
    int horizontalSpacer = w / 4;
    int diskW = w / 50;
    int diskH = h * 0.1;
    painter.save();
    painter.setBrush(Qt::red);
    int n;
    char *tmp = obj->getTower(index, n);

    for (int i = (index == indexDisk ? 1 : 0); i < n; ++i)
       painter.drawRect((index + 1) * horizontalSpacer - (tmp[i]) * diskW / 2, h - (diskH * (n - i + 1)),  (tmp[i]) * diskW, diskH);
    painter.restore();
}


int RenderArea::calculateIndex(const QPoint &point)
{
    int w = width();
    int h = height();
    int horizontalSpacer = w / 4;
    int diskW = w / 50;
    int diskH = h * 0.1;

    if (indexDisk == -1)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (!obj->is_TowerEmpty(i))
            {
                char tmp = obj->getTopTower(i);
                QRect disk(0, 0, (tmp) * diskW, diskH);
                QPoint p((i + 1) * horizontalSpacer - (tmp) * diskW / 2, h - (diskH * (obj->getTowerNDisk(i) + 1)));
                if (disk.contains(point - p))
                {
                    position = p;
                    return i;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 3; ++i)
        {
            QRect disk(0, 0, (NUMBER_MAX_DISKS) * diskW, h * 0.8);
            QPoint P((i + 1) * horizontalSpacer - (NUMBER_MAX_DISKS) * diskW / 2, h * 0.1);
            if (disk.translated(P).contains(point))
                return i;
        }
    }
    return -1;
}
