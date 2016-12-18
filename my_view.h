#ifndef MY_VIEW_H
#define MY_VIEW_H

#include <QtGui>
#include <QGraphicsView>
#include <my_scene.h>


class My_view :public QGraphicsView
{
public:
    My_view(QWidget *parent = NULL);
    void mouse_press(QMouseEvent* event);
};

#endif // MY_VIEW_H
