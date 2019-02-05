/*
******************************************************************************
* Copyright (c) 2017,学生开放实验室
* All rights reserved.
******************************************************************************
* 文件名称： fileicon.h
* 文件标识： 图标头文件
* 摘    要:  获取系统图标
******************************************************************************
* 当前版本： 1.0
* 作者    : Quard
* 创建日期： 2018-01-02T18:15:30
******************************************************************************
*/
#ifndef FILEICON_H
#define FILEICON_H

#include <QIcon>
#include <QString>

class FileIcon
{
  public:
    FileIcon();
    QIcon fileExtensionIcon(const QString extension) const;
    QString fileExtensionType(const QString &extension) const;
    QPixmap getIcon(QString filename);
    bool pixmapIsOnly48Bit(QPixmap pixmap);
};

#endif // FILEICON_H

/************** (C) COPYRIGHT 2014-2018 学生开放实验室 *****END OF FILE*********/
