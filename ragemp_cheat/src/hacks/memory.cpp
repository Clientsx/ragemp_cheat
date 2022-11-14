#include "memory.h"

namespace Memory
{
	DWORD LocalPlayerHandle = 0x0;
	DWORD64 BASE = 0x0;

	//
	using pointer_handler_t = int32_t(*)(intptr_t pointer);
	typedef BOOLEAN(__cdecl* WorldToScreen_t)(Vector3* WorldPos, float* x, float* y);
	typedef BOOL(__fastcall* fpRemoveWeaponFromPed)(DWORD ped, DWORD hash);
	typedef DWORD64(__fastcall* fpSetVehicleOnGroundProperly)(DWORD vehicle, DWORD unk);
	typedef DWORD64(__fastcall* SetVehicleForwardSpeed_t)(DWORD vehicle, float Speed);
	typedef DWORD64(__fastcall* fpGiveDelayedWeaponToPed)(DWORD ped, DWORD hash, int ammo, bool equipNow);
	typedef DWORD64(__fastcall* tSTART_SHAPE_TEST_RAY)(PVector3 From, PVector3 To, unsigned int flags, unsigned int entity, DWORD64* a8, DWORD64 a9);
	typedef DWORD64(__fastcall* t_GET_RAYCAST_RESULT)(DWORD64 Handle, DWORD* hit, PVector3* VecEnd, PVector3* VecSurface, DWORD* entity);
	typedef int(__fastcall* CLEAR_PED_TASKS_IMMEDIATELY_t)(DWORD ped);
	typedef DWORD64(__fastcall* CLEAR_PED_TASKS_t)(DWORD HandleOfPed);
	typedef DWORD64(__fastcall* fpSetVehiclePlateText)(DWORD vehicle, const char* Text);

	pointer_handler_t pointer_to_handle = nullptr;
	WorldToScreen_t World2Screen = nullptr;
	fpRemoveWeaponFromPed RemoveWeaponFromPed = nullptr;
	fpSetVehicleOnGroundProperly pSetVehicleOnGroundProperly = nullptr;
	SetVehicleForwardSpeed_t SetVehicleForwardSpeed = nullptr;
	static fpGiveDelayedWeaponToPed GiveDelayedWeaponToPed = nullptr;
	tSTART_SHAPE_TEST_RAY _START_SHAPE_TEST_RAY = nullptr;
	t_GET_RAYCAST_RESULT _GET_RAYCAST_RESULT = nullptr;
	CLEAR_PED_TASKS_IMMEDIATELY_t oCLEAR_PED_TASKS_IMMEDIATELY = NULL;
	CLEAR_PED_TASKS_t CLEAR_PED_TASKS = nullptr;
	fpSetVehiclePlateText pSetVehiclePlateText = nullptr;

	//functions
	ImVec2 WorldToScreen(Vector3 WorldPos)
	{
		ImVec2 pos;
		if (Helper::ValidPTR((DWORD64)World2Screen))
		{
			if (static_cast<BOOLEAN>(World2Screen(&WorldPos, &pos.x, &pos.y)))
			{
				pos.x = pos.x * ImGui::GetIO().DisplaySize.x;
				pos.y = pos.y * ImGui::GetIO().DisplaySize.y;
				return pos;
			}
		}
		return pos;
	}

	ImVec2 WorldToScreen2(D3DXVECTOR3 WorldPos)
	{
		return WorldToScreen(Vector3(WorldPos.x, WorldPos.y, WorldPos.z));
	}

	ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(BonePositionAddress)(cPed, &tempVec4, wMask);
		Vector3 x(Vector3::FromM128(tempVec4).x, Vector3::FromM128(tempVec4).y, Vector3::FromM128(tempVec4).z);
		return WorldToScreen(x);
	}

	Vector3 GetBonePosVec3(const int64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(BonePositionAddress)(cPed, &tempVec4, wMask);
		Vector3 x(Vector3::FromM128(tempVec4).x, Vector3::FromM128(tempVec4).y, Vector3::FromM128(tempVec4).z);
		return x;
	}

	PVector3 ToPVector3(Vector3 pVec) {
		return PVector3(pVec.x, pVec.y, pVec.z);
	}
	Vector3 ToVector3(PVector3 pVec) {
		return Vector3(pVec.x, pVec.y, pVec.z);
	}

	DWORD64 World;
	DWORD64 LocalPlayer;
	DWORD64 LocalPlayerInfo;
	DWORD64 Camera;
	DWORD64 ReplayInterface;
	DWORD64 WeaponBase;
	DWORD64 BonePositionAddress;
	DWORD64 BlipPointer;
	DWORD64 FlyPatt;

	void initGame()
	{
		//const char* process = "ragemp_v.exe";
		const char* process = "ragemp_v.exe";

		World = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32"), 0x3);
		World = *(DWORD64*)(World + 0x0);
		LocalPlayer = *(DWORD64*)(World + 0x8);
		LocalPlayerInfo = *(DWORD64*)(LocalPlayer + 0x10C8);
		WeaponBase = *(DWORD64*)(LocalPlayer + 0x10D8);
		ReplayInterface = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D"), 0x3);
		World2Screen = (WorldToScreen_t)Helper::FindPattern(process, "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25 ?? 00 00 00 8B");
		pointer_to_handle = (pointer_handler_t)Helper::FindPattern(process, "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB");
		Camera = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"), 0x3);
		BonePositionAddress = Helper::FindPattern(process, "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB");
		BlipPointer = Helper::GetPointerAddress(Helper::FindPattern(process, "4C 8D 05 ? ? ? ? 0F B7 C1"), 0x3);
		FlyPatt = Helper::FindPattern(process, "74 4C 48 8B 07 4C");
	}

	DWORD64 GetCamera()
	{
		if (Helper::ValidPTR(Camera))
			return *(DWORD64*)(Camera + 0x0);
	}

	DWORD64 GetReplayInterface()
	{
		if (Helper::ValidPTR(ReplayInterface))
			return *(DWORD64*)(ReplayInterface + 0x0);
	}

	namespace Check
	{
		bool isPlayerValid()
		{
			if (Helper::ValidPTR(World))
			{
				LocalPlayer = *(DWORD64*)(World + 0x8);
				if (LocalPlayer != NULL)
					return true;
			}
			return false;
		}

		bool isPlayerInfoValid()
		{
			if (Helper::ValidPTR(LocalPlayer))
			{
				LocalPlayerInfo = *(DWORD64*)(LocalPlayer + 0x10C8);
				if (LocalPlayerInfo != NULL)
					return true;
			}
			return false;
		}

		bool isPlayerVehicleValid()
		{
			if (Helper::ValidPTR(LocalPlayer))
			{
				uintptr_t curveh = *(DWORD64*)(LocalPlayer + 0x0D30);
				if (curveh != NULL)
					return true;
			}
			return false;
		}

		int32_t isPlayerInVehicle()
		{
			int32_t state = *(int32_t*)(LocalPlayer + 0xE50);
			if (state != 0)
				return true;
			else
				return false;
		}

		bool IsInsideFirstPerson() {
			return *reinterpret_cast<BYTE*>((char*)LocalPlayer + 0x642) ? true : false;
		}
	}
}