#include "UtilsQt.h"
#include "UtilsString.h"
#include "UtilsCommon.h"
#include <QFileDialog>
#include <QString>
#include <QLayout>
#include <SpaceEngine.h>

QString UtilsQt::getDirDialog(QWidget *parent, QString title, int mode)
{
	QString dirName = QFileDialog::getExistingDirectory(parent, title, Space::Engine::get()->getDataPath());
	switch (mode)
	{
	case 1:
		dirName = QString(UtilsString::rejectPath(dirName.toStdString().c_str(), Space::Engine::get()->getDataPath()).c_str());
		break;
	}
	if ((!dirName.isEmpty()) && !(dirName[dirName.size() - 1] == '/' || dirName[dirName.size() - 1] == '\\'))
	{
		dirName += "/";
	}
	return dirName;
}

//  模式1：从data目录开始寻找文件，且返回一个相对Data的路径
//  模式2：可以自行选择从什么路径开始找文件
//  模式3：同模式2，并且返回的路径是绝对路径
QString UtilsQt::getFileDialog(QWidget *parent, QString title, QString filter, int mode, QString dir)
{
    QString fileName;
    QString dataPath;
    if(Space::Engine::isInitialized())
    {
        dataPath = Space::Engine::get()->getDataPath();
    }
    switch(mode)
    {
    case 1:
        fileName = QFileDialog::getOpenFileName(parent, title, dataPath.toStdString().c_str(), filter);
        fileName = QString(UtilsString::rejectPath(fileName.toStdString().c_str(), Space::Engine::get()->getDataPath()).c_str());
        break;
    case 2:
		fileName = QFileDialog::getOpenFileName(parent, title, dir, filter);
		fileName = QString(UtilsString::rejectPath(fileName.toStdString().c_str(), Space::Engine::get()->getDataPath()).c_str());
        break;
    case 3:
        fileName = QFileDialog::getOpenFileName(parent, title, dir, filter);
        fileName = QString(Space::String(fileName.toStdString().c_str()).get());
        break;
    }
    return fileName;
}


QString UtilsQt::canonicalPath(QString path) 
{
	Space::String pathName = Space::String(path.toStdString().c_str());
	return  QString(pathName.pathname().get()) + QString(pathName.basename().get());
}

QString UtilsQt::savePath(QString name)
{
	if (isAbsolute(name)) return name;
	//    int tmp = Engine::get()->getNumDataPaths();
	for (int i = 0; i < Space::Engine::get()->getNumDataPaths(); i++) {
		//        const char* tmpc = Engine::get()->getDataPath(i);
		QString path = canonicalPath(Space::Engine::get()->getDataPath(i) + name);
		if (UtilsCommon::isFile(path.toStdString().c_str())) return path;
	}
	return canonicalPath(Space::Engine::get()->getDataPath() + name);
}

int UtilsQt::isAbsolute(QString name)
{
#ifdef _WIN32
	if (name.length() > 2 && isAlpha(name.toStdString()[0]) && name.toStdString()[1] == ':' && name.toStdString()[2] == '/') return 1;
#else
	if (name.length() > 1 && name.toStdString()[0] == '/') return 1;
#endif

	return 0;
}

int UtilsQt::isAlpha(int code)
{
	return ((code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z'));
}

void UtilsQt::removeLayoutContent(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        delete child;
    }
}
