#include "../window/window.hpp"

#include <thread>

int main()
{
	// thread your cheat here 


	// hide console window since we're making our own window, or use WinMain() instead.
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	overlay.shouldRun = true;
	overlay.RenderMenu = false;

	overlay.CreateOverlay();
	overlay.CreateDevice();
	overlay.CreateImGui();

	printf("[>>] Hit insert to show the menu in this overlay!\n");

	overlay.SetForeground(GetConsoleWindow());

	while (overlay.shouldRun)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		overlay.StartRender();
		
		if (overlay.RenderMenu) {
			overlay.Render();
		}
		else
			ImGui::GetBackgroundDrawList()->AddText({ 1000, 540 }, ImColor(0.0f, 1.0f, 0.0f), "Overlay Rendering!");

		// if you want to render here, you could move the imgui includes to your .hpp file instead of the .cpp file!
		overlay.EndRender();
	}

	overlay.DestroyImGui();
	overlay.DestroyDevice();
	overlay.DestroyOverlay();
}