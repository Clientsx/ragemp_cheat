#include "./elements.h"
#include "../../imgui/imgui_internal.h"
using namespace ImGui;

namespace Elements
{
    //Fonts
    ImFont* title_font = nullptr;
    ImFont* esp_font = nullptr;
    ImFont* middle_font = nullptr;
    ImFont* bottom_font = nullptr;

    //Elements
    bool Checkbox(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const ImRect check_bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x + label_size.y + style.FramePadding.y * 2, window->DC.CursorPos.y + label_size.y + style.FramePadding.y * 2));
        ItemSize(check_bb, style.FramePadding.y);

        ImRect total_bb = check_bb;
        if (label_size.x > 0)
            SameLine(0, style.ItemInnerSpacing.x);
        const ImRect text_bb(ImVec2(window->DC.CursorPos.x + 0, window->DC.CursorPos.y + style.FramePadding.y), ImVec2(window->DC.CursorPos.x + 0 + label_size.x, window->DC.CursorPos.y + style.FramePadding.y + label_size.y));
        if (label_size.x > 0)
        {
            ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
            total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
        }

        if (!ItemAdd(total_bb, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
            *v = !(*v);

        window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x - 1.f, check_bb.Min.y - 1.f), ImVec2(check_bb.Max.x + 1.f, check_bb.Max.y + 1.f), ImColor(48, 48, 48, 255), 4.0f);
        RenderFrame(check_bb.Min, check_bb.Max, ImColor(18, 18, 18, 255), true, 4.0f);
        if (*v)
        {
            const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());
            const float pad = ImMax(1.0f, (float)(int)(check_sz / 6.0f));
            window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x, check_bb.Min.y), ImVec2(check_bb.Max.x, check_bb.Max.y), ImColor(255, 14, 14, 255), 4.0f);
        }

        if (g.LogEnabled)
            LogRenderedText(&total_bb.Min, *v ? "[X]" : "[]");
        if (label_size.x > 0.0f)
            RenderText(text_bb.GetTL(), label);

        return pressed;
    }

    bool Tab(const char* label, bool selected)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImGui::CalcItemSize(ImVec2(162.5f, 35.5f), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        if (hovered || held)
            ImGui::SetMouseCursor(7);

        auto windowWidth = 162.5f;
        auto textWidth = ImGui::CalcTextSize(label).x;
        if (selected)
        {
            window->DrawList->AddText(title_font, 15.0f, ImVec2(pos.x + (windowWidth - textWidth) * 0.5f, bb.Min.y + (size.y / 2) - (label_size.y / 2)), ImColor(255, 14, 14, 255), label);
        }
        else
        {
            window->DrawList->AddText(title_font, 15.0f, ImVec2(pos.x + (windowWidth - textWidth) * 0.5f, bb.Min.y + (size.y / 2) - (label_size.y / 2)), ImColor(255, 255, 255, 255), label);
        }

        return pressed;
    }
}