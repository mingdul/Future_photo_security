#include "FaceObject.h"

FaceObject::FaceObject(const cv::Rect& box, const cv::Mat& region) : boundingBox(box), faceRegion(region.clone()) {}

//연산자 중복
//이 코드는 FaceObject 객체 간의 동등성 비교를 위해 == 연산자 중복.
//두 FaceObject 객체의 boundingBox(얼굴의 경계 영역)가 동일하면 두 객체를 동일하다고 간주.
bool FaceObject::operator==(const FaceObject& other) const {
    return boundingBox == other.boundingBox;
}
