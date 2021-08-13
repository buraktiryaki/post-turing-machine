#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(WIDH,HEIGHT);
    setWindowTitle("Post Makinesi");
    a = 0;

    mem = new Memory(20,20,30,WIDH);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(step()));

    editor = new CodeEditor(ui->groupBox);
    editor->setFixedSize(350,380);
    editor->zoomIn(5);
    editor->move(5,10);
}

void MainWindow::printHaltState(int s)
{
    if(!s)
    {
        ui->outlLabel_2->setText("Halt (Success)");
        on_startButton_4_clicked();
    }
    else if(s == RT_ERR_INFINITELOOP)
    {
        ui->outlLabel_2->setText("Halt (RT_ERR_INFINITELOOP)");
        on_startButton_4_clicked();
    }
    else if(s == RT_ERR_OVERFLOW)
    {
        ui->outlLabel_2->setText("Halt (RT_ERR_OVERFLOW)");
        on_startButton_4_clicked();
    }
    else if(s == RT_ERR_UNKNOW)
    {
        ui->outlLabel_2->setText("Halt (RT_ERR_UNKNOWERR)");
        on_startButton_4_clicked();
    }
    else if(s == RT_ERR_WRITE)
    {
        ui->outlLabel_2->setText("Halt (RT_ERR_WRITEERR)");
        on_startButton_4_clicked();
    }
    else if(s == RT_ERR_INVALIDOPERAND)
    {
        ui->outlLabel_2->setText("Halt (RT_ERR_INVALIDOPERAND)");
        on_startButton_4_clicked();
    }
}

void MainWindow::changeLine()
{
    QTextCursor c = editor->textCursor();
    c.movePosition(QTextCursor::Start);
    c.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,ip->step);
    editor->setTextCursor(c);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    mem->draw(&painter);

}

void MainWindow::on_pushButton_clicked()
{
    if(mem->getHeadPos() > 0)
        mem->headL();
    repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(mem->getHeadPos() < mem->boyut-1)
        mem->headR();
    repaint();
}

void MainWindow::on_pushButton_zero_clicked()
{
    mem->setMem(0);
    repaint();
}

void MainWindow::on_pushButton_one_clicked()
{
    mem->setMem(1);
    repaint();
}

//start - stop button
void MainWindow::on_startButton_4_clicked()
{
    //basla
    if(ui->startButton_4->text() == "Başla")
    {
        ui->outlLabel_2->clear();

        //create interpreter
        ip = new Interpreter(editor->toPlainText(),mem);
        int err = ip->checkError();

        if(err)
        {
            QString str = "Satır: " + QString::number(err) +
                    " - Söz dizimi hatası" ;
            ui->outlLabel_2->setText(str);
            delete ip;
        }
        //check success
        else
        {
            ui->startButton_4->setText("Bitir");
            //enable continue and step button
            ui->stepButton_5->setEnabled(true);
            ui->otoButton_3->setEnabled(true);
            //disable memory button
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_one->setEnabled(false);
            ui->pushButton_zero->setEnabled(false);
            //enable animSpeed
            ui->animSpeed->setEnabled(true);
            //disable code editor
            editor->disable();
        }
    }
    //bitir
    else
    {
        ui->startButton_4->setText("Başla");
        //disable step and continue button
        ui->stepButton_5->setEnabled(false);
        ui->otoButton_3->setEnabled(false);
        ui->otoButton_3->setText("Devam");
        //disable animSpeed
        ui->animSpeed->setEnabled(false);
        ui->animSpeed->setValue(1);
        //enable memory button
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_one->setEnabled(true);
        ui->pushButton_zero->setEnabled(true);
        //enable code editor
        editor->enable();
        //stop time
        timer->stop();
        //destroy interpreter
        delete ip;
    }
}

void MainWindow::on_stepButton_5_clicked()
{
    //run and print
    printHaltState(ip->runOneStep());
    repaint();
    changeLine();
}

void MainWindow::on_otoButton_3_clicked()
{
    //devam
    if(ui->otoButton_3->text() == "Devam")
    {
        ui->otoButton_3->setText("Dur");
        ui->stepButton_5->setEnabled(false);
        timer->start(2000/ui->animSpeed->value());

    }
    //dur
    else
    {
        ui->otoButton_3->setText("Devam");
        ui->stepButton_5->setEnabled(true);
        timer->stop();
    }

}

void MainWindow::step()
{
    //run and print
    printHaltState(ip->runOneStep());
    repaint();
    changeLine();
}

void MainWindow::on_animSpeed_valueChanged(int arg1)
{
    timer->setInterval(2000/arg1);
}


















