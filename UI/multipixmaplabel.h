#ifndef MULTIPIXMAPLABEL_H
#define MULTIPIXMAPLABEL_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <vector>

extern "C" {
#include "libass/ass.h"
//#include "libass/ass_types.h"
}

#include "AssRender/assrender.h"

class MultiPixmapLabel: public QLabel
{
    Q_OBJECT
public:
    explicit MultiPixmapLabel(QWidget *parent = nullptr);

    void addPixmap(AssRenderLabel arl);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    std::vector<AssRenderLabel> _arls;

//    QImage assImageToQImage(const ASS_Image *image);

};

#endif // MULTIPIXMAPLABEL_H
