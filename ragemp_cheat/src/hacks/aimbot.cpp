#include "aimbot.h"

namespace Aimbot
{
	int current_target = -1;

	float screen_distance(float Xx, float Yy, float xX, float yY)
	{
		return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
	}

	float get_distance(Vector3 to, Vector3 from) {
		return (sqrt(
			((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
	}

	void getBestTarget()
	{
		if (Memory::Check::isPlayerValid())
		{
			DWORD64 cam = Memory::GetCamera();
			if (Helper::ValidPTR(cam)) {
				Vector3 CrosshairPos = *(Vector3*)(cam + 0x60);
				static float oldDistance = FLT_MAX;
				float newDistance = 0;

				if (current_target == -1) oldDistance = FLT_MAX;

				for (int i = 0; i < 255; i++) {
					DWORD64 nPed = Pool::players[i].ped;
					if (nPed == NULL) continue;
					if (nPed == Memory::LocalPlayer) continue;

					ImVec2 aim2d = Memory::GetBonePosW2S(nPed, 0x9995);

					newDistance = screen_distance(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2, aim2d.x, aim2d.y);
					if (newDistance < oldDistance && newDistance < Config::Aimbot_Fov) {
						oldDistance = newDistance;
						current_target = i;
					}
				}
			}
		}
		else
		{
			current_target = -1;
		}
	}

	void Tick()
	{
		if (!Config::Aimbot_Toggle) return;
		auto draw_list = ImGui::GetBackgroundDrawList();
		if (Config::DrawFov) draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), Config::Aimbot_Fov, ImColor(255, 255, 255, 255), 12, 0.8f);

		__try
		{
			if (GetAsyncKeyState(Config::HotKeyAim) & 0x8000) {
				DWORD64 cam = Memory::GetCamera();
				if (Helper::ValidPTR(cam)) {
					if (current_target == -1) getBestTarget();

					if (current_target != -1) {
						DWORD64 target = Pool::players[current_target].ped;
						if (!target) {
							current_target = -1;
							return;
						}

						Vector3 CrosshairPos = *(Vector3*)(cam + 0x60);
						Vector3 aimpos = Memory::GetBonePosVec3(target, 0x9995);
						ImVec2 aim2d = Memory::GetBonePosW2S(target, 0x9995);

						auto Distance = get_distance(CrosshairPos, aimpos);
						float Distance2d = screen_distance(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2, aim2d.x, aim2d.y);

						Vector3 Out = Vector3((aimpos.x - CrosshairPos.x) / Distance, (aimpos.y - CrosshairPos.y) / Distance, (aimpos.z - CrosshairPos.z) / Distance);

						*(Vector3*)(cam + 0x40) = Out;  //FPS
						*(Vector3*)(cam + 0x3D0) = Out; //TPS
					}
				}
			}
			else {
				current_target = -1;
			}
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
	}
}