#ifndef MY_ITEM_H
#define MY_ITEM_H

#include <QtGui>
#include <QGraphicsItem>
#include <storage.h>

enum  Select_state {UNSELECTED, SELECTED};


//---------------------VIRTUAL CLASS - INTERFACE ---------------------

class Drawable_item : public QGraphicsItem          //interface for ur own items
{
protected:
        Select_state state ;
        QColor color;
        qreal x,y,h,w;

public:
        virtual void moveBy(qreal _x, qreal _y);
        virtual void setPos(qreal _x, qreal _y);
        virtual void set_color(int _r, int _g, int _b);
        virtual void scale(qreal _x_fac, qreal _y_fac);
        virtual bool Select_toggle() ;
        virtual bool can_be_degrouped();
        virtual Select_state Is_selected() ;
        virtual ~Drawable_item();
        virtual bool safe(QString &name);
        virtual QString getClassName() = 0;

        qreal get_x();
        qreal get_y();
        qreal get_h();
        qreal get_w();
};


//----------------------ITEMS-------------------------------

//------------CONTAINER--------------------



class Container_item : public Drawable_item
{
protected:
    Storage<Drawable_item*>  containing_items;
    qreal thickness;

public:
    Container_item(qreal _x ,qreal _y ,qreal _w,qreal _h, QGraphicsItem *parent = NULL);
    virtual void add_item(Drawable_item *_item);
    Drawable_item* get_item(int i);

    int get_count();

    virtual void moveBy(qreal _x, qreal _y);
    virtual void set_color(int _r, int _g, int _b);
    virtual void scale(qreal _x_fac, qreal _y_fac);
    virtual bool Select_toggle() ;
    virtual ~Container_item();
    Drawable_item* pop();    //pop out last element
    virtual bool safe(QString &name);

    virtual QString getClassName();


    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
};



class My_ellipse : public Drawable_item
{
public:
     My_ellipse(qreal _x ,qreal _y ,qreal _w,qreal _h, QGraphicsItem *parent = NULL);

protected:
     virtual QString getClassName();
     void paint(QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);
     QRectF boundingRect() const;
     QPainterPath shape() const;
};



class My_triangle : public Drawable_item
{
public:
    My_triangle(qreal _x ,qreal _y ,qreal _w,qreal _h, QGraphicsItem *parent = NULL);
protected:
    virtual QString getClassName();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
};



class My_rectangle : public Drawable_item
{
public:
    My_rectangle(qreal _x ,qreal _y ,qreal _w,qreal _h, QGraphicsItem *parent = NULL);
protected:
    virtual QString getClassName();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
};


//----------------------ITEM CREATORS-------------------------


class Item_creator   //virtual class-interface
{

public:
    virtual Drawable_item* create(QPointF position, qreal _w, qreal _h) = 0;
};

//real creators

class Ellipse_creator : public Item_creator
{
public:
    Ellipse_creator(){}
    virtual Drawable_item* create(QPointF position, qreal _w, qreal _h)
    {
        _w=40, _h = 40;
        return new My_ellipse(position.rx()-_w/2,position.ry()-_h/2, _w, _h);
    }

};



class Triangle_creator : public Item_creator
{
public:
    Triangle_creator(){}
    virtual Drawable_item* create(QPointF position, qreal _w, qreal _h)
    {
        _w=40, _h = 40;
        return new My_triangle(position.rx()-_w/2,position.ry()-_h/2, _w, _h);
    }

};


class Rectangle_creator : public Item_creator
{
public:
    Rectangle_creator(){}
    virtual Drawable_item* create(QPointF position, qreal _w, qreal _h)
    {
        _w=40, _h = 40;
        return new My_rectangle(position.rx()-_w/2,position.ry()-_h/2, _w, _h);
    }

};



#endif // MY_ITEM_H
