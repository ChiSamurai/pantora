#ifndef EINHAENGEPUNKT_H
#define EINHAENGEPUNKT_H

#include <QPoint>
#include <QVector3D>

class Einhaengepunkt : public QVector3D
{
public:
    Einhaengepunkt();
    QPoint koords_pixel;
//    QVector3D koords_global;
};

#endif // EINHAENGEPUNKT_H
