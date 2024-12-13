#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class FaceDetection {
private:
    // 객체포인터 사용
    cv::CascadeClassifier* faceCascade;

public:
    FaceDetection(const std::string& cascadePath); // 생성자 선언
    ~FaceDetection(); // 소멸자 선언

    std::vector<cv::Rect> detectFaces(const cv::Mat& image); // 얼굴 감지 메소드
    bool isInitialized() const; // 초기화 검증 메소드
};

#endif // FACEDETECTION_H
