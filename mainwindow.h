#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <my_scene.h>
#include <storage.h>
#include <interaction_command.h>
#include <my_view.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent * event);
    void resizeEvent(QResizeEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_but_ell_clicked();
    void on_but_triangle_clicked();
    void on_but_rectangle_clicked();
    void on_apply_coords_clicked();
    void on_apply_color_clicked();
    void on_apply_delete_clicked();
    void on_apply_scale_clicked();
    void on_apply_group_clicked();
    void on_apply_degroup_clicked();

    void on_apply_save_clicked();

    void on_apply_load_clicked();



private:
    Ui::MainWindow *ui;
    My_scene *scene;
    My_view *view;
    Interaction_implementation *implementation;   //implement class beahavior
};

#endif // MAINWINDOW_H
