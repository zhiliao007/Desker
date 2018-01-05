/*
******************************************************************************
* Copyright (c) 2017,学生开放实验室
* All rights reserved.
******************************************************************************
* 文件名称： mianwindow.cpp
* 文件标识： mainwindow
* 摘    要: 主窗口
******************************************************************************
* 当前版本： 1.0
* 作者    : zhiliao007
* 创建日期： 2018-01-01T15:13:15
******************************************************************************
*/
#include <QString>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QPainter>
#include <QDebug>
#include <QtWin>

#include "windows_api.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint);//去掉任务栏和标题栏的显示
    this->showMaximized();

    ui->label->setPixmap(getIcon("D:\\Program Files (x86)\\Arduino\\arduino.exe",true));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::getIcon(const QString sourceFile, bool sizeFlag)
{
    // ExtractIconEx 从限定的可执行文件、动态链接库（DLL）、或者图标文件中生成图标句柄数组
    const UINT iconCount = ExtractIconEx((wchar_t *)sourceFile.utf16(), -1, 0, 0, 0);
    if (!iconCount) {
        qDebug() << QString("%1 does not appear to contain icons.").arg(sourceFile);
    }

    QScopedArrayPointer<HICON> icons(new HICON[iconCount]);

    if(sizeFlag){
        if(!ExtractIconEx((wchar_t *)sourceFile.utf16(), 0, icons.data(), 0, iconCount))
            ExtractIconEx((wchar_t *)sourceFile.utf16(), 0, 0, icons.data(), iconCount);
    }
    else
        ExtractIconEx((wchar_t *)sourceFile.utf16(), 0, 0, icons.data(), iconCount);

    return QtWin::fromHICON(icons[0]);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);

    QAction *pNew = new QAction("新建格子",this);
    //QIcon icoNew(":/images/images/new.png");
    //pNew->setIcon(icoNew);
    menu->addAction(pNew);
    //connect(pNew,SIGNAL(triggered()),this,SLOT(close()));

    QAction *pExit = new QAction("退出整理",this);
    QIcon icoExit(":/images/images/exit.png");
    pExit->setIcon(icoExit);
    menu->addAction(pExit);
    connect(pExit,SIGNAL(triggered()),qApp, SLOT(quit()));  //直接退出程序

    QAction *pSet = new QAction("设置中心",this);
    //QIcon icoSet(":/images/images/set.png");
    //pSet->setIcon(icoSet);
    menu->addAction(pSet);
    //connect(pSet,SIGNAL(triggered()),this,SLOT(close()));

    QAction *pAbout = new QAction("帮助关于",this);
    QIcon icoAbout(":/images/images/help.png");
    pAbout->setIcon(icoAbout);
    menu->addAction(pAbout);
    //connect(pAbout,SIGNAL(triggered()),this,SLOT(close()));

    menu->move(cursor().pos());
    menu->show();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);

   //调用windows API获取桌面壁纸路径
   TCHAR chPath[MAX_PATH];
   SystemParametersInfo(SPI_GETDESKWALLPAPER,MAX_PATH,chPath,0);
   QString path = TCHARToQString(chPath);
   QString paths = path.replace(QRegExp("\\\\"), "/");
#ifdef QT_NO_DEBUG

#else
    qDebug() << paths;
#endif //QT_NO_DEBUG

   painter.drawPixmap(0,0,width(),height(),QPixmap(paths));
}

/************** (C) COPYRIGHT 2014-2018 学生开放实验室 *****END OF FILE*********/
