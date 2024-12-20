#include "FaceDetection.h"
#include <stdexcept>
#include <iostream>

FaceDetection::FaceDetection(const std::string& cascadePath) {
    faceCascade = new cv::CascadeClassifier();
    // Haar Cascade 초기화
    if (!faceCascade->load(cascadePath)) {
        throw std::runtime_error("Error: Unable to load Haar Cascade file from " + cascadePath);
    }//예외처리: Haar Cascade 로드 실패 처리
}

std::vector<cv::Rect> FaceDetection::detectFaces(const cv::Mat& image) {
    if (image.empty()) {
        throw std::invalid_argument("Error: Input image is empty.");
    }//예외처리: 입력 이미지가 비어 있을 경우

    std::vector<cv::Rect> faces;
    cv::Mat grayImage;

    // 이미지를 그레이스케일로 변환
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // 히스토그램 평활화: 얼굴 감지 성능 향상
    cv::equalizeHist(grayImage, grayImage);

    // 얼굴 감지
    faceCascade->detectMultiScale(
        grayImage,           // 입력 이미지
        faces,               // 감지된 얼굴 영역 저장 벡터
        1.1,                 // 스케일 팩터
        3,                   // 최소 이웃 수
        0,                   // 플래그
        cv::Size(30, 30)     // 최소 크기
    );

    return faces;
}

bool FaceDetection::isInitialized() const {
    return !faceCascade->empty();
}

FaceDetection::~FaceDetection() {
    delete faceCascade;
}
