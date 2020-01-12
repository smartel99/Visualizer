#include "VisualizerProcess.h"
#include "VisualizerRenderer.h"
#include "utils/Array.h"
#include "vendor/imgui/imgui.h"


void Visualizer::Process(void)
{
    static double timeElapsed = 0;
    static int frameCount = 0;
    static double deltaTime = ImGui::GetIO().DeltaTime;
    static std::vector<int> bandData = { 5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                                         20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5 };

    if ( frameCount != ImGui::GetFrameCount() )
    {
        frameCount = ImGui::GetFrameCount();
        timeElapsed += deltaTime;
        if ( timeElapsed >= 0.250f )
        {
            timeElapsed = 0;
            Array::RotateLeft(bandData, 1);
            Visualizer::SetBand(bandData);
        }
    }


}
