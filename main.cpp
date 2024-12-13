#include "FaceDetection.h"
#include "ImageProcessor.h"
#include "ImageManager.h"
#include "storage.h"
#include <iostream>
#include <fstream>

using namespace std;

// 이미지 처리 및 얼굴 감지 프로그램
int main() {
    try {
        // Haar Cascade 파일 경로
        string cascadePath = "haarcascade_frontalface_default.xml";
        FaceDetection faceDetector(cascadePath);

        // 이미지 파일 경로 설정
        string inputPath = "test_image.jpg";
        string outputPathBlur = "output_blur.jpg";
        string outputPathMask = "output_mask.jpg";
        string copyPathBlur = "copy_output_blur.jpg"; // 블러 처리된 이미지 복사본 경로
        string copyPathMask = "copy_output_mask.jpg"; // 마스크 처리된 이미지 복사본 경로

        // 이미지 로드 및 얼굴 감지
        cv::Mat image = ImageManager::loadImage(inputPath);
        vector<cv::Rect> faces = faceDetector.detectFaces(image);


        // 이미지 프로세서 객체 배열 생성
        vector<ImageProcessor*> processors;
        processors.push_back(new BlurProcessor(15));
        processors.push_back(new MaskProcessor(cv::Scalar(0, 255, 0)));

        // 프로세서별로 처리 및 저장
        string outputPaths[] = {"output_blur.jpg", "output_mask.jpg"};
        for (size_t i = 0; i < processors.size(); ++i) {
            cv::Mat processedImage = image.clone();  // 각 처리기에 원본 이미지의 복사본을 제공
            processors[i]->process(processedImage, faces);
            ImageManager::saveImage(processedImage, outputPaths[i]);
            cout << "Image saved to: " << outputPaths[i] << endl;
        }

        // 메모리 해제
        for (auto processor : processors) {
            delete processor;
        }




        //바이너리 모드로 파일을 열고 파일의 내용 복사
        // 파일 복사 (블러 처리된 이미지)
        ifstream srcBlur(outputPathBlur, ios::binary);
        ofstream destBlur(copyPathBlur, ios::binary);
        if (!srcBlur || !destBlur) {
            throw runtime_error("File cannot be opened for copying.");
        }
        destBlur << srcBlur.rdbuf();
        cout << "Blurred image copied to: " << copyPathBlur << endl;

        // 파일 복사 (마스크 처리된 이미지)
        ifstream srcMask(outputPathMask, ios::binary);
        ofstream destMask(copyPathMask, ios::binary);
        if (!srcMask || !destMask) {
            throw runtime_error("File cannot be opened for copying.");
        }
        destMask << srcMask.rdbuf();
        cout << "Masked image copied to: " << copyPathMask << endl;
        //예외처리: 파일 복사 실패 처리


        // 제네릭 클래스 사용
        Storage<string> stringStorage;
        stringStorage.add("Test string 1");
        stringStorage.add("Test string 2");
        stringStorage.printAll();

        Storage<double> doubleStorage;
        doubleStorage.add(1.23);
        doubleStorage.add(4.56);
        doubleStorage.printAll();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

//전체 프로그램 예외 처리