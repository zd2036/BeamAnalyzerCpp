#pragma once
#include <vector>
#include <string>

// 相机接口
class ICamera {
public:
    virtual ~ICamera() = default;
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool grabFrame(std::vector<uint16_t>& image, int& width, int& height) = 0;
};

// 位移台接口
class IMotion {
public:
    virtual ~IMotion() = default;
    virtual bool moveTo(double pos_mm) = 0;
    virtual double getPosition() = 0;
};
