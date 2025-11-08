#include "ImageProcessor.h"

void ImageProcessor::addStep(ProcessingStep step) {
    steps.push_back(step);
}

cv::Mat ImageProcessor::process(const cv::Mat& input) const {
    cv::Mat result = input.clone();
    
    for (const auto& step : steps) {
        result = step(result);
    }
    
    return result;
}

void ImageProcessor::clear() {
    steps.clear();
}

// Static factory methods for common operations

ImageProcessor::ProcessingStep 
ImageProcessor::resizeStep(const cv::Size& size) {
    return [size](const cv::Mat& img) {
        cv::Mat resized;
        cv::resize(img, resized, size);
        return resized;
    };
}

ImageProcessor::ProcessingStep 
ImageProcessor::normalizeStep() {
    return [](const cv::Mat& img) {
        cv::Mat normalized;
        cv::normalize(img, normalized, 0, 255, cv::NORM_MINMAX);
        return normalized;
    };
}

ImageProcessor::ProcessingStep 
ImageProcessor::contrastEnhancementStep() {
    return [](const cv::Mat& img) {
        cv::Mat enhanced;
        
        if (img.channels() == 1) {
            cv::equalizeHist(img, enhanced);
        } else {
            cv::Mat ycrcb;
            cv::cvtColor(img, ycrcb, cv::COLOR_BGR2YCrCb);
            
            std::vector<cv::Mat> channels;
            cv::split(ycrcb, channels);
            cv::equalizeHist(channels[0], channels[0]);
            cv::merge(channels, ycrcb);
            
            cv::cvtColor(ycrcb, enhanced, cv::COLOR_YCrCb2BGR);
        }
        
        return enhanced;
    };
}

ImageProcessor::ProcessingStep 
ImageProcessor::denoiseStep() {
    return [](const cv::Mat& img) {
        cv::Mat denoised;
        
        if (img.channels() == 3) {
            cv::fastNlMeansDenoisingColored(img, denoised, 10, 10, 7, 21);
        } else {
            cv::fastNlMeansDenoising(img, denoised, 10, 7, 21);
        }
        
        return denoised;
    };
}