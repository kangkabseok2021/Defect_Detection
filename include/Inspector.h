#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "DetectionStrategy.h"
#include "ImageProcessor.h"
#include <memory>
#include <string>

/**
 * @brief Main inspection class that coordinates the entire process
 */
class Inspector {
private:
    std::unique_ptr<DetectionStrategy> detectionStrategy;
    ImageProcessor preprocessor;
    
    // Inspection results
    struct InspectionResult {
        bool passed;
        int defectCount;
        std::vector<Defect> defects;
        cv::Mat annotatedImage;
        std::string detectorUsed;
    };
    
public:
    /**
     * @brief Set the detection strategy (swappable algorithms)
     */
    void setDetectionStrategy(std::unique_ptr<DetectionStrategy> strategy);
    
    /**
     * @brief Configure preprocessing pipeline
     */
    ImageProcessor& getPreprocessor() { return preprocessor; }
    
    /**
     * @brief Inspect an image
     * @param image Input image to inspect
     * @param maxDefects Maximum acceptable number of defects
     * @return Inspection result with pass/fail status
     */
    InspectionResult inspect(const cv::Mat& image, int maxDefects = 5);
    
    /**
     * @brief Generate a report of the inspection
     */
    void generateReport(const InspectionResult& result, 
                       const std::string& outputPath);
};

#endif // INSPECTOR_H