#include "my_item.h"


void Drawable_item::moveBy(qreal _x, qreal _y)
{
    x += _x; y +=_y;
    QGraphicsItem::moveBy(_x,_y);
}

void Drawable_item::setPos(qreal _x, qreal _y)
{
    x=_x; y = _y;
    QGraphicsItem::setPos(_x,_y);
}

void Drawable_item::set_color(int _r, int _g, int _b)
{
    this->color = QColor(_r,_g,_b);
    this->update(this->boundingRect());
}

void Drawable_item::scale(qreal _x_fac, qreal _y_fac)
{
    w *= _x_fac; h *= _y_fac;
    update(this->boundingRect());
}

bool Drawable_item::Select_toggle()
{
    if (state==SELECTED)
    {
        state = UNSELECTED;
        this->update(this->boundingRect());    //need to request redrawing
        return 0;
    }
    else
    {
        state = SELECTED;
        this->update(this->boundingRect());
        return 1;
    }
}

Select_state Drawable_item::Is_selected()
{
    return state;
}

bool Drawable_item::can_be_degrouped()
{
    return (dynamic_cast<Container_item*>(this) == 0)? 0 : 1;
}

Drawable_item::~Drawable_item()
{
    //nothing here, but maybe should be something
}

bool Drawable_item::safe(QString &name)
{
    QFile file;
    file.setFileName(name);
    if (file.open(QIODevice::Append  | QIODevice::Text) == 0)
            throw;
    QTextStream stream(&file);
    stream << getClassName()<< " " << get_x()<< " " << get_y()<< " " << get_w()
           << " " << get_h() << " " << Is_selected() <<"\n";
    file.close();
//    if(!file.exists())
//    {
//        file.open(QIODevice::ReadWrite) ;
//        QTextStream stream(&file);
//        stream<<"ok\n";
//    }
//    else
//    {
//        QFile file(name)

//    }


//    if(file.open(QIODevice::ReadWrite) == 0)

//    {
//        qDebug() << "can't open to safe " << name <<"\n";
//        return 0;
//    }
//    QTextStream stream(&file);
//    stream<<"ok\n";



}



qreal Drawable_item::get_x()
{
    return x;
}
qreal Drawable_item::get_y()
{
    return y;
}
qreal Drawable_item::get_h()
{
    return h;
}
qreal Drawable_item::get_w()
{
    return w;
}


//----------ELLIPSE

void My_ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if (state==UNSELECTED)
    {
        painter->setBrush(color);
        painter->setPen(QPen(QBrush(Qt::black), 3));
    }
    else
    {
        painter->setBrush(color);
        painter->setPen(QPen(QBrush(Qt::red), 3));
    }

    painter->drawEllipse(QRect(0,0,w,h));   //changed
}

QRectF My_ellipse::boundingRect() const
{
    return QRectF(0,0,w,h);
}

QPainterPath My_ellipse::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

My_ellipse::My_ellipse(qreal _x, qreal _y, qreal _w, qreal _h, QGraphicsItem *parent)
{
    x=_x; y=_y; h=_h; w=_w;
    state = UNSELECTED;
    color = QColor(255,255,255);
    this->setPos(_x,_y);

}

QString My_ellipse::getClassName()
{
    return QString("My_ellipse");
}


//--------TRIANGLE


My_triangle::My_triangle(qreal _x, qreal _y, qreal _w, qreal _h, QGraphicsItem *parent)
{
    x=_x; y=_y; h=_h; w=_w;
    state = UNSELECTED;
    color = QColor(255,255,255);

    this->setPos(_x,_y);
}

QString My_triangle::getClassName()
{
    return QString("My_triangle");
}

void My_triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (state==UNSELECTED)
    {
        painter->setBrush(color);
        painter->setPen(QPen(QBrush(Qt::black), 3));
    }
    else
    {
        painter->setBrush(color);
        painter->setPen(QPen(QBrush(Qt::red), 3));
    }

    QPainterPath path;

    path.moveTo(0,h);      //creating a triangle
    path.lineTo(w,h);
    path.lineTo(w/2,0);
    path.lineTo(0,h);

    painter->drawPath(path);
}

QRectF My_triangle::boundingRect() const
{
    return QRectF(0,0,w,h);
}

QPainterPath My_triangle::shape() const
{
    QPainterPath path;
    path.moveTo(0,h);
    path.lineTo(w,h);
    path.lineTo(w/2,0);
    path.lineTo(0,h);
    return path;
}

//--------RECTANGLE

My_rectangle::My_rectangle(qreal _x, qreal _y, qreal _w, qreal _h, QGraphicsItem *parent)
{
    x=_x; y=_y; h=_h; w=_w;
    state = UNSELECTED;
    color = QColor(255,255,255);

    this->setPos(_x,_y); //changed
}

QString My_rectangle::getClassName()
{
    return QString("My_rectangle");
}

void My_rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (state==UNSELECTED)
    {
        painter->setBrush(color);
        painter->setPen(QPen(QBrush(QColor(0,0,0)), 3));
    }
    else
    {
        painter->setBrush(color);
        painter->setPen(QPen(QBrush(Qt::red), 3));
    }

    painter->drawRect(this->boundingRect());
}

QRectF My_rectangle::boundingRect() const
{
    return QRectF(0,0,w,h);
}

QPainterPath My_rectangle::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

//----------------------Container

Container_item::Container_item(qreal _x, qreal _y, qreal _w, qreal _h, QGraphicsItem *parent ) /*:QGraphicsItem(parent)*/
{
    thickness = 3;
    x = _x; y = _y; w = _w; h = _h;
    state = UNSELECTED;
    this->setPos(_x,_y);
}

void Container_item::add_item(Drawable_item *_item)
{
    this->containing_items.Add(_item);
}

Drawable_item *Container_item::get_item(int i)
{
    return this->containing_items[i];

}

//Drawable_item *Container_item::operator[](int i)
//{
//    return this->containing_items[i];
//}

int Container_item::get_count()
{
    return this->containing_items.Get_count();
}

void Container_item::moveBy(qreal _x, qreal _y)
{
    Drawable_item::moveBy(_x,_y);
    for (int i = 0; i < containing_items.Get_count(); ++i)
    {
        containing_items[i]->moveBy(_x,_y);
    }
}

void Container_item::set_color(int _r, int _g, int _b)
{
    for (int i = 0; i < containing_items.Get_count(); ++i)
    {
        Drawable_item* current = containing_items[i];
        current->set_color(_r,_g,_b);
    }
}

void Container_item::scale(qreal _x_fac, qreal _y_fac)
{
    Drawable_item::scale(_x_fac,_y_fac);
    for (int i = 0; i < containing_items.Get_count(); ++i)
    {
        Drawable_item* current = containing_items[i];
        current->setPos((current->get_x()-(this->x))*_x_fac + this->get_x(),
                        (current->get_y()-(this->y))*_y_fac + this->get_y());
        current->scale(_x_fac,_y_fac);
    }
}

bool Container_item::Select_toggle()
{
    if(state == SELECTED)
    {
        state = UNSELECTED;
        this->update(this->boundingRect());
        return 0;
    }
    else
    {
        state = SELECTED;
        this->update(this->boundingRect());
        return 1;
    }
}

Container_item::~Container_item()
{
    int x = this->containing_items.Get_count();

    for(int i = 0 ; i < x; ++i)
    {
        delete this->containing_items.Delete(0);
    }
}

Drawable_item *Container_item::pop()
{
    if(this->containing_items.Get_count() == 0)
        return nullptr;
    else
    {

        return this->containing_items.Delete(0);
    }
}

bool Container_item::safe(QString &name)
{
    QFile file;
    file.setFileName(name);
    if (file.open(QIODevice::Append  | QIODevice::Text) == 0)
            throw;
    QTextStream stream(&file);
    stream << getClassName()<< " " << get_x()<< " " << get_y()<< " " << get_w()
           << " " << get_h() << " " << Is_selected()
           << " " << this->containing_items.Get_count() << "\n";
    file.close();
    int x = this->containing_items.Get_count();
    for(int i = 0; i < x; ++i)
    {
        this->containing_items[i]->safe(name);
    }
}

QString Container_item::getClassName()
{
    return QString("Container_item");
}

void Container_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (state==UNSELECTED)
    {
        painter->setBrush(QColor(0,0,0,0)); //transparent
        painter->setPen(QPen(QBrush(QColor(34,153,153)), thickness));
    }
    else
    {
        painter->setBrush(QColor(0,0,0,0));
        painter->setPen(QPen(QBrush(Qt::red), thickness));
    }

    painter->drawRect(this->boundingRect());
}

QRectF Container_item::boundingRect() const
{
    return QRectF(0-thickness,0-thickness,w+thickness*2,h+thickness*2);
}

QPainterPath Container_item::shape() const
{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}
