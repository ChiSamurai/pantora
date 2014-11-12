#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QUuid>
#include <QDebug>

class AbstractElement
{
public:
    enum type{GRUPPE, SCAN, TEXTUR, BEFUNDGRENZE};
    AbstractElement(AbstractElement *parent = 0);
    ~AbstractElement();

    void setName(QString n) { name = n; }
    QString getName() const { return name; }

    QString getDescription() { return description; }
    void setDescription(QString d) { description = d;}

    void setThumbnail(QPixmap p) { thumbnail = p; }
    QPixmap getThumbnail() { return thumbnail; }
    QIcon getThumbnailIcon() const;

    QString getUuid() const { return uuid;}
    void setUuid(QString u) { uuid = u; }

    // *** Item-spezifische Methoden

    AbstractElement *child(int row) const;
    void appendChild(AbstractElement *item);
    int childCount() const;
    int row() const;
    AbstractElement *parent() { return parentItem; }

    bool removeChildren(int position, int count);
//    bool removeColumns(int position, int columns);

    void setParent(AbstractElement* p){ parentItem = p; }

//    bool insertColumns(int position, int columns);

    virtual int columnCount() const = 0;
    virtual QVariant data(int column) const = 0;
    virtual bool setData(int column, const QVariant &value) = 0;
    virtual type getElementType() const = 0;
private:
    AbstractElement *parentItem;
    QList<AbstractElement*> childItems;
    QPixmap thumbnail;
    QString name, description;
    QString uuid;


};

#endif // ABSTRACTELEMENT_H
