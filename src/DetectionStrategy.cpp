#include "DetectionStrategy.h"

void DetectionStrategy::visualize(cv::Mat& image, 
                                 const std::vector<Defect>& defects) const {
    for (const auto& defect : defects) {
        // Draw bounding box
        cv::rectangle(image, defect.boundingBox, 
                     cv::Scalar(0, 0, 255), 2);
        
        // Draw center point
        cv::circle(image, defect.center, 3, 
                  cv::Scalar(0, 255, 0), -1);
        
        // Add label
        std::string label = defect.type + " (" + 
                          std::to_string(static_cast<int>(defect.area)) + ")";
        cv::putText(image, label, 
                   cv::Point(defect.boundingBox.x, defect.boundingBox.y - 5),
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, 
                   cv::Scalar(255, 255, 255), 1);
    }
}