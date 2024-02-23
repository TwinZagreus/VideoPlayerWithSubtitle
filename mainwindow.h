#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showFrame(AVFrame* frame);

private:
    Ui::MainWindow *ui;
    SwsContext* _swsCtx;
    QLabel * _showLabel;

};
#endif // MAINWINDOW_H
