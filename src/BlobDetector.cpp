#include "BlobDetector.h"

BlobDetector::BlobDetector() {
    // Configure blob detection parameters
    cv::SimpleBlobDetector::Params params;
    
    // Filter by area
    params.filterByArea = true;
    params.minArea = 10;
    params.maxArea = 5000;
    
    // Filter by circularity (how round the blob is)
    params.filterByCircularity = true;
    params.minCircularity = 0.5;
    
    // Filter by convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.8;
    
    // Filter by inertia (how elongated)
    params.filterByInertia = true;
    params.minInertiaRatio = 0.3;
    
    detector = cv::SimpleBlobDetector::create(params);
}

std::vector<Defect> BlobDetector::detect(const cv::Mat& image) {
    std::vector<Defect> defects;
    std::vector<cv::KeyPoint> keypoints;
    
    // Convert to grayscale if needed
    cv::Mat gray;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = image;
    }
    
    // Detect blobs
    detector->detect(gray, keypoints);
    
    // Convert keypoints to Defect objects
    for (const auto& kp : keypoints) {
        float radius = kp.size / 2.0f;
        float area = CV_PI * radius * radius;
        
        cv::Rect bbox(
            static_cast<int>(kp.pt.x - radius),
            static_cast<int>(kp.pt.y - radius),
            static_cast<int>(2 * radius),
            static_cast<int>(2 * radius)
        );
        
        defects.emplace_back(kp.pt, area, bbox, "blob", kp.response);
    }
    
    return defects;
}