#include <iostream>
#include <cmath>
#include "reprojection.hpp"

double calculateDistance(const Point2D& p1, const Point2D& p2) {
    return std::sqrt(std::pow(p1.u - p2.u, 2) + std::pow(p1.v - p2.v, 2));
}

int main() {
    CameraIntrinsics K = {500.0, 500.0, 320.0, 240.0};
    CameraExtrinsics T = {
        {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},
        {0, 0, 5}
    };

    Point3D pw_valid = {0.0, 0.0, 2.0};
    ReprojectionResult res1 = reprojectPoint(pw_valid, K, T);
    
    std::cout << "--- Test 1: Valid Point ---" << std::endl;
    if (res1.status == ReprojectionStatus::SUCCESS) {
        std::cout << "Projected Pixel: (" << res1.pixel.u << ", " << res1.pixel.v << ")" << std::endl;
        Point2D observed = {320.0, 240.0};
        std::cout << "Euclidean Error: " << calculateDistance(res1.pixel, observed) << " pixels" << std::endl;
    } else {
        std::cout << res1.message << std::endl;
    }

    Point3D pw_invalid = {0.0, 0.0, -10.0};
    ReprojectionResult res2 = reprojectPoint(pw_invalid, K, T);
    
    std::cout << "\n--- Test 2: Invalid Point (Negative Depth) ---" << std::endl;
    if (res2.status == ReprojectionStatus::INVALID_DEPTH) {
        std::cout << "Caught Exception correctly: " << res2.message << std::endl;
    } else {
        std::cout << "Failed to catch negative depth!" << std::endl;
    }

    return 0;
}