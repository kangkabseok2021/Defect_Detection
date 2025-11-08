#include "EdgeDefectDetector.h"

EdgeDefectDetector::EdgeDefectDetector(double thresh1, double thresh2, 
                                       double minArea)
    : cannyThreshold1(thresh1), cannyThreshold2(thresh2), 
      minContourArea(minArea) {}

std::vector<Defect> EdgeDefectDetector::detect(const cv::Mat& image) {
    std::vector<Defect> defects;
    
    // Convert to grayscale
    cv::Mat gray;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = image.clone();
    }
    
    // Apply Gaussian blur to reduce noise
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5);
    
    // Canny edge detection
    cv::Mat edges;
    cv::Canny(gray, edges, cannyThreshold1, cannyThreshold2);
    
    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, 
                     cv::CHAIN_APPROX_SIMPLE);
    
    // Analyze contours
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        
        if (area < minContourArea) {
            continue; // Skip small contours
        }
        
        // Get bounding box and center
        cv::Rect bbox = cv::boundingRect(contour);
        cv::Moments m = cv::moments(contour);
        cv::Point2f center(m.m10 / m.m00, m.m01 / m.m00);
        
        // Calculate defect characteristics
        double perimeter = cv::arcLength(contour, true);
        double circularity = 4 * CV_PI * area / (perimeter * perimeter);
        
        // Low circularity suggests an edge defect (crack/scratch)
        float confidence = 1.0f - static_cast<float>(circularity);
        
        defects.emplace_back(center, static_cast<float>(area), 
                           bbox, "edge_defect", confidence);
    }
    
    return defects;
}