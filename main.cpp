#include <QCoreApplication>
#include <QIODevice>
#include <QTextStream>
#include <QProcess>

#include "preapptasks.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("PersistenConfigIniApplication");
    QCoreApplication::setOrganizationName("JHilk");

    PreAppTasks::copyIniToDestDir();

    QString pathToPersitentIni = PreAppTasks::pathToInitFile();
    qDebug() << pathToPersitentIni;

    //Write Simple sentence to Local iniFile
    QFile writeAbleIniFile(pathToPersitentIni);
    if(!writeAbleIniFile.open(QIODevice::ReadWrite |QIODevice::Append)){
        qDebug() << "Could not open local ini file" << writeAbleIniFile.errorString() << writeAbleIniFile.error();
        return -1;
    }

    //Write something to the ini file
    QTextStream inout(&writeAbleIniFile);
    inout << "Simple text: Hello World";
    inout.flush();

    //Read Everything back:
    writeAbleIniFile.seek(0);
    QString textInfile;
    inout >> textInfile;
    writeAbleIniFile.close();

    qDebug() << "Text in file" << textInfile;

    //Open local file explorer in folder containing the ini file
#ifdef Q_OS_MACOS
    QStringList args;
    args << "-e";
    args << "tell application \"Finder\"";
    args << "-e";
    args << "activate";
    args << "-e";
    args << "select POSIX file \""+pathToPersitentIni+"\"";
    args << "-e";
    args << "end tell";
    QProcess::startDetached("osascript", args);
#endif

#ifdef Q_OS_WIN

    QStringList args;
    args << "/select," << QDir::toNativeSeparators(pathToPersitentIni);

    QProcess::startDetached("explorer", args);

#endif


    return 0; //a.exec();
}
