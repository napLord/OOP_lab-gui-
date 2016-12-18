#include "my_view.h"



void My_view::mouse_press(QMouseEvent *event)
{
    My_scene* scene = dynamic_cast<My_scene*>(this->scene()) ;
    scene->click_handle(mapToScene(QPoint( mapFromParent(event->pos())))); //posin window coordinates -> pos in view coords -> click_handle(scene coords)
}

My_view::My_view(QWidget *parent) : QGraphicsView(parent)
{

}


