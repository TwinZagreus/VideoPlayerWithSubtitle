#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

extern "C" {
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
}

extern "C" {
#include "libass/ass.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"Hello FFMPEG,version is "+ QString::fromUtf8(av_version_info());

    qDebug()<<"Hello ass,version:"+QString::number(ass_library_version());

}

MainWindow::~MainWindow()
{
    delete ui;
}

