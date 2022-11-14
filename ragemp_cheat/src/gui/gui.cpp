#define IMGUI_DEFINE_MATH_OPERATORS
#include "gui.h"

namespace Gui
{
    //Functions

    bool ConvertTabNumberToBool(int value, int mustvalue)
    {
        if (value == mustvalue)
            return true;
        return false;
    }

    void DrawMenu()
    {
        //Breite = 650 - Höhe = 520; - Hauptfarbe = 18, 18, 18 - TabFarbe = 24, 24, 24 - Tabheadfarbe = 32, 32, 32 - Rotfarbe = 255, 14, 14
        auto draw_list = ImGui::GetBackgroundDrawList();
        const ImVec2 pos(ImGui::GetWindowPos().x + 50, ImGui::GetWindowPos().y + 50);
        draw_list->AddRectFilled(ImVec2(pos.x - 1.5f, pos.y - 1.5f), ImVec2(pos.x + 1.5f + 650, pos.y + 1.5f + 520), ImColor(48, 48, 48, 255), 8.f);
        draw_list->AddRectFilled(pos, ImVec2(pos.x + 650, pos.y + 520), ImColor(18, 18, 18, 255), 8.f);
        auto windowWidth = 650;
        auto textWidth = ImGui::CalcTextSize("crmnl - shit").x;
        draw_list->AddText(Elements::title_font, 15.0f, ImVec2(pos.x + (windowWidth - textWidth) * 0.5f, pos.y + 10), ImColor(255, 14, 14, 255), "crmnl - shit");
        draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 35), ImVec2(pos.x + 650, pos.y + 35 + 38), ImColor(48, 48, 48, 255));
        draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 36.5f), ImVec2(pos.x + 650, pos.y + 35 + 37.5f), ImColor(24, 24, 24, 255));

        {
            //top tabs
            ImGui::SetCursorPos(ImVec2(50, 86.5f));

            if (Elements::Tab("Aimbot", ConvertTabNumberToBool(Config::Current_Tab, 0)))
            {
                Config::Current_Tab = 0;
            };
            ImGui::SameLine(0.0f, 0.0f);
            if (Elements::Tab("Visuals", ConvertTabNumberToBool(Config::Current_Tab, 1)))
            {
                Config::Current_Tab = 1;
            };
            ImGui::SameLine(0.0f, 0.0f);
            if (Elements::Tab("Misc", ConvertTabNumberToBool(Config::Current_Tab, 2)))
            {
                Config::Current_Tab = 2;
            };
            ImGui::SameLine(0.0f, 0.0f);
            if (Elements::Tab("Settings", ConvertTabNumberToBool(Config::Current_Tab, 3)))
            {
                Config::Current_Tab = 3;
            };
        }

        //jetzt hier die nogger mitte
        ImGui::SetCursorPos(ImVec2(62.5f, 134));
        draw_list->AddRectFilled(ImVec2(pos.x + 13 - 1.5f, pos.y + 85 - 1.5f), ImVec2(pos.x + 318 + 1.5f, pos.y + 475 + 1.5f), ImColor(48, 48, 48, 255), 4.f);
        draw_list->AddRectFilled(ImVec2(pos.x + 13, pos.y + 85), ImVec2(pos.x + 318, pos.y + 115), ImColor(32, 32, 32, 255), 4.f);
        draw_list->AddRectFilled(ImVec2(pos.x + 13, pos.y + 115), ImVec2(pos.x + 318, pos.y + 475), ImColor(24, 24, 24, 255), 4.f);
        draw_list->AddLine(ImVec2(pos.x + 13, pos.y + 115), ImVec2(pos.x + 318, pos.y + 115), ImColor(48, 48, 48, 255), 1.5f);
        if (Config::Current_Tab == 0)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 18, pos.y + 91), ImColor(255, 255, 255, 255), "Aimbot");

            {
                ImGui::SetCursorPos(ImVec2(70, 180));
                ImGui::BeginGroup();
                {
                    Elements::Checkbox("Enable", &Config::Aimbot_Toggle);
                    Elements::Checkbox("Draw fov", &Config::DrawFov);
                    ImGui::PushItemWidth(290);
                    ImGui::SliderInt("Fov size", &Config::Aimbot_Fov, 10, 400);
                    ImGui::PopItemWidth();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::PushItemWidth(290);
                    ImGui::SliderInt("Smoothness", &Config::Aimbot_Smooth, 0, 50);
                    ImGui::PopItemWidth();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::PushItemWidth(290);
                    ImGui::SliderFloat("Prediction", &Config::Aimbot_Prediction, 0, 2);
                    ImGui::PopItemWidth();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    const char* aimbotbones[3] = { "Head", "Neck", "Body" };
                    ImGui::PushItemWidth(290);
                    ImGui::Combo("Bone", &Config::Aimbot_Bone, aimbotbones, 3);
                    ImGui::PopItemWidth();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    Elements::Checkbox("Horizontal", &Config::Aimbot_HorizontalOnly);
                    Elements::Checkbox("Visible Check", &Config::Aimbot_VisibleCheck);
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::PushItemWidth(290);
                    ImGui::SliderInt("Max Aimbot Distance", &Config::Max_Aimbot_Distance, 10, 1000);
                    ImGui::PopItemWidth();
                }
                ImGui::EndGroup();
            }
        }
        else if (Config::Current_Tab == 1)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 18, pos.y + 91), ImColor(255, 255, 255, 255), "General");

            {
                ImGui::SetCursorPos(ImVec2(70, 180));
                ImGui::BeginGroup();
                {
                    Elements::Checkbox("Enable", &Config::Npc_Esp);
                    Elements::Checkbox("Include self", &Config::Npc_IncludeSelf_Esp);
                    Elements::Checkbox("Include npc", &Config::Npc_IncludeNpc_Esp);
                    Elements::Checkbox("Skeleton", &Config::Npc_Bone_Esp);
                    Elements::Checkbox("Healthbar", &Config::Npc_Health_Esp);
                    Elements::Checkbox("Weapon", &Config::Npc_Weapon_Esp);
                    Elements::Checkbox("Distance", &Config::Npc_Distance_Esp);
                    Elements::Checkbox("Snaplines", &Config::Npc_Snapline_Esp);
                    Elements::Checkbox("Barrel", &Config::Npc_Barrel_Esp);
                    Elements::Checkbox("Box", &Config::Npc_Box_Esp);
                    if (Config::Npc_Box_Esp)
                    {
                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();
                        const char* boxtypes[3] = { "Default", "Corner", "3D" };
                        ImGui::PushItemWidth(290);
                        ImGui::Combo("Boxtype", &Config::Npc_Box_Esp_Type, boxtypes, 3);
                        ImGui::PopItemWidth();
                    }
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::PushItemWidth(290);
                    ImGui::SliderInt("Max ESP Distance", &Config::Npc_Max_Distance, 0, 1000);
                    ImGui::PopItemWidth();
                }
                ImGui::EndGroup();
            }
        }
        else if (Config::Current_Tab == 2)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 18, pos.y + 91), ImColor(255, 255, 255, 255), "General");

            {
                ImGui::SetCursorPos(ImVec2(70, 180));
                ImGui::BeginGroup();
                {
                    Elements::Checkbox("No spread", &Config::No_Spread);
                    Elements::Checkbox("No recoil", &Config::No_Recoil);
                    Elements::Checkbox("Player god", &Config::God_Mode);
                    Elements::Checkbox("No gravity", &Config::NoGravity);
                    Elements::Checkbox("Noclip", &Config::NoClip);
                    Elements::Checkbox("Smooth Fly", &Config::FlyHack);
                    Elements::Checkbox("No ragdoll", &Config::NoRagdoll);
                    Elements::Checkbox("Seatbelt", &Config::Seatbelt);
                    Elements::Checkbox("Engine always on", &Config::StartEngineCars);
                    Elements::Checkbox("Unlock all veh", &Config::UseLockedCars);
                }
                ImGui::EndGroup();
            }
        }
        else if (Config::Current_Tab == 3)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 18, pos.y + 91), ImColor(255, 255, 255, 255), "Configs");

            {
                ImGui::SetCursorPos(ImVec2(70, 180));
                ImGui::BeginGroup();
                {
                //Checkbox
                }
                ImGui::EndGroup();
            }
        }

        ImGui::SetCursorPos(ImVec2(380, 134));
        draw_list->AddRectFilled(ImVec2(pos.x + 334 - 1.5f, pos.y + 85 - 1.5f), ImVec2(pos.x + 638 + 1.5f, pos.y + 475 + 1.5f), ImColor(48, 48, 48, 255), 4.f);
        draw_list->AddRectFilled(ImVec2(pos.x + 334, pos.y + 85), ImVec2(pos.x + 638, pos.y + 115), ImColor(32, 32, 32, 255), 4.f);
        draw_list->AddRectFilled(ImVec2(pos.x + 334, pos.y + 115), ImVec2(pos.x + 638, pos.y + 475), ImColor(24, 24, 24, 255), 4.f);
        draw_list->AddLine(ImVec2(pos.x + 334, pos.y + 115), ImVec2(pos.x + 638, pos.y + 115), ImColor(48, 48, 48, 255), 1.5f);
        if (Config::Current_Tab == 0)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 340, pos.y + 91), ImColor(255, 255, 255, 255), "Triggerbot");

            {
                ImGui::SetCursorPos(ImVec2(392.5f, 180));
                //Checkbox
            }
        }
        else if (Config::Current_Tab == 1)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 340, pos.y + 91), ImColor(255, 255, 255, 255), "Colors");

            {
                ImGui::SetCursorPos(ImVec2(392.5f, 180));
                //Checkbox
            }
        }
        else if (Config::Current_Tab == 2)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 340, pos.y + 91), ImColor(255, 255, 255, 255), "Extra");

            {
                ImGui::SetCursorPos(ImVec2(392.5f, 180));
                //Checkbox
            }
        }
        else if (Config::Current_Tab == 3)
        {
            draw_list->AddText(Elements::middle_font, 16.5f, ImVec2(pos.x + 340, pos.y + 91), ImColor(255, 255, 255, 255), "Hotkeys");

            {
                ImGui::SetCursorPos(ImVec2(392.5f, 180));
                //Checkbox
            }
        }

        //bottom
        draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 489), ImVec2(pos.x + 650, pos.y + 520), ImColor(48, 48, 48, 255));
        draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 490), ImVec2(pos.x + 650, pos.y + 520), ImColor(24, 24, 24, 255));
        draw_list->AddText(Elements::bottom_font, 16.5f, ImVec2(pos.x + 13, pos.y + 497.5), ImColor(255, 255, 255, 255), "RAGE:MP");
        draw_list->AddText(Elements::bottom_font, 16.5f, ImVec2(pos.x + 540, pos.y + 497.5), ImColor(255, 255, 255, 255), "Okt 30 2022");
    }
}