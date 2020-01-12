#include "VisualizerRenderer.h"
#include "VisualizerProcess.h"
#include "vendor/imgui/imgui.h"
#include <iostream>

#define BACKGROUND_COLOR(val)   (GetColorFromVal(val)&0x00FFFFFF) + fadedValue;

static ImU32 GetColorFromVal(int val);
static void UpdateFrameBuff(void);

static bool p_open = true;
// Value -> height of bar.
static std::array<int, 30> bands = { 20 };
// X -> 30, Y -> 20. Stores color of each cells.
static std::array<std::array<ImU32, 20>, 30> frameBuffer;
static const int fadeAmount = 0x10000000;
static const int fadedValue = 0x20000000;


void Visualizer::Init(void)
{
    for ( int x = 0; x < frameBuffer.size(); x++ )
    {
        for ( int y = 0; y < frameBuffer[x].size(); y++ )
        {
            frameBuffer[x][y] = BACKGROUND_COLOR(y);
        }
    }
}

void Visualizer::Open(void)
{
    p_open = true;
}

void Visualizer::Render(void)
{
    if ( p_open == false )
    {
        return;
    }
    if ( !ImGui::Begin("Visualizer", &p_open) )
    {
        ImGui::End();
        return;
    }

    UpdateFrameBuff();
    Visualizer::Process();

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 position = ImGui::GetCursorScreenPos();
    ImVec2 windowSize = ImGui::GetWindowContentRegionMax();
    float spacing = 10.f;
    float width = (windowSize.x - (spacing * bands.size())) / bands.size();
    float height = (windowSize.y - (spacing * bands.size())) / 20.f;    // 20 -> Max number of bars on Y axis

    position.y += windowSize.y;
    float x = position.x;
    float y = position.y - 100.f;

    ImVec2 p1(x, y);
    ImVec2 p2(x + width, y + height);

    for ( int xCell = 0; xCell < frameBuffer.size(); xCell++ )
    {
        p1.y = y;
        p2.y = y + height;
        for ( int yCell = 0; yCell < frameBuffer[xCell].size(); yCell++ )
        {
            draw_list->AddRectFilled(p1, p2, frameBuffer[xCell][yCell], 0.0f, 0);  // Square
            p1.y -= spacing + height;
            p2.y -= spacing + height;
        }

        p1.x += spacing + width;
        p2.x += spacing + width;
    }

    ImGui::End();
}

void Visualizer::SetBand(const std::array<int, 30>& vals)
{
    for ( int i = 0; i < bands.size(); i++ )
    {
        bands[i] = vals[i];
    }
}

void Visualizer::SetBand(const std::vector<int>& vals)
{
    for ( int i = 0; i < bands.size(); i++ )
    {
        bands[i] = vals[i];
    }
}

void Visualizer::SetBand(int band, int val)
{
    if ( band >= bands.size() )
    {
        return;
    }

    bands[band] = val > 20 ? 20 : val;    // Clip value at 20.
}

ImU32 GetColorFromVal(int val)
{
    if ( val <= 12 )
    {
        // Green.
        return 0xFF1AFF29;
    }
    else if ( val <= 17 )   // Between 13 and 17.
    {
        // Yellow.
        return 0xFF00FFEF;
    }
    else if ( val <= 20 )   // Between 18 and 20.
    {
        // Red.
        return 0xFF2C2CFF;
    }
    else
    {
        // White.
        return 0xFFFFFFFF;
    }
}

void UpdateFrameBuff(void)
{
    for ( int x = 0; x < bands.size(); x++ )
    {
        int maxVal = bands[x];
        int y = 0;
        for ( y = 0; y <= maxVal; y++ )
        {
            frameBuffer[x][y] = GetColorFromVal(y);
        }

        // Fade out inactive cells.
        for ( ; y <= frameBuffer[x].size(); y++ )
        {
            if ( (frameBuffer[x][y] & IM_COL32_A_MASK) > fadedValue )
            {
                frameBuffer[x][y] -= fadeAmount;
            }
            if ( (frameBuffer[x][y] & IM_COL32_A_MASK) < fadedValue )
            {
                frameBuffer[x][y] += fadedValue - (frameBuffer[x][y] & IM_COL32_A_MASK);
            }
        }
    }
}
