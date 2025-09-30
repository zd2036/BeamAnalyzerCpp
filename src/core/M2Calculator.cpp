#include "core/M2Calculator.h"
#include <cmath>
#include <limits>

M2Result M2Calculator::computeM2(const std::vector<double>& z, const std::vector<double>& D4sigma, double lambda) {
    M2Result res;
    size_t n = z.size();
    if (n < 6 || n != D4sigma.size()) { res.M2 = NAN; return res; }
    std::vector<double> W2(n);
    for (size_t i = 0; i < n; ++i) {
        double W = D4sigma[i] / 2.0;
        W2[i] = W*W;
    }
    double zmin = z.front(), zmax = z.back();
    for (double t : z) { if (t < zmin) zmin = t; if (t > zmax) zmax = t; }
    double range = (zmax - zmin);
    double z0_lo = zmin - 0.2*range;
    double z0_hi = zmax + 0.2*range;
    double best_rss = std::numeric_limits<double>::infinity();
    double best_z0 = 0, best_a = 0, best_b = 0;
    int steps = 500;
    for (int s = 0; s <= steps; ++s) {
        double z0 = z0_lo + (z0_hi - z0_lo) * (double(s) / double(steps));
        double Sx = 0, Sxx = 0, Sy = 0, Sxy = 0;
        for (size_t i = 0; i < n; ++i) {
            double X = (z[i] - z0);
            X = X*X;
            double y = W2[i];
            Sx += X; Sxx += X*X; Sy += y; Sxy += X*y;
        }
        double denom = (double)n * Sxx - Sx * Sx;
        if (std::abs(denom) < 1e-16) continue;
        double a = (double(n) * Sxy - Sx * Sy) / denom;
        double b = (Sxx * Sy - Sx * Sxy) / denom;
        double rss = 0;
        for (size_t i = 0; i < n; ++i) {
            double X = (z[i] - z0); X = X*X;
            double pred = a * X + b;
            double diff = W2[i] - pred;
            rss += diff * diff;
        }
        if (rss < best_rss) {
            best_rss = rss;
            best_z0 = z0; best_a = a; best_b = b;
        }
    }
    if (best_b <= 0 || best_a <= 0) { res.M2 = NAN; return res; }
    res.fitA = best_a; res.fitB = best_b; res.z0 = best_z0;
    res.W0 = std::sqrt(best_b);
    res.M2 = (M_PI / lambda) * std::sqrt(best_a * best_b);
    res.rss = best_rss;
    return res;
}
