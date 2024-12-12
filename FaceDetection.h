#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class FaceDetection {
private:
    cv::CascadeClassifier faceCascade; // 얼굴 감지에 사용할 Haar Cascade Classifier

public:
    // 생성자: Haar Cascade 파일 경로를 받아 초기화
    explicit FaceDetection(const std::string& cascadePath);

    // 얼굴 감지 함수: 이미지에서 얼굴 영역(cv::Rect)을 벡터로 반환
    std::vector<cv::Rect> detectFaces(const cv::Mat& image);

    // 예외처리: Cascade 초기화 실패 확인
    bool isInitialized() const;

    ~FaceDetection(); // 소멸자
};

#endif // FACEDETECTION_H
