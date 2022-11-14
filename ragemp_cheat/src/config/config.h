#pragma once
#include "../../includes.h"

namespace Config
{
	extern bool isMenuVisible;
	extern int Current_Tab;

	extern int OpenMenuKey;
	extern bool God_Mode;
	extern bool NoGravity;
	extern bool Invisible;
	extern bool NoRagdoll;
	extern bool Seatbelt;
	extern bool Crosshair;
	extern bool Wanted;
	extern bool VehicleEsp;
	extern bool VehicleEsp_Name;
	extern bool VehicleEsp_Distance;
	extern bool VehicleEsp_3Dbox;
	extern bool ObjectESP;

	extern int Max_Aimbot_Distance;
	extern bool Aimbot_Toggle;
	extern int Aimbot_Type;
	extern int Aimbot_Smooth;
	extern bool Aimbot_HorizontalOnly;
	extern int Aimbot_Fov;
	extern float Aimbot_Prediction;
	extern bool DrawFov;
	extern int Aimbot_Bone;
	extern bool Aimbot_VisibleCheck;

	extern bool No_Recoil;
	extern bool No_Spread;
	extern bool Fast_Reload;
	extern bool Super_Velocity;
	extern bool Super_Dmg;
	extern bool Sniper_Range;
	extern bool Rapide_Fire;
	extern bool Bullet_Type;
	extern int WeaponSpawn;
	extern int WeaponSpawnAmmo;

	extern bool Veh_God_Mode;
	extern bool Veh_Impulse;
	extern bool UseLockedCars;
	extern bool StartEngineCars;
	extern bool DrawLastVeh;

	extern bool Npc_Esp;
	extern bool Npc_IncludeSelf_Esp;
	extern bool Npc_IncludeNpc_Esp;
	extern int Npc_Max_Distance;
	extern bool Npc_Name_Esp;
	extern bool Npc_Box_Esp;
	extern int Npc_Box_Esp_Type;
	extern bool Npc_Health_Esp;
	extern bool Npc_Weapon_Esp;
	extern bool Npc_Distance_Esp;
	extern bool Npc_Barrel_Esp;
	extern bool Npc_Snapline_Esp;
	extern bool Npc_Bone_Esp;
	extern bool Npc_Full_Bone_Esp;
	extern bool Npc_HeadDot_Esp;
	extern float Npc_HeadDot_Size;

	extern bool Toggle_2D_Radar;

	extern bool UseRayCast;
	extern bool NoClip;
	extern float NoClipSpeed;
	extern bool FlyHack;
	extern float FlySpeed;

	extern int HotKeyAim;
	extern int HotKeyAim2;
	extern int HotKeyFly;
	extern int HotKeyNoClip;
	extern int HotKeyTeleportToWayP;
	extern int HotKeyResetHealth;
	extern int HotKeyResetArmour;
	extern int HotKeyFlipVeh;
	extern int HotKeyVehImpulseIncreace;
	extern int HotKeyVehImpulseDecrease;
	extern int HotKeyVehImpulseConstant;
}