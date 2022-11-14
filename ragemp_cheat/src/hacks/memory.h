#pragma once
#include "../../includes.h"

namespace Memory
{
	extern DWORD LocalPlayerHandle;
	extern DWORD64 BASE;

	extern ImVec2 WorldToScreen(Vector3 WorldPos);
	extern ImVec2 WorldToScreen2(D3DXVECTOR3 WorldPos);
	extern ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask);
	extern Vector3 GetBonePosVec3(const int64_t cPed, const int32_t wMask);
	extern PVector3 ToPVector3(Vector3 pVec);
	extern Vector3 ToVector3(PVector3 pVec);

	extern DWORD64 World;
	extern DWORD64 LocalPlayer;
	extern DWORD64 LocalPlayerInfo;
	extern DWORD64 Camera;
	extern DWORD64 ReplayInterface;
	extern DWORD64 WeaponBase;
	extern DWORD64 BonePositionAddress;
	extern DWORD64 BlipPointer;
	extern DWORD64 FlyPatt;

	extern void initGame();
	extern DWORD64 GetCamera();
	extern DWORD64 GetReplayInterface();

	namespace Check
	{
		extern bool isPlayerValid();
		extern bool isPlayerInfoValid();
		extern bool isPlayerVehicleValid();
		extern int32_t isPlayerInVehicle();
		extern bool IsInsideFirstPerson();
	}
}