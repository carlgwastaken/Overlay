#pragma once
#include <d3d11.h>
#include <dxgi.h>

#include "../../ext/ImGui 1.90/imgui.h"
#include "../../ext/ImGui 1.90/imgui_impl_dx11.h"
#include "../../ext/ImGui 1.90/imgui_impl_win32.h"

class Overlay {
private:
	// creation of device, window, and ImGui.
	bool CreateDevice();
	void CreateOverlay(const char* window_name);
	bool CreateImGui();

	// destruction of device, window and ImGui.
	void DestroyDevice();
	void DestroyOverlay();
	void DestroyImGui();

	// returns 60.f if it fails.
	float GetRefreshRate();
public:
	void SetupOverlay(const char* window_name) {
		CreateOverlay(window_name);
		CreateDevice();
		CreateImGui();
	}

	// deconstructor called when program is exiting. THIS IS CALLED AUTOMATICALLY, NO NEED TO CALL IT YOURSELF!
	~Overlay() {
		DestroyDevice();
		DestroyOverlay();
		DestroyImGui();
	}

	// if we should render menu on top of the overlay.
	bool RenderMenu;

	// if we should run the overlay at all
	bool shouldRun = true;

	// for use inside of your main loop to render.
	void StartRender();
	void EndRender();

	// i'm using this for the menu specifically, but you could render ESP and shit like that in here if you wanted to.
	// as long as you're calling ImGui::GetBackgroundDrawList() between Start and End render you're fine to do what you want :)
	
	// NOTE: if the user presses the x in the titlebar, the styles will not be set correctly. This can be fixed by checking the renderMenu bool every frame.
	// (which is really bad for performance)
	void Render();

	// small helper functions for the SetForeground function
	bool IsWindowInForeground(HWND window) { return GetForegroundWindow() == window; }
	bool BringToForeground(HWND window) { return SetForegroundWindow(window); }

	// sets the window to the foreground
	void SetForeground(HWND window);
private:
	// winapi window requirements
	HWND overlay;
	WNDCLASSEX wc;

	ID3D11Device* device;
	ID3D11DeviceContext* device_context;
	IDXGISwapChain* swap_chain;
	ID3D11RenderTargetView* render_targetview;
};