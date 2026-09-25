#include "reprojection.hpp"

ReprojectionResult reprojectPoint(
    const Point3D& pw, 
    const CameraIntrinsics& K, 
    const CameraExtrinsics& T) 
{
    ReprojectionResult result;
    
    double Xc = T.R[0][0]*pw.x + T.R[0][1]*pw.y + T.R[0][2]*pw.z + T.t[0];
    double Yc = T.R[1][0]*pw.x + T.R[1][1]*pw.y + T.R[1][2]*pw.z + T.t[1];
    double Zc = T.R[2][0]*pw.x + T.R[2][1]*pw.y + T.R[2][2]*pw.z + T.t[2];

    if (Zc <= 1e-6) {
        result.status = ReprojectionStatus::INVALID_DEPTH;
        result.message = "Error: Point is behind the camera (Z <= 0).";
        return result;
    }

    double u = K.fx * (Xc / Zc) + K.cx;
    double v = K.fy * (Yc / Zc) + K.cy;

    result.status = ReprojectionStatus::SUCCESS;
    result.pixel = {u, v};
    result.message = "Success";
    return result;
}