#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>

//가상함수:ImageProcessor 클래스
//process는 순수 가상 함수로 선언되었습니다(= 0). 순수 가상 함수는 ImageProcessor가 추상 클래스가 되도록 만듭니다.
//ImageProcessor는 직접 객체를 생성할 수 없으며, 이를 상속받은 클래스에서 반드시 구현해야 합니다.

// 추상 클래스: 이미지 처리 공통 인터페이스
class ImageProcessor {
    
//추상 클래스 ImageProcessor
public:
    virtual void process(cv::Mat& image, const std::vector<cv::Rect>& regions) = 0;
    virtual ~ImageProcessor() {}
};

//BlurProcessor 클래스 (상속 구현)
//BlurProcessor는 ImageProcessor를 상속받아 **특정 처리(블러 효과)**를 구현합니다.
//process 메서드를 재정의(override)하여 입력 이미지의 지정된 영역을 블러 처리합니다.

class BlurProcessor : public ImageProcessor {
private:
    int blurKernelSize; // 블러 커널 크기

public:
    // 생성자
    explicit BlurProcessor(int kernelSize = 15);

    //process 함수는 가상 함수 재정의로, 블러 처리를 구현합니다. override 키워드는 재정의임을 명시적으로 선언하여 실수를 방지합니다(예: 오타로 인한 잘못된 함수 이름).
    void process(cv::Mat& image, const std::vector<cv::Rect>& regions) override {
        for (const auto& region : regions) {
            cv::Mat faceROI = image(region);
            cv::GaussianBlur(faceROI, faceROI, cv::Size(blurKernelSize, blurKernelSize), 0);
        }
    }
};

// MaskProcessor 클래스 (상속 구현)
//MaskProcessor는 ImageProcessor를 상속받아 **특정 처리(마스크 효과)**를 구현합니다.
//process 메서드를 재정의(override)하여 지정된 영역에 컬러 마스크를 적용합니다.
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

#endif // IMAGEPROCESSOR_H


//다형성 지원:
// 기반 클래스 포인터/참조를 통해 파생 클래스의 구현을 호출할 수 있습니다.
// 새로운 ImageProcessor 파생 클래스를 추가하더라도 기존 코드를 수정할 필요가 없습니다.