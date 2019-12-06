#include "CommonUtils.h"
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QFontDatabase>

namespace CommonUtils
{
QString CommonUtils::loadFontFamilyFromFiles(const QString &sfontFile)
{
    QString font = "";

    QFile fontFile(sfontFile);
    if(!fontFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Open font file error";
        return font;
    }

    int loadedFontID = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if(!loadedFontFamilies.empty())
    {
        font = loadedFontFamilies.at(0);
    }
    fontFile.close();
    return font;
}
}
