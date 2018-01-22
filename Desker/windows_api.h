/*
******************************************************************************
* Copyright (c) 2017,学生开放实验室
* All rights reserved.
******************************************************************************
* 文件名称： windows_api.h
* 文件标识： win_api头文件
* 摘    要:
******************************************************************************
* 当前版本： 1.0
* 作者    : Quard
* 创建日期： 2018-01-01T15:13:15
******************************************************************************
*/
#ifndef WINDOWS_API_H
#define WINDOWS_API_H

#include <windows.h>
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
#endif /*UNICODE*/

#endif // WINDOWS_API_H

/************** (C) COPYRIGHT 2014-2018 学生开放实验室 *****END OF FILE*********/
