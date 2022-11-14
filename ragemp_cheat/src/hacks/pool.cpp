#include "pool.h"

namespace Pool
{
	Players players[255];
	Vehicles vehicles[255];

	void TickPlayer()
	{
		DWORD64 list_interface = NULL;
		DWORD64 list = NULL;
		int list_max_ptr = 0;

		__try
		{
			DWORD64 replayInterface = Memory::GetReplayInterface();
			if (Helper::ValidPTR(replayInterface))
			{
				list_interface = *(DWORD64*)(replayInterface + 0x18);
				list = *(DWORD64*)(list_interface + 0x100);
				list_max_ptr = *(int*)(list_interface + 0x108);
			}
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}

		for (int i = 0; i < 255; i++)
		{
			players[i].ped = NULL;
			players[i].position.x = 0.0f;

			if (i < list_max_ptr)
			{
				__try
				{
					DWORD64 ped = *(DWORD64*)(list + i * 0x10);
					if (Helper::ValidPTR(ped))
					{
						players[i].ped = ped;
						Vector3 pedPos = *(Vector3*)(ped + 0x90);
						players[i].position = Vector3(pedPos);
					}
				}
				__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
			}
		}
	}

	void TickVehicle()
	{
		DWORD64 list_interface = NULL;
		DWORD64 list = NULL;
		int list_max_ptr = 0;

		__try
		{
			DWORD64 replayInterface = Memory::GetReplayInterface();
			if (Helper::ValidPTR(replayInterface))
			{
				list_interface = *(DWORD64*)(replayInterface + 0x10);
				list = *(DWORD64*)(list_interface + 0x180);
				list_max_ptr = *(int*)(list_interface + 0x188);
			}
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}

		for (int i = 0; i < 255; i++)
		{
			vehicles[i].veh = NULL;
			vehicles[i].position.x = 0.0f;

			if (i < list_max_ptr)
			{
				__try
				{
					DWORD64 veh = *(DWORD64*)(list + i * 0x10);
					if (Helper::ValidPTR(veh))
					{
						vehicles[i].veh = veh;
						Vector3 vehPos = *(Vector3*)(veh + 0x90);
						vehicles[i].position = Vector3(vehPos);
					}
				}
				__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
			}
		}
	}
}