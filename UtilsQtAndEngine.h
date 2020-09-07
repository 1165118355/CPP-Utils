#ifndef UTILSQTANDENGINE_H
#define UTILSQTANDENGINE_H

#include <QImage>
#include <SpaceImage.h>

namespace UtilsQtAndEngine {

    /// \brief  将Space的图像转换成Qt的图像
    QImage spaceImageToQImage(Space::ImagePtr uimage);
    Space::ImagePtr compressImageToCommonImage(Space::ImagePtr uimage);

    /// \brief  space的图像格式枚举转换成Qt的图像格式枚举
    QImage::Format spaceImageFormatToQtImageFormat(int spaceImageFormat);
}

#endif // UTILSQTANDENGINE_H
