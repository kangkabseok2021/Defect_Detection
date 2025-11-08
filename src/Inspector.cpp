#include "Inspector.h"
#include <fstream>
#include <iomanip>

void Inspector::setDetectionStrategy(
    std::unique_ptr<DetectionStrategy> strategy) {
    detectionStrategy = std::move(strategy);
}

Inspector::InspectionResult Inspector::inspect(const cv::Mat& image, 
                                               int maxDefects) {
    InspectionResult result;
    
    // Preprocessing
    cv::Mat processed = preprocessor.process(image);
    
    // Detection
    if (detectionStrategy) {
        result.defects = detectionStrategy->detect(processed);
        result.detectorUsed = detectionStrategy->getName();
    }
    
    result.defectCount = static_cast<int>(result.defects.size());
    result.passed = (result.defectCount <= maxDefects);
    
    // Create annotated image
    result.annotatedImage = image.clone();
    if (detectionStrategy) {
        detectionStrategy->visualize(result.annotatedImage, result.defects);
    }
    
    return result;
}

void Inspector::generateReport(const InspectionResult& result, 
                               const std::string& outputPath) {
    std::ofstream report(outputPath);
    
    report << "=== Quality Inspection Report ===\n\n";
    report << "Detector Used: " << result.detectorUsed << "\n";
    report << "Status: " << (result.passed ? "PASSED" : "FAILED") << "\n";
    report << "Defects Found: " << result.defectCount << "\n\n";
    
    report << "Defect Details:\n";
    report << std::setw(5) << "ID" 
           << std::setw(15) << "Type"
           << std::setw(15) << "Center (x,y)"
           << std::setw(12) << "Area"
           << std::setw(12) << "Confidence\n";
    report << std::string(60, '-') << "\n";
    
    for (size_t i = 0; i < result.defects.size(); ++i) {
        const auto& defect = result.defects[i];
        report << std::setw(5) << i 
               << std::setw(15) << defect.type
               << std::setw(8) << defect.center.x 
               << "," << std::setw(5) << defect.center.y
               << std::setw(12) << std::fixed << std::setprecision(2) 
               << defect.area
               << std::setw(12) << defect.confidence << "\n";
    }
    
    report.close();
}