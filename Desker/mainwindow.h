/*
******************************************************************************
* Copyright (c) 2017,学生开放实验室
* All rights reserved.
******************************************************************************
* 文件名称： mianwindow.h
* 文件标识： mainwindow
* 摘    要: 主窗口
******************************************************************************
* 当前版本： 1.0
* 作者    : zhiliao007
* 创建日期： 2018-01-01T15:13:15
******************************************************************************
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap getIcon(const QString sourceFile, bool sizeFlag);
    void contextMenuEvent(QContextMenuEvent *event);
    void paintEvent(QPaintEvent *event);


private:
    Ui::MainWindow *ui;

protected:
    void mouseDoubleClickEvent(QMouseEvent*event);//双击
};

#endif // MAINWINDOW_H

/************** (C) COPYRIGHT 2014-2018 学生开放实验室 *****END OF FILE*********/
