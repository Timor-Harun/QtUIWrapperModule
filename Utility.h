#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QFileInfo>

namespace TimorHarun {
	namespace Utility {
		static QString getFileNamePrefix(const QString& pyFilePath)
		{
			//�������Ƕ�ȡ�ļ������ƣ��ַ����ָ�
			QFileInfo fileInfo(pyFilePath);
			QString className = fileInfo.fileName();

			//���һ��б�ܵ�λ��
			int backslashIndex = pyFilePath.lastIndexOf('/');
			int potIndex = pyFilePath.lastIndexOf('.');
			return pyFilePath.mid(backslashIndex + 1, potIndex - backslashIndex - 1);
		}

		static std::string stdstr(const QString&str)
		{
			return str.toStdString();
		}

		static const char* cstr(const QString& str)
		{
			return str.toStdString().c_str();
		}
	}
}

#endif

