#pragma once
#include <vector>
#include <string>

struct Point3D { double x, y, z; };
struct Point2D { double u, v; };

struct CameraIntrinsics {
    double fx, fy, cx, cy;
};

struct CameraExtrinsics {
    double R[3][3]; 
    double t[3];    
};

enum class ReprojectionStatus {
    SUCCESS,
    INVALID_DEPTH, 
    INVALID_PARAM
};

struct ReprojectionResult {
    ReprojectionStatus status;
    Point2D pixel;
    std::string message;
    double error_distance;
};

ReprojectionResult reprojectPoint(
    const Point3D& pw, 
    const CameraIntrinsics& K, 
    const CameraExtrinsics& T
);