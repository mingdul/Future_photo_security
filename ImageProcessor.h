#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>

//가상함수:ImageProcessor 클래스
//process 가상 함수로 선언(= 0). 가상 함수는 ImageProcessor가 추상 클래스가 되도록 만듭니다.
//ImageProcessor는 직접 객체를 생성할 수 없으며, 이를 상속받은 클래스에서 구현.

// 추상 클래스: 이미지 처리 공통 인터페이스
class ImageProcessor {
    
//추상 클래스 ImageProcessor
public:
    virtual void process(cv::Mat& image, const std::vector<cv::Rect>& regions) = 0;
    virtual ~ImageProcessor() {}
};//다형성으로 객체를 삭제할 때 적절한 소멸자가 호출되도록 보장

//BlurProcessor 클래스 (상속 구현)
//BlurProcessor는 ImageProcessor를 상속받아 블러 효과를 구현합니다.
//process 메서드를 override하여 입력 이미지의 지정된 영역을 블러 처리.

class BlurProcessor : public ImageProcessor {
private:
    int blurKernelSize; // 블러 커널 크기

public:
    // 생성자
    explicit BlurProcessor(int kernelSize = 15);

    //process 함수는 가상 함수 재정의로, 블러 처리를 구현 override 키워드는 재정의임을 명시적으로 선언하여 실수를 방지
    void process(cv::Mat& image, const std::vector<cv::Rect>& regions) override {
        for (const auto& region : regions) {
            cv::Mat faceROI = image(region);
            cv::GaussianBlur(faceROI, faceROI, cv::Size(blurKernelSize, blurKernelSize), 0);
        }
    }
};

// MaskProcessor 클래스 (상속 구현)
//MaskProcessor는 ImageProcessor를 상속받아 마스크 효과를 구현
//process 메서드를 재정의(override)하여 지정된 영역에 컬러 마스크를 적용
class MaskProcessor : public ImageProcessor {
private:
    cv::Scalar maskColor; // 마스크 색상

public:
    // 생성자
    explicit MaskProcessor(const cv::Scalar& color = cv::Scalar(0, 0, 255)); // 기본값 빨간색

    //process 함수는 가상 함수 재정의로, 지정된 영역에 컬러 마스크를 적용하는 작업을 구현
    void process(cv::Mat& image, const std::vector<cv::Rect>& regions) override {
        for (const auto& region : regions) {
            cv::rectangle(image, region, maskColor, cv::FILLED);
        }
    }
};

#endif