#include "FaceDetection.h"
#include "ImageProcessor.h"
#include "ImageManager.h"
#include <iostream>

int main() {
    try {
        std::string cascadePath = "haarcascade_frontalface_default.xml";
        FaceDetection faceDetector(cascadePath);

        std::string inputPath = "test_image.jpg";
        std::string outputPathBlur = "output_blur.jpg";
        std::string outputPathMask = "output_mask.jpg";

        cv::Mat image = ImageManager::loadImage(inputPath);
        std::vector<cv::Rect> faces = faceDetector.detectFaces(image);

        BlurProcessor blurProcessor(15);
        blurProcessor.process(image, faces);
        ImageManager::saveImage(image, outputPathBlur);
        std::cout << "Blurred image saved to: " << outputPathBlur << std::endl;

        cv::Mat image2 = ImageManager::loadImage(inputPath);
        MaskProcessor maskProcessor(cv::Scalar(0, 255, 0));
        maskProcessor.process(image2, faces);
        ImageManager::saveImage(image2, outputPathMask);
        std::cout << "Masked image saved to: " << outputPathMask << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
