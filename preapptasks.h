#ifndef PREAPPTASKS_H
#define PREAPPTASKS_H

#include <QDebug>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

class PreAppTasks
{
public:
    PreAppTasks() = default;

    static void copyIniToDestDir()
    {
        QFile destFile(pathToInitFile());
        QFile orgFile(":/Config.ini");

        if(destFile.exists()){
            //Both Files exists: implement your logic, for this case here
            qDebug() << Q_FUNC_INFO << "InifFile exists in target location:" << destFile.fileName();
        } else {
            qDebug() << Q_FUNC_INFO << "InifFile does not exist, copying it from ressource folder to:" << destFile.fileName();
            //DestFile does not exist (propably the first program execution) -> simply copy from install folder
            //But first, create the folder, if it does not exist
            QFileInfo info(destFile.fileName());
            info.setFile(info.absolutePath());
            if(!info.exists()){
                QDir d;
                d.mkpath(info.absoluteFilePath());
            }
            orgFile.copy(destFile.fileName());
            //Since we copy from readonly we have to set writing permission.
            //ITS NOT A BUG ITS A FEATURE....
            destFile.setPermissions(QFile::WriteUser | destFile.permissions());
        }
    }

    static QString pathToInitFile()
    {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QString("/Config.ini");
    }
};

#endif // PREAPPTASKS_H
