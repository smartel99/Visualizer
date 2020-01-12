#pragma once
#include "imgui/imgui.h"

class MainMenu
{
public:
    MainMenu(void);
    ~MainMenu(void)
    {
    }

    void Process(void);

private:
    void FileMenu(void);
    void EditMenu(void);
    void HelpMenu(void);

};

