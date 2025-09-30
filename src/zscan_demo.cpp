#include "HardwareAbstraction.h"
#include <iostream>
#include <fstream>
#include <vector>

extern class BeamAnalyzer;

int main() {
    SimCamera cam;
    SimMotion stage;

    if (!cam.open()) {
        std::cerr << "Failed to open camera\n";
        return -1;
    }

    std::ofstream fout("zscan_results.csv");
    fout << "z(mm),w_x,w_y\n";

    for (int i = 0; i <= 10; ++i) {
        double z = i * 0.5;
        stage.moveTo(z);
        std::vector<uint16_t> img;
        int w, h;
        cam.grabFrame(img, w, h);
        double x0, y0, wx, wy;
        BeamAnalyzer::computeSecondMoments(img, w, h, x0, y0, wx, wy);
        fout << z << "," << wx << "," << wy << "\n";
        std::cout << "z=" << z << " wx=" << wx << " wy=" << wy << "\n";
    }

    fout.close();
    cam.close();
    return 0;
}
