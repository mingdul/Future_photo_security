#ifndef FACEOBJECT_H
#define FACEOBJECT_H

#include <opencv2/opencv.hpp>

class FaceObject {
public:
    cv::Rect boundingBox;
    cv::Mat faceRegion;

    FaceObject(const cv::Rect& box, const cv::Mat& region);
    bool operator==(const FaceObject& other) const;
};

#endif
