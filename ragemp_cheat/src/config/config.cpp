#pragma once
#include "./config.h"

namespace Config
{
	bool isMenuVisible = false;
	int Current_Tab = 0;

	int OpenMenuKey = 23;
	bool God_Mode = false;
	bool NoGravity = false;
	bool Invisible = false;
	bool NoRagdoll = false;
	bool Seatbelt = false;
	bool Crosshair = false;
	bool Wanted = false;
	bool VehicleEsp = false;
	bool VehicleEsp_Name = false;
	bool VehicleEsp_Distance = false;
	bool VehicleEsp_3Dbox = false;
	bool ObjectESP = false;

	int Max_Aimbot_Distance = 250;
	bool Aimbot_Toggle = false;
	int Aimbot_Type = 0;
	int Aimbot_Smooth = 0;
	bool Aimbot_HorizontalOnly = false;
	int Aimbot_Fov = 60;
	float Aimbot_Prediction = 0.05f;
	bool DrawFov = false;
	int Aimbot_Bone = 2;
	bool Aimbot_VisibleCheck = false;

	bool No_Recoil = false;
	bool No_Spread = false;
	bool Fast_Reload = false;
	bool Super_Velocity = false;
	bool Super_Dmg = false;
	bool Sniper_Range = false;
	bool Rapide_Fire = false;
	bool Bullet_Type = false;
	int WeaponSpawn = 0;
	int WeaponSpawnAmmo = 0;

	bool Veh_God_Mode = false;
	bool Veh_Impulse = false;
	bool UseLockedCars = false;
	bool StartEngineCars = false;
	bool DrawLastVeh = false;

	bool Npc_Esp = false;
	bool Npc_IncludeSelf_Esp = false;
	bool Npc_IncludeNpc_Esp = false;
	int Npc_Max_Distance = 0;
	bool Npc_Name_Esp = false;
	bool Npc_Box_Esp = false;
	int Npc_Box_Esp_Type = 0;
	bool Npc_Health_Esp = false;
	bool Npc_Weapon_Esp = false;
	bool Npc_Distance_Esp = false;
	bool Npc_Barrel_Esp = false;
	bool Npc_Snapline_Esp = false;
	bool Npc_Bone_Esp = false;
	bool Npc_Full_Bone_Esp = false;
	bool Npc_HeadDot_Esp = false;
	float Npc_HeadDot_Size = 1.25f;

	bool Toggle_2D_Radar = false;

	bool UseRayCast = false;
	bool NoClip = false;
	float NoClipSpeed = 1.025f;
	bool FlyHack = false;
	float FlySpeed = 1.025f;

	int HotKeyAim = 2;
	int HotKeyAim2 = 2;
	int HotKeyFly = 0;
	int HotKeyNoClip = 0;
	int HotKeyTeleportToWayP = 0;
	int HotKeyResetHealth = 0;
	int HotKeyResetArmour = 0;
	int HotKeyFlipVeh = 0;
	int HotKeyVehImpulseIncreace = 0;
	int HotKeyVehImpulseDecrease = 0;
	int HotKeyVehImpulseConstant = 0;
}