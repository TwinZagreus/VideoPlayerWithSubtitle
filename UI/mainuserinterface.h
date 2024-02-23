#ifndef MAINUSERINTERFACE_H
#define MAINUSERINTERFACE_H

#include <QMainWindow>

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

    QDialog * overlayDialog;
protected:
    void showEvent(QShowEvent *event) override ;
    void resizeEvent(QResizeEvent *event) override ;
    void moveEvent(QMoveEvent *event) override ;

};

#endif // MAINUSERINTERFACE_H
