#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QPixmap>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const int UPDATE_NAME_INTERVAL = 100;
    const int UPDATE_BACKBROUND_INTERVAL = 7000;
    const QString LINE_TXT_FILE_NAME = "names.txt";

    setWindowIcon(QIcon(":/image/1.ico"));
    setAutoFillBackground(true);
    initPixmaps();
    updateBackground();

    updateNameTimer=new QTimer();
    updateNameTimer->setInterval(UPDATE_NAME_INTERVAL);
    connect(updateNameTimer,SIGNAL(timeout()),this,SLOT(updateNextName()));


    updateBackbround=new QTimer();
    updateBackbround->setInterval(UPDATE_BACKBROUND_INTERVAL);
    connect(updateBackbround,SIGNAL(timeout()),this,SLOT(updateBackground()));
    updateBackbround->start();

    qsrand(0);
    startTimes=0;

    parseFromLineTXTFile(LINE_TXT_FILE_NAME);
}

MainWindow::~MainWindow()
{
    delete ui;
    while(pixmaps.length()) {
        delete pixmaps.last();
        pixmaps.removeLast();
    }

}
void MainWindow::initPixmaps()  {
    for(int i=1;i<5;++i)
        pixmaps.append(new QPixmap(":/image/"+QString::number(i)+".jpg"));
}

void MainWindow::parseFromLineTXTFile(QString filePath)    {
    QFile f(filePath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  {
        dealNoFile();
        return;
    }
    QTextStream readStream(&f);
    while(!readStream.atEnd())
        names.append(readStream.readLine());
    f.close();
}

void MainWindow::dealNoFile()   {
    ui->startButton->setEnabled(false);
    ui->nameEdit->setText("文件在哪里?");
}
void MainWindow::startUpdate()  {
    updateNameTimer->start();
}
void MainWindow::updateNextName()    {
     if(names.length()<1)   {
         ui->nameEdit->setText("已经没人了");
         return;
     }
     int nextNameIndex=qrand()% names.length();
     ui->nameEdit->setText(names.at(nextNameIndex));
}

void MainWindow::stopUpdate()   {
    updateNameTimer->stop();
    names.removeOne(ui->nameEdit->text());
}

void MainWindow::on_startButton_clicked()
{
    if(ui->startButton->text()=="Start!")   {
        ui->startButton->setText("Stop!");
        ui->label->setText("No."+QString::number(++startTimes));
        startUpdate();
    }
    else {
        ui->startButton->setText("Start!");
        stopUpdate();
    }
}

void MainWindow::updateBackground()  {
    nextPictureIndex=qrand()% pixmaps.length();
    palette.setBrush(QPalette::Background, QBrush(pixmaps[nextPictureIndex]->scaled(size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
}

void MainWindow::resizeEvent(QResizeEvent*) {
    palette.setBrush(QPalette::Background, QBrush(pixmaps[nextPictureIndex]->scaled(size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
}
