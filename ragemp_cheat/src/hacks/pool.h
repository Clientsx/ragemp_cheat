#pragma once
#include "../../includes.h"

namespace Pool
{
#ifndef _MAIN_H_
#define _MAIN_H_

	struct Players
	{
		DWORD64 ped;
		Vector3 position;
	};

	struct Vehicles
	{
		DWORD64 veh;
		Vector3 position;
	};

#endif//_MAIN_H_

	extern Players players[255];
	extern Vehicles vehicles[255];

	extern void TickPlayer();
	extern void TickVehicle();
}