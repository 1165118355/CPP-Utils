#ifndef UTILSQT_H
#define UTILSQT_H

#include <vector>
#include <string>
#include <QString>
#include <QWidget>

namespace UtilsQt
{
    /// \brief  调用qt文件对话框来获取文件的路径（他是基于Space的DataPath的相对路径）
    QString getFileDialog(QWidget *parent, QString title, QString filter="(all file (*.*))", int mode=1, QString dir="./");
	QString getDirDialog(QWidget *parent, QString title, int mode=1);

    /// \brief
    void removeLayoutContent(QLayout *layout);
	
    /// \brief  喵
	QString canonicalPath(QString path);
	QString savePath(QString name);

    /// \brief  汪
	int isAbsolute(QString name);
	int isAlpha(int code);
};

#endif // UTILSQT_H
