#pragma once
#include "../../includes.h"

namespace Elements
{
    //Fonts
    extern ImFont* title_font;
    extern ImFont* esp_font;
    extern ImFont* middle_font;
    extern ImFont* bottom_font;

    //Elements
    extern bool Checkbox(const char* label, bool* v);
    extern bool Tab(const char* label, bool selected);
}