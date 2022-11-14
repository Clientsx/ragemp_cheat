#pragma once
#include <Windows.h>
#include <stdio.h> 
#include <string> 
#include <sstream> 
#include <iostream>
#include "../../includes.h"

#define IsValidPtr(x) (x && !IsBadReadPtr(&x, sizeof(void*) && x != nullptr && x > nullptr))

enum Bones {
	HEAD = 0x796E,
	NECK = 0x9995,
	RIGHT_HAND = 0xDEAD,
	RIGHT_FOREARM = 0x6E5C,
	RIGHT_UPPER_ARM = 0x9D4D,
	RIGHT_CLAVICLE = 0x29D2,

	LEFT_HAND = 0x49D9,
	LEFT_FOREARM = 0xEEEB,
	LEFT_UPPER_ARM = 0xB1C5,
	LEFT_CLAVICLE = 0xFCD9,

	PELVIS = 0x2E28,
	SPINE_ROOT = 0xE0FD,
	SPINE0 = 0x60F2,
	SPINE1 = 0x60F0,
	SPINE2 = 0x60F1,
	SPINE3 = 0x60F2,

	RIGHT_TOE = 0x512D,
	RIGHT_FOOT = 0xCC4D,
	RIGHT_CALF = 0x9000,
	RIGHT_THIGH = 0xCA72,
	LEFT_TOE = 0x083C,
	LEFT_FOOT = 0x3779,
	LEFT_CALF = 0xF9BB,
	LEFT_THIGH = 0xE39F
};

enum class eGameState : int32_t
{
	Invalid = -1,
	Playing,
	Died,
	Arrested,
	FailedMission,
	LeftGame,
	Respawn,
	InMPCutscene
};

enum class eDamageType : int32_t
{
	Unknown,
	None,
	Melee,
	Bullet,
	BulletRubber,
	Explosive,
	Fire,
	Collision,
	Fall,
	Drown,
	Electric,
	BarbedWire,
	FireExtinguisher,
	Smoke,
	WaterCannon,
	Tranquilizer
};

enum class eFireType : int32_t
{
	None,
	Melee,
	InstantHit,
	DelayedHit,
	ProjectTile,
	VolumetricParticle
};

enum class eWeaponWheelSlot : int32_t
{
	Pistol,
	SMG,
	Rifle,
	Sniper,
	UnarmedMelee,
	ShotGun,
	Heavy,
	ThrowableSpecial
};

enum class eAmmoSpecialType : int32_t
{
	None,
	ArmorPiercing,
	Explosive,
	FMJ,
	HollowPoint,
	Incendiary,
	Tracer
};

enum class eAmmoFlags : uint32_t
{
	InfiniteAmmo = 0,
	AddSmokeOnExplosion = 1,
	Fuse = 2,
	FixedAfterExplosion = 3,
};

enum class eVehicleType : std::uint32_t
{
	VEHICLE_TYPE_NONE = 4294967295,
	VEHICLE_TYPE_CAR = 0,
	VEHICLE_TYPE_PLANE = 1,
	VEHICLE_TYPE_TRAILER = 2,
	VEHICLE_TYPE_QUADBIKE = 3,
	VEHICLE_TYPE_DRAFT = 4,
	VEHICLE_TYPE_SUBMARINECAR = 5,
	VEHICLE_TYPE_AMPHIBIOUS_AUTOMOBILE = 6,
	VEHICLE_TYPE_AMPHIBIOUS_QUADBIKE = 7,
	VEHICLE_TYPE_HELI = 8,
	VEHICLE_TYPE_BLIMP = 9,
	VEHICLE_TYPE_AUTOGYRO = 10,
	VEHICLE_TYPE_BIKE = 11,
	VEHICLE_TYPE_BICYCLE = 12,
	VEHICLE_TYPE_BOAT = 13,
	VEHICLE_TYPE_TRAIN = 14,
	VEHICLE_TYPE_SUBMARINE = 15,
};

enum class eVehicleClass : std::uint8_t
{
	VC_COMPACT = 0,
	VC_SEDAN = 1,
	VC_SUV = 2,
	VC_COUPE = 3,
	VC_MUSCLE = 4,
	VC_SPORT_CLASSIC = 5,
	VC_SPORT = 6,
	VC_SUPER = 7,
	VC_MOTORCYCLE = 8,
	VC_OFF_ROAD = 9,
	VC_INDUSTRIAL = 10,
	VC_UTILITY = 11,
	VC_VAN = 12,
	VC_CYCLE = 13,
	VC_BOAT = 14,
	VC_HELICOPTER = 15,
	VC_PLANE = 16,
	VC_SERVICE = 17,
	VC_EMERGENCY = 18,
	VC_MILITARY = 19,
	VC_COMMERCIAL = 20,
	VC_RAIL = 21,
	VC_OPEN_WHEEL = 22,
};

enum IntersectOptions {
	IntersectEverything = -1,
	IntersectMap = 1,
	IntersectMissionEntityAndTrain = 2,
	IntersectPeds1 = 4,
	IntersectPeds2 = 8,
	IntersectVehicles = 10,
	IntersectObjects = 16,
	IntersectVegetation = 256
};