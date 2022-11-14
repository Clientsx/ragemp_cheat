#pragma once
#include "../../includes.h"

namespace Aimbot
{
	extern float screen_distance(float Xx, float Yy, float xX, float yY);
	extern float get_distance(Vector3 to, Vector3 from);
	extern void getBestTarget();
	extern void Tick();
}