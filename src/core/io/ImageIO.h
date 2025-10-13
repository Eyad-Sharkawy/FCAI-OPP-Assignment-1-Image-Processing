#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <QString>
#include <QFileInfo>
#include <stdexcept>
#include "../image/Image_Class.h"

class ImageIO {
public:
    static Image loadFromFile(const QString& path)
    {
        if (path.isEmpty()) {
            throw std::invalid_argument("Empty file path");
        }
        QFileInfo fi(path);
        if (!fi.exists() || !fi.isFile()) {
            throw std::invalid_argument("File does not exist");
        }
        Image img;
        img.loadNewImage(path.toStdString());
        return img;
    }

    static void saveToFile(const Image& image, const QString& path)
    {
        if (path.isEmpty()) {
            throw std::invalid_argument("Empty file path");
        }
        Image copy = image; // saveImage is non-const in current API
        copy.saveImage(path.toStdString());
    }
};

#endif // IMAGEIO_H


