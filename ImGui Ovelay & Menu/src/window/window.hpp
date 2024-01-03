#pragma once
#include <d3d11.h>

class Overlay {
public:
	// functions for the d3d11 device
	static bool CreateDevice();
	static void DestroyDevice();

	// functions for the window
	static void CreateOverlay();
	static void DestroyOverlay();

	// functions for ImGui
	static bool CreateImGui();
	static void DestroyImGui();

	// for use inside of your main loop to render.
	static void StartRender();
	static void EndRender();

	// i'm using this for the menu specifically, but you could render ESP and shit like that in here if you wanted to.
	// as long as you're calling ImGui::GetBackgroundDrawList() between Start and End render you're fine to do what you want :)
	static void Render();

	// winapi window requirements
	static HWND overlay;
	static WNDCLASSEX wc;

	// small helper functions for the SetForeground function
	static bool IsWindowInForeground(HWND window) { return GetForegroundWindow() == window; }
	static bool BringToForeground(HWND window) { return SetForegroundWindow(window); }

	// sets the window to the foreground
	static void SetForeground(HWND window);

	static ID3D11Device* device;
	static ID3D11DeviceContext* device_context;
	static IDXGISwapChain* swap_chain;
	static ID3D11RenderTargetView* render_targetview;

	// if we should render menu on top of the overlay.
	inline static bool RenderMenu;

	// if we should run the overlay at all
	inline static bool shouldRun;
};

inline Overlay overlay;