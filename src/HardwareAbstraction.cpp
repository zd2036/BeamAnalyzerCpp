#include "HardwareAbstraction.h"
#include <iostream>
#include <thread>
#include <cmath>

// 模拟相机实现
class SimCamera : public ICamera {
public:
    bool open() override { return true; }
    bool close() override { return true; }
    bool grabFrame(std::vector<uint16_t>& image, int& width, int& height) override {
        width = 128;
        height = 128;
        image.resize(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double dx = x - width / 2.0;
                double dy = y - height / 2.0;
                double r2 = dx * dx + dy * dy;
                image[y * width + x] = static_cast<uint16_t>(65535 * exp(-r2 / (2 * 20.0 * 20.0)));
            }
        }
        return true;
    }
};

// 模拟位移台实现
class SimMotion : public IMotion {
    double pos = 0.0;
public:
    bool moveTo(double pos_mm) override {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        pos = pos_mm;
        return true;
    }
    double getPosition() override { return pos; }
};
