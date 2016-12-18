#ifndef MY_TREE_H
#define MY_TREE_H

#include <QtGui>
#include <QTreeWidget>
#include <QGraphicsScene>

#include "storage.h"
#include "my_item.h"

class My_scene ;

class My_tree : public QTreeWidget
{

    Q_OBJECT

private:
    My_scene* scene;
public:
    My_tree(My_scene *_scene, QWidget *parent = 0);
    void update(Ex_storage<Drawable_item*> & storage);
    virtual bool event(QEvent *e);

protected:
    void add_item(Drawable_item *item, int i, QTreeWidgetItem *parent = 0);

private slots:
    void notify();


};

#endif // MY_TREE_H
