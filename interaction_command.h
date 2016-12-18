#ifndef INTERACTION_COMMAND_H
#define INTERACTION_COMMAND_H

#include <QtCore>
#include <QStack>

#include <my_scene.h>
#include <my_view.h>
#include <my_tree.h>



class  Interaction_implementation
{
protected:
    My_scene *scene;
    My_view *view;
    My_tree *tree;
    QStack<Scene_memento*> interactions;
public:
    virtual bool apply_ellipse() = 0;
    virtual bool apply_triangle() = 0;
    virtual bool apply_rectangle() = 0;
    virtual bool apply_move(qreal x, qreal y) = 0;
    virtual bool apply_color(qreal r, qreal g, qreal b) = 0;
    virtual bool apply_mouse_press_event(QMouseEvent *event) = 0;
    virtual bool apply_key_press_event(QKeyEvent *event) = 0;
    virtual bool apply_delete() = 0;
    virtual bool apply_scale(qreal _x_fac, qreal _y_fac) = 0;
    virtual bool apply_group() = 0;
    virtual bool apply_degroup() = 0;
    virtual bool apply_save() = 0;
    virtual bool apply_load() = 0;


};

class Main_implementation : public Interaction_implementation
{
public:
    Main_implementation(My_scene *_scene, My_view *_view, My_tree *_tree);
    virtual bool apply_ellipse();
    virtual bool apply_triangle();
    virtual bool apply_rectangle();
    virtual bool apply_move(qreal _x, qreal _y);
    virtual bool apply_color(qreal _r, qreal _g, qreal _b);
    virtual bool apply_mouse_press_event(QMouseEvent *event) ;
    virtual bool apply_key_press_event(QKeyEvent *event) ;
    virtual bool apply_delete();
    virtual bool apply_scale(qreal _x_fac, qreal _y_fac) ;
    virtual bool apply_group() ;
    virtual bool apply_degroup();
    virtual bool apply_save() ;
    virtual bool apply_load() ;

};






#endif // INTERACTION_COMMAND_H
