#include "ImageManager.h"
#include <stdexcept>

cv::Mat ImageManager::loadImage(const std::string& path) {
    cv::Mat image = cv::imread(path);
    if (image.empty()) {
        throw std::runtime_error("Error: Unable to load image from " + path);
    }
    return image;
} //예외처리: 이미지 로드 실패 처리

//함수중복: 여기서 saveImage 함수는 오버로드를 통해 기본 품질(95)로 저장할 수 있도록 구현되었습니다. saveImage의 두 번째 버전은 품질을 설정할 수 있으며, 첫 번째 함수는 두 번째 함수를 호출하여 기본값을 사용
void ImageManager::saveImage(const cv::Mat& image, const std::string& path) {
    saveImage(image, path, 95); // 기본 품질로 설정
}

void ImageManager::saveImage(const cv::Mat& image, const std::string& path, int quality) {
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(quality);
    cv::imwrite(path, image, compression_params);
}