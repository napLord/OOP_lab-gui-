#include "interaction_command.h"


Main_implementation::Main_implementation(My_scene *_scene, My_view *_view, My_tree *_tree)
{
    this->scene = _scene;
    this->view = _view;
    this->tree = _tree;
}

bool Main_implementation::apply_ellipse()
{
    scene->set_creator(new Ellipse_creator);
}

bool Main_implementation::apply_triangle()
{

    scene->set_creator(new Triangle_creator);
}

bool Main_implementation::apply_rectangle()
{
    scene->set_creator(new Rectangle_creator);

}

bool Main_implementation::apply_move(qreal _x, qreal _y)
{
    scene->move_selected(_x,_y);
}

bool Main_implementation::apply_color(qreal _r, qreal _g, qreal _b)
{
    scene->set_color_selected(_r,_g,_b);
}

bool Main_implementation::apply_mouse_press_event(QMouseEvent *event)
{
    view->mouse_press(event);
}

bool Main_implementation::apply_key_press_event(QKeyEvent *event)
{
    qDebug() << "move";


    switch(event->key())
       {
           case Qt::Key_8:
           {
              scene->move_selected(0,-10);
              break;
           }

           case Qt::Key_2:
           {
               scene->move_selected(0,10);
               break;
           }

           case Qt::Key_4:
           {
               scene->move_selected(-10,0);
               break;
           }

           case Qt::Key_6:
           {
               scene->move_selected(10,0);
               break;
           }

       }

}

bool Main_implementation::apply_delete()
{
    scene->delete_selected();
}

bool Main_implementation::apply_scale(qreal _x_fac, qreal _y_fac)
{
    scene->scale_selected(_x_fac, _y_fac);
}

bool Main_implementation::apply_group()
{
    scene->group_selected();
}

bool Main_implementation::apply_degroup()
{
    scene->degroup();
}

bool Main_implementation::apply_save()
{
    scene->save("unnamed1.txt");
}

bool Main_implementation::apply_load()
{
    scene->load("unnamed1.txt");
}







