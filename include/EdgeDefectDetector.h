#ifndef EDGE_DEFECT_DETECTOR_H
#define EDGE_DEFECT_DETECTOR_H

#include "DetectionStrategy.h"

/**
 * @brief Detects edge defects using Canny edge detection and contour analysis
 * Good for: cracks, scratches, boundary irregularities
 */
class EdgeDefectDetector : public DetectionStrategy {
private:
    double cannyThreshold1;
    double cannyThreshold2;
    double minContourArea;
    
public:
    EdgeDefectDetector(double thresh1 = 50, double thresh2 = 150, 
                       double minArea = 100);
    
    std::vector<Defect> detect(const cv::Mat& image) override;
    std::string getName() const override { return "Edge Defect Detector"; }
};

#endif // EDGE_DEFECT_DETECTOR_H