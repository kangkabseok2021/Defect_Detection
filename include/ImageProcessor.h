#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <functional>
#include <vector>

/**
 * @brief Modular image preprocessing pipeline
 * Allows chaining of preprocessing steps
 */
class ImageProcessor {
public:
    using ProcessingStep = std::function<cv::Mat(const cv::Mat&)>;
    
    /**
     * @brief Add a processing step to the pipeline
     */
    void addStep(ProcessingStep step);
    
    /**
     * @brief Process image through all steps in the pipeline
     */
    cv::Mat process(const cv::Mat& input) const;
    
    /**
     * @brief Clear all processing steps
     */
    void clear();
    
    // Common preprocessing steps (static factory methods)
    static ProcessingStep resizeStep(const cv::Size& size);
    static ProcessingStep normalizeStep();
    static ProcessingStep contrastEnhancementStep();
    static ProcessingStep denoiseStep();
    
private:
    std::vector<ProcessingStep> steps;
};

#endif // IMAGE_PROCESSOR_H