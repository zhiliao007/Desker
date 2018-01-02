/*
******************************************************************************
* Copyright (c) 2017,学生开放实验室
* All rights reserved.
******************************************************************************
* 文件名称： fileicon.cpp
* 文件标识： 图标头文件
* 摘    要:  获取系统图标
******************************************************************************
* 当前版本： 1.0
* 作者    : Quard
* 创建日期： 2018-01-02T18:15:30
******************************************************************************
*/
#include <QTemporaryFile>
#include <QFileIconProvider>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "fileicon.h"

FileIcon::FileIcon()
{

}

QIcon FileIcon::fileExtensionIcon (const QString extension) const
{
    QFileIconProvider icon_provider;
    QIcon icon;
    QTemporaryFile tmp_file(QDir::tempPath() + QDir::separator() + QCoreApplication::applicationName() + "_XXXXXX" + extension);
    tmp_file.setAutoRemove(false);

    if(tmp_file.open())
    {
        QString file_name = tmp_file.fileName();
        tmp_file.write(QByteArray());
        tmp_file.close();

        icon = icon_provider.icon(QFileInfo(file_name));
        tmp_file.remove();
    }
    else
    {
        qCritical()<<QString("failed to write temporary file %1").arg(tmp_file.fileName());
    }

    return icon;
}

QString FileIcon::fileExtensionType(const QString & extension) const
{
    QFileIconProvider icon_provider;
    QString type;
    QTemporaryFile tmp_file(QDir::tempPath() + QDir::separator() + QCoreApplication::applicationName() + "_XXXXXX" + extension);
    tmp_file.setAutoRemove(false);

    if(tmp_file.open())
    {
        QString file_name = tmp_file.fileName();
        tmp_file.write(QByteArray());
        tmp_file.close();

        type = icon_provider.type(QFileInfo(file_name));

        tmp_file.remove();
    }
    else
    {
        qCritical()<<QString("failed to write temporary file %1") .arg(tmp_file.fileName());
    }

    return type;
}

/************** (C) COPYRIGHT 2014-2018 学生开放实验室 *****END OF FILE*********/
