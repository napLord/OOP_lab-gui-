#include "my_scene.h"

#include <QtCore>
#include <QApplication>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>


void My_scene::move_selected(qreal x, qreal y)
{
    for(int i =0; i<storage.selected_items.Get_count(); ++i)
    {
        qreal sl = this->sceneRect().left();
        qreal sr = this->sceneRect().right();
        qreal st = this->sceneRect().top();
        qreal sb = this->sceneRect().bottom();


        if ((xmin + x) < sl)    x = sl - xmin;
        if ((xmax + x) > sr)    x = sr - xmax;
        if ((ymin + y) < st)    y = st - ymin;
        if ((ymax + y) > sb)    y = sb - ymax;

        storage.selected_items[i]->moveBy(x,y);
    }

    xmin = xmin + x;
    xmax = xmax + x;
    ymin = ymin + y;
    ymax = ymax + y;
}

void My_scene::unselect_selected()
{
    for (int i = 0; i<storage.selected_items.Get_count(); ++i)
        storage.selected_items[i]->Select_toggle();
}

My_scene::My_scene(QObject *parent): QGraphicsScene(parent)
{
    creator = new Rectangle_creator;
    xmin = 0, xmax = 0, ymin = 0; ymax = 0;
}

void My_scene::make_obj(QPointF point)
{

    Drawable_item *ptr = creator->create(point, 40,40);
    this->addItem(ptr);
    storage.Add(ptr);
}

void My_scene::pars_stroke(QString name, int &stroke, Container_item *container)
{
    QFile file(name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text) == 0)
        return;

    QTextStream stream(&file);
    QString type;
    int is_selected = 0;
    qreal x, y, w, h;

    for(int i = 0; i < stroke; ++i)
        stream.readLine();

    stream >>type >> x >> y >> w >> h >> is_selected;

    if( type == "My_ellipse")
    {
        this->set_creator(new Ellipse_creator);
        Drawable_item *current = creator->create(QPoint(x+w/2,y+h/2), w, h);
        if(is_selected)
            this->add_to_selected(current);
        this->addItem(current);

        if(container == 0)
            this->storage.Add(current);
        else
            container->add_item(current);
        return;

    }

    if( type == "My_triangle")
    {
        this->set_creator(new Triangle_creator);
        Drawable_item *current = creator->create(QPoint(x+w/2,y+h/2),  w, h);
        if(is_selected)
            this->add_to_selected(current);
        this->addItem(current);

        if(container == 0)
            this->storage.Add(current);
        else
            container->add_item(current);
        return;

    }

    if( type == "My_rectangle")
    {
        this->set_creator(new Rectangle_creator);
        Drawable_item *current = creator->create(QPoint(x+w/2,y+h/2),  w, h);
        if(is_selected)
            this->add_to_selected(current);
        this->addItem(current);

        if(container == 0)
            this->storage.Add(current);
        else
            container->add_item(current);

        return;
    }

    if( type == "Container_item")
    {
        int count;
        stream >> count;

        Container_item *attached_container = new Container_item(x,y,w,h);

        for(int i = 0; i < count; ++i)
        {
            this->pars_stroke(name, ++stroke, attached_container);
        }

        if(container == 0)
            this->storage.Add(attached_container);
        else
            container->add_item(attached_container);
        this->addItem(attached_container);
        return;
    }




}






void My_scene::set_color_selected(qreal _r, qreal _g, qreal _b)
{
    for (int i = 0; i<storage.selected_items.Get_count(); ++i)
        storage.selected_items[i]->set_color(_r,_g,_b);

}

void My_scene::set_creator(Item_creator *_creator)
{
    if (creator != nullptr)
        delete creator;
    this->creator = _creator;
}

void My_scene::add_to_selected(Drawable_item *item)
{
    this->storage.selected_items.Add(item);

    if(!item->Is_selected())
        item->Select_toggle();

    if (this->storage.selected_items.Get_count() == 1) // if "item" is only one
    {
        xmax = item->get_x()+item->get_w(); xmin = item->get_x(); ymax = item->get_y()+item->get_h(); ymin = item->get_y();
    }
    else
    {
        if (item->get_x() < xmin)  xmin = item->get_x();
        if ((item->get_x() + item->get_w()) > xmax) xmax = item->get_x() + item->get_w();
        if (item->get_y() < ymin) ymin = item->get_y();
        if ((item->get_y() + item->get_h()) >ymax) ymax = item->get_y() + item->get_h();
    }
}

void My_scene::scale_selected(qreal _x_fac, qreal _y_fac)
{
    int x = storage.selected_items.Get_count();
    for (int i = 0; i < x; ++i)
    {

        storage.selected_items[0]->scale(_x_fac, _y_fac);               //scale 0s item
        this->add_to_selected(storage.selected_items.Delete(0));        //delete it and pushback it at the same time
        move_selected(0,0);
    }                                                                   //now he item  at back and scaled
}

void My_scene::clear_selected()
{
    this->storage.selected_items.clear();
    xmin = 0; ymin = 0; xmax = 0; ymax = 0;
}

void My_scene::group_selected()
{
    int x = storage.selected_items.Get_count();
    if (x == 0)
        return;

    Container_item *container = new Container_item(xmin,ymin,xmax-xmin,ymax-ymin);
    this->addItem(container);
    storage.Add(container);

    for (int i = 0; i < x; ++i)
    {
        Drawable_item * current = this->storage.selected_items[i];
        container->add_item( this->storage.selected_items[i]);
        storage.Delete(current);
    }

    this->unselect_selected();
    this->clear_selected();

    this->add_to_selected(container);
    notify();
}

void My_scene::degroup()
{
    if((storage.selected_items.Get_count() != 1) || !storage.selected_items[0]->can_be_degrouped()  )
        return;
    else
    {
        Container_item  *ptr = dynamic_cast<Container_item*>(storage.selected_items[0]);
        Drawable_item * popped = ptr->pop();
        while(popped!= nullptr)
        {
            popped->Select_toggle();
            this->add_to_selected(popped);
            this->storage.Add(popped);
            popped = ptr->pop();

        }
        this->storage.Delete(ptr);
        this->storage.selected_items.Delete(ptr);
        delete ptr;
    }
    notify();
}

void My_scene::save(QString name)
{
    QFile file(name);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text) == 0)
        return;
    file.resize(0);

    int count = 0;
    for (int i = 0; i < storage.Get_count(); ++i)
    {
        if (storage[i]->getClassName() == "Container_item")
        {
            Container_item* container = dynamic_cast<Container_item*> (storage[i]);
            count += container->get_count();
        }
        count++;
    }
    file.write((QString::number(count)).toLocal8Bit());
    file.write(QString("\n").toLocal8Bit());
    file.close();
    for(int i = 0; i < storage.Get_count(); ++i)
    {
        storage[i]->safe(name);
    }
}

void My_scene::load(QString name)
{
    QFile file(name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text) == 0)
        return;

    int x = this->storage.Get_count();
    for(int i = 0; i < x; ++i)
    {
        delete this->storage.Delete(0);
    }
    this->storage.clear();
    this->storage.selected_items.clear();

    QTextStream stream(&file);
    int n = 0;
    stream >> n;
    file.close();
    for (int i = 1; i <= n; ++i)
    {

        this->pars_stroke(name,i);


//        if( type == "My_ellipse")
//        {
//            delete this->creator;
//            this->creator = new Ellipse_creator;
//            Drawable_item *current =  this->creator->create(QPointF(x+w/2,y+h/2),w,h);
//            if(is_selected)
//            {
//                current->Select_toggle();
//                this->storage.selected_items.Add(current);
//            }
//            this->storage.Add(current);
//            this->addItem(current);

////            qDebug() << x << y << w << h;
//        }

//        if( type == "My_triangle")
//        {
//                delete this->creator;
//                this->creator = new Triangle_creator;
//            Drawable_item *current =  this->creator->create(QPointF(x+w/2,y+h/2),w,h);
//            if(is_selected)
//            {
//                current->Select_toggle();
//                this->storage.selected_items.Add(current);
//            }
//            this->storage.Add(current);
//            this->addItem(current);

//        }

//        if( type == "My_rectangle")
//        {
//                delete this->creator;
//                this->creator = new Rectangle_creator;
//            Drawable_item *current =  this->creator->create(QPointF(x+w/2,y+h/2),w,h);
//            if(is_selected)
//            {
//                current->Select_toggle();
//                this->storage.selected_items.Add(current);
//            }
//            this->storage.Add(current);
//            this->addItem(current);
//        }

//        if( type == "Container_item")
//        {
//            Container_item *container = new Container_item(x,y,w,h);
//            this->addItem(container);
//            storage.Add(container);

//            int count;
//            stream >> count;
//            for (int i = 0; i < count; ++i)
//            {
//                QString type;
//                int is_selected = 0;
//                qreal x, y, w, h;
//                stream >> type >> x >> y >> w >> h >> is_selected;


//                if( type == "My_ellipse")
//                {
//                    delete this->creator;
//                    this->creator = new Ellipse_creator;
//                    Drawable_item *current =  this->creator->create(QPointF(x+w/2,y+h/2),w,h);
//                    if(is_selected)
//                    {
//                        current->Select_toggle();
//                        this->storage.selected_items.Add(current);
//                    }
//                    this->storage.Add(current);
//                    this->addItem(current);

//        //            qDebug() << x << y << w << h;
//                }

//                if( type == "My_triangle")
//                {
//                        delete this->creator;
//                        this->creator = new Triangle_creator;
//                    Drawable_item *current =  this->creator->create(QPointF(x+w/2,y+h/2),w,h);
//                    if(is_selected)
//                    {
//                        current->Select_toggle();
//                        this->storage.selected_items.Add(current);
//                    }
//                    this->storage.Add(current);
//                    this->addItem(current);

//                }

//                if( type == "My_rectangle")
//                {
//                        delete this->creator;
//                        this->creator = new Rectangle_creator;
//                    Drawable_item *current =  this->creator->create(QPointF(x+w/2,y+h/2),w,h);
//                    if(is_selected)
//                    {
//                        current->Select_toggle();
//                        this->storage.selected_items.Add(current);
//                    }
//                    this->storage.Add(current);
//                    this->addItem(current);
//                }





//                Drawable_item * current_attached = this->storage.Delete(this->storage.Get_count()-1);
//                container->add_item(current_attached);
//            }


//            if(is_selected)
//            {
//                container->Select_toggle();
//                this->storage.selected_items.Add(container);
//            }
//        }



    }


notify();

}

void My_scene::set_tree(My_tree *_tree)
{
    tree = _tree;
}

void My_scene::notify()
{
    tree->update(storage);
}

void My_scene::update(QList<QTreeWidgetItem *> &items)
{
    this->unselect_selected();
    this->clear_selected();
    for(int i = 0; i< items.count(); ++i)
    {
        if (items[i]->parent() == 0)
            this->add_to_selected(this->storage[(items[i]->text(0)).toInt()]);
    }
}

Drawable_item *My_scene::get_item(int i)
{
    return this->storage[i];

}






void My_scene::click_handle(QPointF position)
{
    if(!this->sceneRect().contains(position)) //if position isn't in scene
        return;

        Drawable_item *item = dynamic_cast<Drawable_item*>
                       (this->itemAt(position,QTransform()));

        if (item == NULL) // click on scene
        {
            this->unselect_selected();
            this->clear_selected();
            this->make_obj(position);

        }
        else  //click on object
        {

          if(QApplication::keyboardModifiers() & Qt::ControlModifier) // is ctrl pressed? yes = 1
          {
            if (!item->Is_selected())
            {
                item->Select_toggle();
                this->add_to_selected(item);
            }
            else
            {
                item->Select_toggle();
                this->storage.selected_items.Delete(item);
            }
          }
          else  //ctrl isn't pressed
          {
              this->unselect_selected();
              this->clear_selected();
              item->Is_selected() ? : item->Select_toggle();
              this->add_to_selected(item);

          }
        }
        notify();
}

void My_scene::delete_selected()
{
    int x = storage.selected_items.Get_count();

    for (int i = 0 ; i < x; ++i)
    {
        storage.Delete(storage.selected_items[0]);
        delete storage.selected_items.Delete(0);
    }
    notify();
}





//Scene_memento& My_scene::create_memento()
//{
//    Scene_memento* new_mem = new Scene_memento;

//    Storage<Drawable_item*> *current_state  = new Storage<Drawable_item*>;
//    for (int i = 0; i < this->storage.selected_items.Get_count(); ++i)
//        current_state->Add(this->storage.selected_items[i]);
//    new_mem->set_state(*current_state);

//    return *new_mem;
//}

//bool My_scene::event(QEvent *e)
//{
//    //nothing here to recieving  no events by the default way
//}

//void My_scene::set_memento(Scene_memento &_state)
//{
//    this->unselect_selected();
//    this->clear_selected();

//    Storage<Drawable_item*> state_stor =  _state.get_state();
//    for(int i = 0; i <state_stor.Get_count(); ++i)
//    {
//        this->add_to_selected(state_stor[i]);
//        this->storage.Delete(state_stor[i]);
//        this->storage.Add(state_stor[i]);
//    }
//}



//Scene_memento::Scene_memento()
//{
//}

//Storage<Drawable_item *> &Scene_memento::get_state()
//{
//    return (this->state);
//}

//void Scene_memento::set_state(const Storage<Drawable_item *> &_state)
//{
//    this->state = _state;
//}
