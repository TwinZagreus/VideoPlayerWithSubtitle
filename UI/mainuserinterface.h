#ifndef MAINUSERINTERFACE_H
#define MAINUSERINTERFACE_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include "multipixmaplabel.h"
#include "AssRender/assrender.h"

namespace Ui {
class MainUserInterface;
}

class MainUserInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUserInterface(QWidget *parent = nullptr);
    ~MainUserInterface();

private:
    Ui::MainUserInterface *ui;

    void createOverlayDialog();

    QDialog * _overlayDialog = nullptr;
    MultiPixmapLabel * _overlayLabel = nullptr;
    QVBoxLayout * _overlayLayout = nullptr;


    QMediaPlayer * _player = nullptr;
    QVideoWidget * _videoWidget = nullptr;
    QAudioOutput * _audioOutPut=nullptr;
//    AssRender _assRender;
protected:
    void showEvent(QShowEvent *event) override ;
    void resizeEvent(QResizeEvent *event) override ;
    void moveEvent(QMoveEvent *event) override ;

};

#endif // MAINUSERINTERFACE_H
