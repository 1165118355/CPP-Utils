#include "UtilsQtAndEngine.h"

namespace UtilsQtAndEngine {

QImage spaceImageToQImage(Space::ImagePtr uimage)
{
    if(!uimage|| !uimage->isLoaded() || uimage->getType() != Space::Image::IMAGE_2D)
    {
        printf("SpaceImage转QtImage失败,uimage是空或者图像未加载\n");
        return QImage();
    }
    int width = uimage->getWidth();
    int height = uimage->getHeight();
    Space::ImagePtr tmpUImage = Space::Image::create(uimage);
    if(tmpUImage->isCompressedFormat())
    {
        tmpUImage->decompress();
        compressImageToCommonImage(tmpUImage);
    }
    QImage qimage(width, height, spaceImageFormatToQtImageFormat(tmpUImage->getFormat()));

    for(int i=0; i<width; ++i)
    {
        for(int j=0; j<height; ++j)
        {
            Space::Image::Pixel pixel = tmpUImage->get2D(i, j);
            switch(tmpUImage->getFormat())
            {
            case Space::Image::FORMAT_R8:
                pixel.i.r = pixel.i.r;
                pixel.i.a = 255;
                break;
            case Space::Image::FORMAT_R16:
                pixel.i.r = pixel.i.r / 65536.0 * 255.0;
                pixel.i.a = 255;
                break;
            case Space::Image::FORMAT_RG16:
                pixel.i.r = pixel.i.r / 65536.0 * 255;
                pixel.i.g = pixel.i.g / 65536.0 * 255;
                pixel.i.a = 255;
                break;
            case Space::Image::FORMAT_RGB16:
                pixel.i.r = pixel.i.r / 65536.0 * 255;
                pixel.i.g = pixel.i.g / 65536.0 * 255;
                pixel.i.b = pixel.i.b / 65536.0 * 255;
                pixel.i.a = 255;
                break;
            case Space::Image::FORMAT_RGBA16:
                pixel.i.r = pixel.i.r / 65536.0 * 255;
                pixel.i.g = pixel.i.g / 65536.0 * 255;
                pixel.i.b = pixel.i.b / 65536.0 * 255;
                pixel.i.a = pixel.i.a / 65536.0 * 255;
                break;
            case Space::Image::FORMAT_R16F:
                break;
            }

            qimage.setPixelColor(i, j, QColor(pixel.i.r, pixel.i.g, pixel.i.b, pixel.i.a));
        }
    }
    return qimage;
}

Space::ImagePtr compressImageToCommonImage(Space::ImagePtr uimage)
{
    switch(uimage->getFormat())
    {
    case Space::Image::FORMAT_ATI1:
        uimage->convertToFormat(Space::Image::FORMAT_R8);
        break;
    case Space::Image::FORMAT_ATI2:
        uimage->convertToFormat(Space::Image::FORMAT_RG8);
        break;
    case Space::Image::FORMAT_DXT1:
    case Space::Image::FORMAT_DXT3:
    case Space::Image::FORMAT_DXT5:
        uimage->convertToFormat(Space::Image::FORMAT_RGBA8);
        break;
    }
    return uimage;
}

QImage::Format spaceImageFormatToQtImageFormat(int spaceImageFormat)
{
    QImage::Format qtImageFormat = QImage::Format_RGBA8888;
    switch(spaceImageFormat)
    {
    case Space::Image::FORMAT_R8:
        qtImageFormat = QImage::Format_RGB888;
        break;
    case Space::Image::FORMAT_RG8:
        qtImageFormat = QImage::Format_RGB888;
        break;
    case Space::Image::FORMAT_RGB8:
        qtImageFormat = QImage::Format_RGB888;
        break;
    case Space::Image::FORMAT_RGBA8:
        qtImageFormat = QImage::Format_RGBA8888;
        break;
    case Space::Image::FORMAT_R16:
        break;
    case Space::Image::FORMAT_RG16:
        break;
    case Space::Image::FORMAT_RGB16:
        break;
    case Space::Image::FORMAT_RGBA16:
        break;
    case Space::Image::FORMAT_R16F:
        break;
    case Space::Image::FORMAT_RG16F:
        break;
    case Space::Image::FORMAT_RGB16F:
        break;
    case Space::Image::FORMAT_RGBA16F:
        break;
    case Space::Image::FORMAT_R32F:
        qtImageFormat = QImage::Format_RGB32;
        break;
    case Space::Image::FORMAT_RG32F:
        qtImageFormat = QImage::Format_RGB32;
        break;
    case Space::Image::FORMAT_RGB32F:
        qtImageFormat = QImage::Format_RGB32;
        break;
    case Space::Image::FORMAT_RGBA32F:
        qtImageFormat = QImage::Format_ARGB32;
        break;
    case Space::Image::FORMAT_RGB565:
        qtImageFormat = QImage::Format_RGB16;
        break;
    case Space::Image::FORMAT_RGBA4:
        qtImageFormat = QImage::Format_ARGB4444_Premultiplied;
        break;
    case Space::Image::FORMAT_RGB5A1:
        qtImageFormat = QImage::Format_RGB555;
        break;
    case Space::Image::FORMAT_RGB10A2:
        qtImageFormat = QImage::Format_A2RGB30_Premultiplied;
        break;
    }
    return qtImageFormat;
}

}
