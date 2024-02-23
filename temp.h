#ifndef TEMP_H
#define TEMP_H

#include <QWidget>

namespace Ui {
class Temp;
}

class Temp : public QWidget
{
    Q_OBJECT

public:
    explicit Temp(QWidget *parent = nullptr);
    ~Temp();

private:
    Ui::Temp *ui;
};

#endif // TEMP_H
