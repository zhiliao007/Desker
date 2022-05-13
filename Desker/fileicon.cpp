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
#include <QLibrary>
#include <QMessageBox>
#include "fileicon.h"

#if defined(Q_OS_WIN)
#include <QtWin>
#include "windows_api.h"
#endif

#if defined(Q_OS_LINUX)

#endif

#if defined(Q_OS_WIN)
typedef HICON (*CYCGetIcon)(CONST TCHAR *, CONST INT);
#endif

FileIcon::FileIcon()
{
}

QIcon FileIcon::fileExtensionIcon(const QString extension) const
{
    QFileIconProvider icon_provider;
    QIcon icon;
    QTemporaryFile tmp_file(QDir::tempPath() +
                            QDir::separator() +
                            QCoreApplication::applicationName() +
                            "_XXXXXX" +
                            extension);
    tmp_file.setAutoRemove(false);

    if (tmp_file.open())
    {
        QString file_name = tmp_file.fileName();
        tmp_file.write(QByteArray());
        tmp_file.close();

        icon = icon_provider.icon(QFileInfo(file_name));
        tmp_file.remove();
    }
    else
    {
        qCritical() << QString("failed to write temporary file %1")
                           .arg(tmp_file.fileName());
    }

    return icon;
}

QString FileIcon::fileExtensionType(const QString &extension) const
{
    QFileIconProvider icon_provider;
    QString type;
    QTemporaryFile tmp_file(QDir::tempPath() +
                            QDir::separator() +
                            QCoreApplication::applicationName() +
                            "_XXXXXX" +
                            extension);
    tmp_file.setAutoRemove(false);

    if (tmp_file.open())
    {
        QString file_name = tmp_file.fileName();
        tmp_file.write(QByteArray());
        tmp_file.close();

        type = icon_provider.type(QFileInfo(file_name));

        tmp_file.remove();
    }
    else
    {
        qCritical() << QString("failed to write temporary file %1")
                           .arg(tmp_file.fileName());
    }

    return type;
}

QPixmap FileIcon::getIcon(QString filename)
{
#if defined(Q_OS_WIN)
    QLibrary mylib("getIcon.dll");
    HICON hIcon;
    QPixmap pixmap;
    if (mylib.load())
    {
        CYCGetIcon icon;
        icon = (CYCGetIcon)mylib.resolve("CYCGetIcon");
        if (icon != NULL)
        {
            //#define SHIL_EXTRALARGE     2
            //#define SHIL_JUMBO     4
            hIcon = icon(QStringToTCHAR(filename), 4);
            pixmap = QtWin::fromHICON(hIcon);
            if (!pixmapIsOnly48Bit(pixmap))
                return pixmap;
            else
            {
                //qDebug()<<"48 bits only";
                hIcon = icon(QStringToTCHAR(filename), 2);
                return QtWin::fromHICON(hIcon);
            }
        }
    }
    QMessageBox::information(NULL, "NO", "Cannot load 'getIcon.dll' correctly!");
    return QPixmap(":/pic/chilun.png");
#endif
}

bool FileIcon::pixmapIsOnly48Bit(QPixmap pixmap)
{
    QImage img = pixmap.toImage();
    int row = img.height(), col = img.width();
    for (int i = 49; i < row; ++i)
    {
        for (int j = 49; j < col; ++j)
        {
            if ((img.pixel(i, j) & 0xff000000) != 0)
                return false;
        }
    }
    return true;
}

/************** (C) COPYRIGHT 2014-2018 学生开放实验室 *****END OF FILE*********/
