#include "includes.h"
HWND hWnd = NULL;
Present oPresent = NULL;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* pRenderTargetView;
WNDPROC oWndProc;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool ImGuiInit = false;

int getFPS()
{
	return ImGui::GetIO().Framerate;
};

HRESULT hkPresent(IDXGISwapChain* pSwapchain, UINT SyncInterval, UINT Flags) {
	if (!ImGuiInit) {
		if (SUCCEEDED(pSwapchain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapchain->GetDesc(&sd);
			hWnd = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

			Elements::title_font = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arial.ttf", 14);
			Elements::esp_font = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arial.ttf", 14);
			Elements::middle_font = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arial.ttf", 14);
			Elements::bottom_font = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arial.ttf", 14);

			ImGui_ImplWin32_Init(hWnd);
			ImGui_ImplDX11_Init(pDevice, pContext);
			ImGuiInit = true;

			while (Memory::BASE == NULL)
				Memory::BASE = reinterpret_cast<DWORD64>(GetModuleHandleA(NULL));

			Memory::initGame();
		}
		else return oPresent(pSwapchain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::GetIO().WantCaptureMouse = Config::isMenuVisible;
	ImGui::GetIO().WantCaptureKeyboard = Config::isMenuVisible;
	ImGui::GetIO().WantTextInput = Config::isMenuVisible;
	ImGui::GetIO().MouseDrawCursor = Config::isMenuVisible;

	if (GetAsyncKeyState(VK_END) & 1)
	{
		Config::isMenuVisible = !Config::isMenuVisible;
	}

	if (Config::isMenuVisible)
	{
		ImGui::SetNextWindowSize(ImVec2{ 670 ,540 });
		ImGui::Begin("cmrnl - shit", NULL, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus);
		{
			Gui::DrawMenu();
		}
		ImGui::End();
	}

	Pool::TickPlayer();
	Pool::TickVehicle();
	Aimbot::Tick();
	Visuals::Tick();

	ImGui::Render();
	pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapchain, SyncInterval, Flags);
}

void STDMETHODCALLTYPE MainThread() 
{
	uintptr_t pPresentAddr = SteamOverlay::FindPattern(SteamOverlay::GetSteamModule(), "48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8");
	SteamOverlay::CreateHook(pPresentAddr, (uintptr_t)hkPresent, (long long*)&oPresent);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) 
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		MainThread();
	}
	return TRUE;
}
