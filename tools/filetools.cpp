#include "filetools.h"

FileTools::FileTools()
{
}

void FileTools::copyFolder(QString sourceFolder, QString destFolder){
    QDir sourceDir(sourceFolder);
    if(!sourceDir.exists()) return;
    QDir destDir(destFolder);
    if(!destDir.exists()){
        destDir.mkdir(destFolder);
    }
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++){
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        QFile::copy(srcName, destName);
    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++){
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        copyFolder(srcName, destName);
    }
}

bool FileTools::deleteFolder(QString folder){
    bool result = true;
    QDir dir(folder);
    if (dir.exists(folder)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = deleteFolder(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) return result;
        }
        result = dir.rmdir(folder);
    }
    return result;
}

bool FileTools::clearFolder(QString folder){
    bool result = true;
    QDir dir(folder);
    if (dir.exists(folder)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = deleteFolder(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) return result;
        }
    }
    return result;
}

