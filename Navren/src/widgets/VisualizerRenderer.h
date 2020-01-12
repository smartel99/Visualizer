#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <array>
#include <vector>

namespace Visualizer
{
    void Init(void);
    void Open(void);
    void Render(void);
    void SetBand(const std::array<int, 30>& vals);
    void SetBand(const std::vector<int>& vals);
    void SetBand(int band, int val);
}

#endif
