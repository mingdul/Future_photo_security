#include "ImageProcessor.h"
#include <iostream>

// ================= BlurProcessor ==================

BlurProcessor::BlurProcessor(int kernelSize)
    : blurKernelSize(kernelSize) {
    if (kernelSize <= 0 || kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be a positive odd number.");
    }
}

void BlurProcessor::process(cv::Mat& image, const std::vector<cv::Rect>& regions) {
    for (const auto& region : regions) {
        // 얼굴 영역을 블러 처리
        cv::Mat faceROI = image(region);
        cv::GaussianBlur(faceROI, faceROI, cv::Size(blurKernelSize, blurKernelSize), 0);
    }
}

// ================= MaskProcessor ==================

MaskProcessor::MaskProcessor(const cv::Scalar& color)
    : maskColor(color) {}

void MaskProcessor::process(cv::Mat& image, const std::vector<cv::Rect>& regions) {
    for (const auto& region : regions) {
        // 얼굴 영역에 사각형 마스크 적용
        cv::rectangle(image, region, maskColor, cv::FILLED);
    }
}

