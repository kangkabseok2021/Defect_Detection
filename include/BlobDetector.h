#ifndef BLOB_DETECTOR_H
#define BLOB_DETECTOR_H

#include "DetectionStrategy.h"

/**
 * @brief Detects circular/blob-like defects using SimpleBlobDetector
 * Good for: holes, spots, contamination
 */
class BlobDetector : public DetectionStrategy {
private:
    cv::Ptr<cv::SimpleBlobDetector> detector;
    
public:
    BlobDetector();
    
    std::vector<Defect> detect(const cv::Mat& image) override;
    std::string getName() const override { return "Blob Detector"; }
};

#endif // BLOB_DETECTOR_H