#include "my_tree.h"
#include "my_scene.h"


My_tree::My_tree(My_scene* _scene,QWidget *parent) : QTreeWidget(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHeaderLabel("Items");
    this->setSelectionMode(QAbstractItemView::MultiSelection);
    scene = _scene;

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(notify()));

}

void My_tree::notify()
{
    QList<QTreeWidgetItem *> items = this->selectedItems();
    scene->update(items);

    QTreeWidgetItemIterator it(this);
       while (*it) {
           if ((*it)->isSelected())
           {
               (*it)->setBackground(0,QBrush(QColor(255,0,0)));
               if ((*it)->parent()!=0)
               {
                   (*it)->setSelected(0);
                   (*it)->setBackground(0,QBrush(QColor(Qt::white)));
               }

           }
           else
               (*it)->setBackground(0,QBrush(QColor(Qt::white)));
           ++it;
       }

}

void My_tree::update(Ex_storage<Drawable_item *> &storage)
{
    this->clear();
    for(int i = 0; i < storage.Get_count(); ++i)
    {
        add_item(storage[i], i);
    }
}


bool My_tree::event(QEvent *e)
{
    if(e->type() == QEvent::KeyPress)
        return 0;
    else
        QTreeWidget::event(e);

}

void My_tree::add_item(Drawable_item* item, int i, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *ptr;
    if(parent == 0)
        ptr = new QTreeWidgetItem(this);
    else
        ptr = new QTreeWidgetItem(parent);


    if(item->getClassName() == "My_ellipse")
    {
        ptr->setText(0, QString().setNum(i));
        ptr->setIcon(0,QIcon("ell.png"));
        if(item->Is_selected())
            ptr->setBackground(0,QBrush(QColor(255,0,0,170)));
        return;

    }

    if(item->getClassName() == "My_triangle")
    {
        ptr->setText(0, QString().setNum(i));
        ptr->setIcon(0,QIcon("triangle.png"));
        if(item->Is_selected())
            ptr->setBackground(0,QBrush(QColor(255,0,0,170)));
        return;

    }

    if(item->getClassName()== "My_rectangle")
    {
        ptr->setText(0, QString().setNum(i));
        ptr->setIcon(0,QIcon("rectangle.png"));
        if(item->Is_selected())
            ptr->setBackground(0,QBrush(QColor(255,0,0,170)));
        return;
    }

    if(item->getClassName() == "Container_item")
    {
        Container_item *container_item = dynamic_cast<Container_item *>(item);

        ptr->setText(0, QString().setNum(i));
        ptr->setIcon(0,QIcon("selection.png"));
        if(item->Is_selected())
            ptr->setBackground(0,QBrush(QColor(255,0,0,170)));

        for(int j = 0; j < container_item->get_count(); ++j)
            add_item(container_item->get_item(j),j,ptr);
        return;

    }




}
