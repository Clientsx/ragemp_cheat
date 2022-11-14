#include "./visuals.h"

namespace Visuals
{

	bool isInScreen(const ImVec2& from, const ImVec2& to) {
		float ScreenCX = ImGui::GetIO().DisplaySize.x;
		float ScreenCY = ImGui::GetIO().DisplaySize.y;
		if ((from.x >= 0) && (from.x <= (ScreenCX)) & (from.y >= 0) & (from.y <= (ScreenCY)))
		{
			if ((to.x >= 0) & (to.x <= (ScreenCX)) & (to.y >= 0) & (to.y <= (ScreenCY)))
			{
				return true;
			}
		}
		return false;
	}

	void DrawBoneLine(ImVec2 start, ImVec2 stop)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		if (isInScreen(start, stop))
			draw_list->AddLine(start, stop, ImColor(255, 255, 255, 150), 0.8f);
	}


	void draw_bones(DWORD64 cPed) {
		const auto rToe = Memory::GetBonePosW2S(cPed, 0x512D);
		const auto rFoot = Memory::GetBonePosW2S(cPed, 0xCC4D);
		const auto rCalf = Memory::GetBonePosW2S(cPed, 0x9000);
		const auto rThigh = Memory::GetBonePosW2S(cPed, 0xCA72);

		const auto lToe = Memory::GetBonePosW2S(cPed, 0x083C);
		const auto lFoot = Memory::GetBonePosW2S(cPed, 0x3779);
		const auto lCalf = Memory::GetBonePosW2S(cPed, 0xF9BB);
		const auto lThigh = Memory::GetBonePosW2S(cPed, 0xE39F);

		const auto pelvis = Memory::GetBonePosW2S(cPed, 0x2E28);
		const auto spineRoot = Memory::GetBonePosW2S(cPed, 0xE0FD);
		const auto spine0 = Memory::GetBonePosW2S(cPed, 0x5C01);
		const auto spine1 = Memory::GetBonePosW2S(cPed, 0x60F0);
		const auto spine2 = Memory::GetBonePosW2S(cPed, 0x60F1);
		const auto spine3 = Memory::GetBonePosW2S(cPed, 0x60F2);

		const auto lClavicle = Memory::GetBonePosW2S(cPed, 0xFCD9);
		const auto lUpperArm = Memory::GetBonePosW2S(cPed, 0xB1C5);
		const auto lForearm = Memory::GetBonePosW2S(cPed, 0xEEEB);
		const auto lHand = Memory::GetBonePosW2S(cPed, 0x49D9);

		const auto rClavicle = Memory::GetBonePosW2S(cPed, 0x29D2);
		const auto rUpperArm = Memory::GetBonePosW2S(cPed, 0x9D4D);
		const auto rForearm = Memory::GetBonePosW2S(cPed, 0x6E5C);
		const auto rHand = Memory::GetBonePosW2S(cPed, 0xDEAD);

		const auto neck = Memory::GetBonePosW2S(cPed, 0x9995);
		const auto head = Memory::GetBonePosW2S(cPed, 0x796E);

		DrawBoneLine(rToe, rFoot);
		DrawBoneLine(rFoot, rCalf);
		DrawBoneLine(rCalf, rThigh);
		DrawBoneLine(rThigh, pelvis);

		DrawBoneLine(lToe, lFoot);
		DrawBoneLine(lFoot, lCalf);
		DrawBoneLine(lCalf, lThigh);
		DrawBoneLine(lThigh, pelvis);

		DrawBoneLine(pelvis, spineRoot);
		DrawBoneLine(spineRoot, spine0);
		DrawBoneLine(spine0, spine1);
		DrawBoneLine(spine1, spine2);
		DrawBoneLine(spine2, spine3);
		DrawBoneLine(spine3, neck);
		DrawBoneLine(neck, head);

		DrawBoneLine(lClavicle, lUpperArm);
		DrawBoneLine(lUpperArm, lForearm);
		DrawBoneLine(lForearm, lHand);

		DrawBoneLine(rClavicle, rUpperArm);
		DrawBoneLine(rUpperArm, rForearm);
		DrawBoneLine(rForearm, rHand);

		DrawBoneLine(rClavicle, neck);
		DrawBoneLine(lClavicle, neck);
	}

	void Tick()
	{
		if (!Config::Npc_Esp) return;

		for (int i = 0; i < 255; i++) {
			DWORD64 nPed = Pool::players[i].ped;
			if (nPed == NULL) continue;
			if (!Helper::ValidPTR(nPed)) continue;

			Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
			Vector3 pedPos = Vector3(Pool::players[i].position.x, Pool::players[i].position.y, Pool::players[i].position.z);
			auto Distance = Aimbot::get_distance(localpos, Pool::players[i].position);
			int dif = (int)Distance / 30;
			int fontSize = 18 - dif <= 2 ? 2 : (18 - dif);

			ImVec2 player_pos = Memory::WorldToScreen(localpos);
			ImVec2 screen_ped_pos = Memory::WorldToScreen(Vector3(pedPos.x, pedPos.y, pedPos.z - 1.0f));
			ImVec2 screenHead_ped_pos = Memory::WorldToScreen(Vector3(pedPos.x, pedPos.y, pedPos.z + 0.9f));

			if (screen_ped_pos.x > 0 && screenHead_ped_pos.x > 0)
			{
				float h = screenHead_ped_pos.y - screen_ped_pos.y;
				float h2 = screenHead_ped_pos.x - screen_ped_pos.x;
				float w = (screen_ped_pos.y - screenHead_ped_pos.y) / 3.5f;
				auto draw_list = ImGui::GetBackgroundDrawList();

				if (Config::Npc_Bone_Esp)
				{
					draw_bones(nPed);
				}

				if (Config::Npc_Health_Esp)
				{
					float health = *(float*)(nPed + 0x280) - 100.0f;
					if (health > 200.0f)    health = 200.0f;
					else if (health < 0.0f) health = 0.0f;

					float armor = *(float*)(nPed + 0x150C);
					if (armor > 100.0f)    armor = 100.0f;
					else if (armor < 0.0f) armor = 0.0f;

					float oneHealth2 = h / 100;
					draw_list->AddLine(ImVec2(screen_ped_pos.x - w - 6.0f, screen_ped_pos.y), ImVec2(screen_ped_pos.x - w - 6.0f, screenHead_ped_pos.y), ImColor(0, 0, 0, 150), 2.0f);
					draw_list->AddLine(ImVec2(screen_ped_pos.x - w - 6.0f, screen_ped_pos.y), ImVec2(screen_ped_pos.x - w - 6.0f, screenHead_ped_pos.y - h + oneHealth2 * health), ImColor(80, 150, 80, 255), 2.0f);
					std::string player_armor_string = "[" + std::to_string((int)round(armor)) + "]";
					draw_list->AddText(ImVec2(screen_ped_pos.x - (ImGui::CalcTextSize(player_armor_string.c_str()).x / 2), screen_ped_pos.y + 23), ImColor(0, 0, 255, 255), player_armor_string.c_str());

					if (armor > 0)
					{
						draw_list->AddLine(ImVec2(screen_ped_pos.x - w - 9.0f, screen_ped_pos.y), ImVec2(screen_ped_pos.x - w - 9.0f, screenHead_ped_pos.y), ImColor(0, 0, 0, 150), 2.0f);
						draw_list->AddLine(ImVec2(screen_ped_pos.x - w - 9.0f, screen_ped_pos.y), ImVec2(screen_ped_pos.x - w - 9.0f, screenHead_ped_pos.y - h + oneHealth2 * armor), ImColor(40, 140, 185, 255), 2.0f);
					}
				}

				if (Config::Npc_Box_Esp)
				{
					if (Config::Npc_Box_Esp_Type == 0)
					{
						draw_list->AddLine(ImVec2(screen_ped_pos.x - w, screenHead_ped_pos.y), ImVec2(screen_ped_pos.x + w, screenHead_ped_pos.y), ImColor(140, 200, 255, 255), 0.8f); // Oben
						draw_list->AddLine(ImVec2(screen_ped_pos.x - w, screen_ped_pos.y), ImVec2(screen_ped_pos.x - w, screenHead_ped_pos.y), ImColor(140, 200, 255, 255), 0.8f); // Links
						draw_list->AddLine(ImVec2(screen_ped_pos.x + w, screen_ped_pos.y), ImVec2(screen_ped_pos.x + w, screenHead_ped_pos.y), ImColor(140, 200, 255, 255), 0.8f); // Rechts
						draw_list->AddLine(ImVec2(screen_ped_pos.x - w, screen_ped_pos.y), ImVec2(screen_ped_pos.x + w, screen_ped_pos.y), ImColor(140, 200, 255, 255), 0.8f); // Unten
					}
					else
					{

					}
				}

				if (Config::Npc_Snapline_Esp)
				{
					ImVec2 screen_player_pos = Memory::WorldToScreen(Vector3(localpos.x, localpos.y, localpos.z - 1.0f));
					ImVec2 screen_ped_pos2 = Memory::WorldToScreen(pedPos);
					if (screen_player_pos.x > 0 && screen_ped_pos2.x > 0)
					{
						draw_list->AddLine(ImVec2(screen_player_pos.x, screen_player_pos.y), ImVec2(screen_ped_pos2.x, screen_ped_pos2.y), ImColor(255, 255, 255, 70), 0.8f);

					}
				}

				if (Config::Npc_Barrel_Esp)
				{

				}
			}
		}
	}
}