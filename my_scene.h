#ifndef MY_SCENE_H
#define MY_SCENE_H

#include <QtGui>
#include <QGraphicsView>

#include "my_item.h"
#include "storage.h"
#include "my_tree.h"


class Scene_memento             //memento that doesn't work at all, ayylmao
{
private:
    Storage<Drawable_item*> state;
public:
    Scene_memento();
    Storage<Drawable_item*> &get_state();
    void set_state(const Storage<Drawable_item*>& _state);
};



class My_scene : public QGraphicsScene
{
protected:
    Ex_storage<Drawable_item*> storage;  //exstorage is storage that contains storage inside it, best solution ever(no)
    qreal xmax, xmin, ymax, ymin;  //   coords that define the rectangle of selected items
    Item_creator *creator;   //creating a needle item, item stored in storage
    My_tree *tree;


    void unselect_selected();
    void make_obj(QPointF point);
    Scene_memento &create_memento();
    void pars_stroke(QString name, int &stroke, Container_item *container = 0);

public:
    My_scene(QObject *parent = NULL);
    void click_handle(QPointF position);
    void set_memento(Scene_memento &_state);
    void set_creator(Item_creator*_creator);
    void delete_selected();
    void set_color_selected(qreal _r, qreal _g, qreal _b);
    void move_selected(qreal x, qreal y);
    void add_to_selected(Drawable_item *item);
    void scale_selected(qreal _x_fac, qreal _y_fac);
    void clear_selected();
    void group_selected();
    void degroup();
    void save(QString name);
    void load(QString name);
    void set_tree(My_tree *_tree);
    void notify();
    void update(QList<QTreeWidgetItem *> &items);
    Drawable_item* get_item(int i);

};










#endif // MY_SCENE_H
