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

#include "windows_api.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint); //去掉标题栏的显示
    //this->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint);//去掉任务栏和标题栏的显示
    this->showMaximized();

    //调用样式表修改背景函数（废弃，改用重写paintEvent()事件绘制背景）
    //this->setStyleSheet("background-image:url("+paths+");");
}

MainWindow::~MainWindow()
{
    delete ui;
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
    connect(pExit,SIGNAL(triggered()),this,SLOT(close()));

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
