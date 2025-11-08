# Mini-Project: Modular Quality Inspection System
## OpenCV Demo for ASYS Group Interview

---

## Project Overview

**Purpose:** Demonstrate practical OpenCV skills and modular software architecture for industrial quality inspection

**What It Demonstrates:**
- OpenCV proficiency (image processing, defect detection)
- Modular, reusable architecture
- C++ best practices
- Real-world industrial application understanding

---

## System Architecture

```
┌─────────────────────────────────────────────────┐
│         Quality Inspection Pipeline             │
├─────────────────────────────────────────────────┤
│                                                 │
│  ┌──────────────┐      ┌──────────────┐         │
│  │   Image      │─────>│ Preprocessing│         │
│  │ Acquisition  │      │    Module    │         │
│  └──────────────┘      └──────┬───────┘         │
│                               │                 │
│                               v                 │
│                       ┌──────────────┐          │
│                       │  Detection   │          │
│                       │   Module     │          │
│                       │ (Swappable)  │          │
│                       └──────┬───────┘          │
│                              │                  │
│                              v                  │
│                       ┌──────────────┐          │
│                       │ Validation & │          │
│                       │  Reporting   │          │
│                       └──────────────┘          │
└─────────────────────────────────────────────────┘
```

---

## Implementation

### File Structure
```
QualityInspection/
├── include/
│   ├── ImageProcessor.h
│   ├── DetectionStrategy.h
│   ├── BlobDetector.h
│   ├── EdgeDefectDetector.h
│   └── Inspector.h
├── src/
│   ├── ImageProcessor.cpp
|   |── DetectionStrategy.cpp
│   ├── BlobDetector.cpp
│   ├── EdgeDefectDetector.cpp
│   └── Inspector.cpp
├── test_images/
│   └── (sample images)
└── main.cpp
```

# How to Build and Run

### Windows (Visual Studio)

1. **Install OpenCV:**
   - Download from opencv.org
   - Extract to `C:\opencv`
   - Set environment variable: `OPENCV_DIR = C:\opencv\build`

2. **Create Build Directory:**
   ```cmd
   mkdir build
   cd build
   ```

3. **Generate Visual Studio Solution:**
   ```cmd
   cmake .. -G "Visual Studio 16 2019"
   ```

4. **Open in Visual Studio:**
   - Open `QualityInspection.sln`
   - Build solution (F7)
   - Run (F5)

### Linux

```bash
# Install OpenCV
sudo apt-get install libopencv-dev

# Build
mkdir build && cd build
cmake ..
make

# Run
./bin/QualityInspection [optional_image_path]
```
