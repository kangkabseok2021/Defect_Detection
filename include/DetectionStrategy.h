#ifndef DETECTION_STRATEGY_H
#define DETECTION_STRATEGY_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

/**
 * @brief Structure to represent a detected defect
 */
struct Defect {
    cv::Point2f center;
    float area;
    cv::Rect boundingBox;
    std::string type;
    float confidence;
    
    Defect(cv::Point2f c, float a, cv::Rect bb, 
           std::string t = "unknown", float conf = 1.0)
        : center(c), area(a), boundingBox(bb), 
          type(t), confidence(conf) {}
};

/**
 * @brief Abstract base class for detection strategies
 * This allows swapping detection algorithms at runtime (Strategy Pattern)
 */
class DetectionStrategy {
public:
    virtual ~DetectionStrategy() = default;
    
    /**
     * @brief Detect defects in the input image
     * @param image Input image to analyze
     * @return Vector of detected defects
     */
    virtual std::vector<Defect> detect(const cv::Mat& image) = 0;
    
    /**
     * @brief Get the name of this detection strategy
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Draw detection results on image
     */
    virtual void visualize(cv::Mat& image, 
                          const std::vector<Defect>& defects) const;
};

#endif // DETECTION_STRATEGY_H