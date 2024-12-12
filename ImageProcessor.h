#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>

// 추상 클래스: 이미지 처리 공통 인터페이스
class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;

    // 순수 가상 함수: 이미지 처리
    virtual void process(cv::Mat& image, const std::vector<cv::Rect>& regions) = 0;
};

// 블러 처리 클래스
class BlurProcessor : public ImageProcessor {
private:
    int blurKernelSize; // 블러 커널 크기

public:
    // 생성자
    explicit BlurProcessor(int kernelSize = 15);

    // 블러 처리 구현
    void process(cv::Mat& image, const std::vector<cv::Rect>& regions) override;
};

// 마스크 처리 클래스
class MaskProcessor : public ImageProcessor {
private:
    cv::Scalar maskColor; // 마스크 색상

public:
    // 생성자
    explicit MaskProcessor(const cv::Scalar& color = cv::Scalar(0, 0, 255)); // 기본값 빨간색

    // 마스크 처리 구현
    void process(cv::Mat& image, const std::vector<cv::Rect>& regions) override;
};

#endif // IMAGEPROCESSOR_H
