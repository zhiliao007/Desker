#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <QString>
#include <QDebug>
#include <QAction>
#include <QMenu>

#ifdef UNICODE
#define QStringToTCHAR(x)     (wchar_t*) x.utf16()
#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()
#define TCHARToQString(x)     QString::fromUtf16((ushort*)(x))
#define TCHARToQStringN(x,y)  QString::fromUtf16((ushort*)(x),(y))
#else
#define QStringToTCHAR(x)     x.local8Bit().constData()
#define PQStringToTCHAR(x)    x->local8Bit().constData()
#define TCHARToQString(x)     QString::fromLocal8Bit((x))
#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))
#endif



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::SubWindow|Qt::FramelessWindowHint);//去掉任务栏的显示和标题栏
    this->showMaximized();

    TCHAR chPath[MAX_PATH];
    SystemParametersInfo(SPI_GETDESKWALLPAPER,MAX_PATH,chPath,0);

    QString path = TCHARToQString(chPath);
    QString paths = path.replace(QRegExp("\\\\"), "/");

#ifdef QT_NO_DEBUG

#else
    qDebug() << "background-image:url("+paths+");";
#endif /*QT_NO_DEBUG*/

    this->setStyleSheet("background-image:url("+paths+");");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);

    QAction *pExit = new QAction("退出",this);
    menu->addAction(pExit);
    connect(pExit,SIGNAL(triggered()),this,SLOT(close()));

    menu->move(cursor().pos());
    menu->show();
}
