#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtGui>
#include <QTreeWidget>

#include <my_view.h>
#include <my_tree.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    view = new My_view(this);
    scene = new My_scene();
    My_tree *tree = new My_tree(scene);
    scene->set_tree(tree);
    this->implementation = new Main_implementation(scene, view, tree);
    scene->setSceneRect(-400,-225,800,450);

    ui->setupUi(this);

    view->setScene(scene);
    view->fitInView(scene->sceneRect());
    ui->gridLayout->addWidget(view,0,0);

    ui->Tree_v_layout->insertWidget(0,tree);

    ui->but_ell->setIcon(QIcon("ell.png"));
    ui->but_triangle->setIcon(QIcon("triangle.png"));
    ui->but_rectangle->setIcon(QIcon("rectangle.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::showEvent(QShowEvent *event)    //fitting scene in view
{
    view->fitInView(scene->sceneRect());
    QWidget::showEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    view->fitInView(scene->sceneRect());
    QWidget::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->implementation->apply_mouse_press_event(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    this->implementation->apply_key_press_event(event);
}

void MainWindow::on_but_ell_clicked()
{
    this->implementation->apply_ellipse();
}

void MainWindow::on_but_triangle_clicked()
{
    this->implementation->apply_triangle();
}

void MainWindow::on_but_rectangle_clicked()
{
    this->implementation->apply_rectangle();
}

void MainWindow::on_apply_coords_clicked()
{
    this->implementation->apply_move(ui->line_x->text().toDouble(),
                                     ui->line_y->text().toDouble());
}

void MainWindow::on_apply_color_clicked()
{
    this->implementation->apply_color(ui->line_r->text().toDouble(),
                                      ui->line_g->text().toDouble(),
                                      ui->line_b->text().toDouble());
}

void MainWindow::on_apply_delete_clicked()
{
    this->implementation->apply_delete();
}

void MainWindow::on_apply_scale_clicked()
{
    this->implementation->apply_scale(ui->line_x_fac->text().toDouble(),
                                      ui->line_y_fac->text().toDouble());
}

void MainWindow::on_apply_group_clicked()
{
    this->implementation->apply_group();
}

void MainWindow::on_apply_degroup_clicked()
{
    this->implementation->apply_degroup();
}

void MainWindow::on_apply_save_clicked()
{
  this->implementation->apply_save();
}

void MainWindow::on_apply_load_clicked()
{
    this->implementation->apply_load();
}


