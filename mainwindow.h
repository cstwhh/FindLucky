#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QResizeEvent>
#include<QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent*);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void updateNextName();
    void updateBackground();
private:
    Ui::MainWindow *ui;
    QVector<QString> names;
    QTimer *updateNameTimer;
    QTimer *updateBackbround;
    int startTimes,nextPictureIndex;
    QPalette palette;
    QVector<QPixmap*> pixmaps;

    void parseFromLineTXTFile(QString filePath);
    void dealNoFile();
    void startUpdate();
    void stopUpdate();
    void initPixmaps();
};

#endif // MAINWINDOW_H
