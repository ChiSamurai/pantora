#ifndef GRUPPENTYP_H
#define GRUPPENTYP_H

#include <QString>
#include <QIcon>
#include <QColor>

class GruppenTyp
{
public:
    GruppenTyp(QString name);

    void setColor(QColor color) { farbe = color; };
    QColor getColor() { return farbe;};

    void setName(QString n) { name = n; };
    QString getName() { return name; };

private:
    QString name;
    QIcon icon;
    QColor farbe;
};

#endif // GRUPPENTYP_H
