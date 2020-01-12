#include "MainMenu.h"
#include "vendor/json/json.hpp"
#include "widgets/VisualizerRenderer.h"


MainMenu::MainMenu(void)
{
}

void MainMenu::Process(void)
{
    if ( ImGui::BeginMenuBar() )
    {
        if ( ImGui::BeginMenu("File") )
        {
            FileMenu();
            ImGui::EndMenu();
        }
        if ( ImGui::BeginMenu("Edit") )
        {
            EditMenu();
            ImGui::EndMenu();
        }
        if ( ImGui::BeginMenu("Help") )
        {
            HelpMenu();
            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
}

void MainMenu::FileMenu(void)
{
    if ( ImGui::Button("Open Visualizer") )
    {
        Visualizer::Open();
    }
}

void MainMenu::EditMenu(void)
{
}

void MainMenu::HelpMenu(void)
{
    if ( ImGui::MenuItem("User Guide") )
    {
    }
    if ( ImGui::MenuItem("About") )
    {
    }
}