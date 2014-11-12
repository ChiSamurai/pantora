#ifndef FILETOOLS_H
#define FILETOOLS_H

#include <QString>
#include <QFile>
#include <QDir>

class FileTools
{
public:
    FileTools();
    static void copyFolder(QString sourceFolder, QString destFolder);
    static bool deleteFolder(QString folder);
    static bool clearFolder(QString folder);
};

#endif // FILETOOLS_H
