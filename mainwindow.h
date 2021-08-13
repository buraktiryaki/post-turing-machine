#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>


#include "interpreter.h"
#include "memory.h"
#include "codeeditor.h"

#include <QDebug>

#define WIDH 800
#define HEIGHT 600

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void printHaltState(int s);
    void changeLine();
    ~MainWindow();

    int a;

private:
    Ui::MainWindow *ui;
    Memory *mem;
    CodeEditor *editor;
    Interpreter *ip;
    QTimer *timer;


protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_zero_clicked();
    void on_pushButton_one_clicked();
    void on_startButton_4_clicked();
    void on_stepButton_5_clicked();
    void on_otoButton_3_clicked();
    void step();
    void on_animSpeed_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
