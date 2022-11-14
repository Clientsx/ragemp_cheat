#pragma once
#include <Windows.h>
#include <vector>
#include <dxgi.h>
#include <d3d11.h>
#include <emmintrin.h>
#include "SteamOverlay.hpp"
#include <emmintrin.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")
#include <D3dx9math.h>

#include "./src/gui/gui.h"
#include "./src/elements/elements.h"
#include "./src/config/config.h"
#include "./src/gta/Game.h"
#include "./src/gta/Math.h"
#include "./src/hacks/pool.h"
#include "./src/hacks/memory.h"
#include "./src/hacks/aimbot.h"
#include "./src/hacks/visuals.h"
#include "./src/helper/helper.h"


typedef unsigned long ulong_t;
typedef HRESULT(*Present)(IDXGISwapChain*, UINT, UINT);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);