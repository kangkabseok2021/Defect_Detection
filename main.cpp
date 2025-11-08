#include "Inspector.h"
#include "BlobDetector.h"
#include "EdgeDefectDetector.h"
#include <iostream>
#include <filesystem>

void demonstrateModularity(const cv::Mat& image);
void runInspection(const std::string& imagePath);

int main(int argc, char** argv) {
    std::cout << "=== Modular Quality Inspection System ===" << std::endl;
    std::cout << "Demonstrating OpenCV and Modular Architecture\n" << std::endl;
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <image_path>" << std::endl;
        std::cout << "\nRunning demo with built-in test..." << std::endl;
        
        // Create a synthetic test image
        cv::Mat testImage = cv::Mat::zeros(600, 800, CV_8UC3);
        testImage.setTo(cv::Scalar(200, 200, 200)); // Light gray background
        
        // Add some synthetic defects
        cv::circle(testImage, cv::Point(200, 200), 30, 
                  cv::Scalar(50, 50, 50), -1); // Dark spot
        cv::circle(testImage, cv::Point(400, 300), 20, 
                  cv::Scalar(50, 50, 50), -1);
        cv::line(testImage, cv::Point(100, 400), cv::Point(300, 500), 
                cv::Scalar(0, 0, 0), 3); // Scratch
        
        demonstrateModularity(testImage);
    } else {
        runInspection(argv[1]);
    }
    
    return 0;
}

void demonstrateModularity(const cv::Mat& image) {
    std::cout << "\n1. Demonstrating Swappable Detection Strategies\n";
    std::cout << std::string(50, '-') << std::endl;
    
    // Create inspector
    Inspector inspector;
    
    // Configure preprocessing
    inspector.getPreprocessor().addStep(
        ImageProcessor::contrastEnhancementStep()
    );
    
    // Test with Blob Detector
    std::cout << "\nTesting with Blob Detector..." << std::endl;
    inspector.setDetectionStrategy(std::make_unique<BlobDetector>());
    auto result1 = inspector.inspect(image, 10);
    std::cout << "  - Found " << result1.defectCount << " defects" << std::endl;
    std::cout << "  - Status: " << (result1.passed ? "PASSED" : "FAILED") 
              << std::endl;
    
    cv::imshow("Blob Detection Results", result1.annotatedImage);
    inspector.generateReport(result1, "blob_report.txt");
    
    // Test with Edge Defect Detector
    std::cout << "\nTesting with Edge Defect Detector..." << std::endl;
    inspector.setDetectionStrategy(
        std::make_unique<EdgeDefectDetector>(50, 150, 50)
    );
    auto result2 = inspector.inspect(image, 10);
    std::cout << "  - Found " << result2.defectCount << " defects" << std::endl;
    std::cout << "  - Status: " << (result2.passed ? "PASSED" : "FAILED") 
              << std::endl;
    
    cv::imshow("Edge Detection Results", result2.annotatedImage);
    inspector.generateReport(result2, "edge_report.txt");
    
    std::cout << "\n2. Demonstrating Modular Preprocessing\n";
    std::cout << std::string(50, '-') << std::endl;
    
    // Show different preprocessing combinations
    ImageProcessor processor;
    
    // Pipeline 1: Normalize only
    processor.addStep(ImageProcessor::normalizeStep());
    cv::Mat processed1 = processor.process(image);
    cv::imshow("Preprocessing: Normalized", processed1);
    
    // Pipeline 2: Normalize + Contrast Enhancement
    processor.clear();
    processor.addStep(ImageProcessor::normalizeStep());
    processor.addStep(ImageProcessor::contrastEnhancementStep());
    cv::Mat processed2 = processor.process(image);
    cv::imshow("Preprocessing: Normalized + Contrast", processed2);
    
    std::cout << "\n3. Key Architecture Features Demonstrated:\n";
    std::cout << "  ✓ Strategy Pattern for swappable algorithms\n";
    std::cout << "  ✓ Pipeline Pattern for preprocessing\n";
    std::cout << "  ✓ Separation of concerns (detection, processing, reporting)\n";
    std::cout << "  ✓ Reusable components\n";
    std::cout << "  ✓ Easy to extend with new detectors\n";
    
    std::cout << "\nPress Cntl + C keys to close windows..." << std::endl;
    cv::waitKey(0);

    cv::destroyAllWindows();
}

void runInspection(const std::string& imagePath) {
    // Load image
    cv::Mat image = cv::imread(imagePath);
    
    if (image.empty()) {
        std::cerr << "Error: Could not load image: " << imagePath << std::endl;
        return;
    }
    
    std::cout << "Loaded image: " << imagePath << std::endl;
    std::cout << "Size: " << image.cols << "x" << image.rows << std::endl;
    
    demonstrateModularity(image);
}