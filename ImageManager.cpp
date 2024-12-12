#include "ImageManager.h"
#include <stdexcept>

cv::Mat ImageManager::loadImage(const std::string& path) {
    cv::Mat image = cv::imread(path);
    if (image.empty()) {
        throw std::runtime_error("Error: Unable to load image from " + path);
    }
    return image;
}

void ImageManager::saveImage(const cv::Mat& image, const std::string& path) {
    if (!cv::imwrite(path, image)) {
        throw std::runtime_error("Error: Unable to save image to " + path);
    }
}