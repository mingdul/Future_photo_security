#include "FaceObject.h"

FaceObject::FaceObject(const cv::Rect& box, const cv::Mat& region) : boundingBox(box), faceRegion(region.clone()) {}

bool FaceObject::operator==(const FaceObject& other) const {
    return boundingBox == other.boundingBox;
}
