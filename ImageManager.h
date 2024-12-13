#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <opencv2/opencv.hpp>
#include <string>

class ImageManager {
public:
    static cv::Mat loadImage(const std::string& path);
    static void saveImage(const cv::Mat& image, const std::string& path, int quality);
    static void saveImage(const cv::Mat& image, const std::string& path); // 오버로드 버전
};

#endif