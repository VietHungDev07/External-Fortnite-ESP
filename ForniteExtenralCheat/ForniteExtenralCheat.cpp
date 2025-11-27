#include <iostream>
#include <windows.h>
#include <dwmapi.h>
#include <d3d9.h>
#include "Driver/Driver.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include <SDK/SDK.h>
#pragma comment(lib,"d3d9.lib")
using namespace std;

bool menuShow = true;
HWND _HWND = NULL;
int ScreenHeight = NULL;
int ScreenWidth = NULL;
int ScreenLeft = NULL;
int ScreenRight = NULL;
int ScreenTop = NULL;
int ScreenBottom = NULL;
namespace Setting
{
	bool ESP = false;
	bool Box = false;
	bool line = false;
	bool Skeleton = false;
	bool Distance = false;

}

namespace OverlayWindow
{
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCWSTR Name;
}

namespace DirectX9Interface
{
	IDirect3D9Ex* Direct3D9 = NULL;
	IDirect3DDevice9Ex* pDevice = NULL;
	D3DPRESENT_PARAMETERS pParams = { NULL };
	MARGINS Margin = { -1 };
	MSG Message = { NULL };
}

void InputHandler() {
	for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;
	int button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) button = 0;
	if (button != -1) ImGui::GetIO().MouseDown[button] = true;
}
void DrawEntity()
{
	if (Setting::ESP)
	{
		for (int i = 0; i < Aactor::GetPlayerArraySize(); i++)
		{
			auto AactorAddress = Aactor::GetActorAddress(i);
			if (AactorAddress == UPlayer::GetLocalPlayer()) 
				continue;



			if (Setting::Box || Setting::Skeleton || Setting::line || Setting::Distance)
			{
				uintptr_t mesh = Bone::GetMesh(AactorAddress);

				FVector2D Bone1 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 66)); 
				FVector2D Bone14 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 75));
				FVector2D Bone15 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 82));

				if (Setting::Box)
				{
					float HeadX = Bone1.x;
					float HeadY = Bone1.y;

				
					float FeetY = max(Bone14.y, Bone15.y);

			
					float Height = FeetY - HeadY;

		
					float Width = Height * 0.4f;

					float Left = HeadX - Width / 2;
					float Right = HeadX + Width / 2;

					ImGui::GetBackgroundDrawList()->AddRect(
						ImVec2(Left, HeadY),
						ImVec2(Right, FeetY),
						ImColor(255, 255, 0),   
						1.0f
					);
				}

			
				if (Setting::line)
				{
					FVector2D L1 = Camera::ProjectWorldToScreen(Aactor::GetActorLocation(AactorAddress)); 
					FVector2D L2 = Camera::ProjectWorldToScreen(Aactor::GetActorLocation(UPlayer::GetLocalPlayer())); 

					ImGui::GetBackgroundDrawList()->AddLine(
						ImVec2(L2.x, L2.y),
						ImVec2(L1.x, L1.y),
						ImColor(0, 0, 0),   
						1.8f
					);
				}



				if (Setting::Distance)
				{
					float Distance = Aactor::GetActorLocation(AactorAddress)
						.Distance(Aactor::GetActorLocation(UPlayer::GetLocalPlayer())) / 100.0f;

					char text[32];
					sprintf(text, "%.1f m", Distance);

					ImGui::GetBackgroundDrawList()->AddText(
						ImVec2(Bone1.x + 5, Bone1.y - 15),
						ImColor(255, 255, 255),
						text
					);
				}

		
				if (Setting::Skeleton)
				{
					FVector2D Bone2 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 9));
					FVector2D Bone3 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 38));
					FVector2D Bone4 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 10));
					FVector2D Bone5 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 39));
					FVector2D Bone6 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 62));
					FVector2D Bone7 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 33));
					FVector2D Bone8 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 7));
					FVector2D Bone9 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 3));
					FVector2D Bone10 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 71));
					FVector2D Bone11 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 78));
					FVector2D Bone12 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 79));
					FVector2D Bone13 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 72));

					auto draw = ImGui::GetBackgroundDrawList();

					draw->AddLine(ImVec2(Bone1.x, Bone1.y), ImVec2(Bone2.x, Bone2.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone1.x, Bone1.y), ImVec2(Bone3.x, Bone3.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone2.x, Bone2.y), ImVec2(Bone4.x, Bone4.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone3.x, Bone3.y), ImVec2(Bone5.x, Bone5.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone5.x, Bone5.y), ImVec2(Bone6.x, Bone6.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone4.x, Bone4.y), ImVec2(Bone7.x, Bone7.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone1.x, Bone1.y), ImVec2(Bone8.x, Bone8.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone8.x, Bone8.y), ImVec2(Bone9.x, Bone9.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone9.x, Bone9.y), ImVec2(Bone10.x, Bone10.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone9.x, Bone9.y), ImVec2(Bone11.x, Bone11.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone10.x, Bone10.y), ImVec2(Bone13.x, Bone13.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone11.x, Bone11.y), ImVec2(Bone12.x, Bone12.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone13.x, Bone13.y), ImVec2(Bone14.x, Bone14.y), ImColor(255, 255, 255), 1.0f);
					draw->AddLine(ImVec2(Bone12.x, Bone12.y), ImVec2(Bone15.x, Bone15.y), ImColor(255, 255, 255), 1.0f);
				}
			}
		}
	}
}

void Render()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		menuShow = !menuShow;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

//	ImGui::GetIO().MouseDrawCursor = menuShow;
	DrawEntity();
	if (menuShow)
	{
		ImGui::SetNextWindowSize(ImVec2(350, 350));
		ImGui::Begin("The Blade Dancerr", nullptr, ImGuiWindowFlags_NoCollapse);

		ImGui::Text("Visual Settings");
		ImGui::Separator();

		ImGui::Checkbox("ESP", &Setting::ESP);
		ImGui::Checkbox("Box", &Setting::Box);
		ImGui::Checkbox("Line", &Setting::line);
		ImGui::Checkbox("Skeleton", &Setting::Skeleton);
		ImGui::Spacing();
		ImGui::Separator();

		ImGui::End();
	}

	ImGui::EndFrame();

	DirectX9Interface::pDevice->SetRenderState(D3DRS_ZENABLE, false);
	DirectX9Interface::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DirectX9Interface::pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

	DirectX9Interface::pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (DirectX9Interface::pDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		DirectX9Interface::pDevice->EndScene();
	}

	HRESULT result = DirectX9Interface::pDevice->Present(NULL, NULL, NULL, NULL);
	if (result == D3DERR_DEVICELOST && DirectX9Interface::pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}


void MainLoop() {
	static RECT OldRect;
	ZeroMemory(&DirectX9Interface::Message, sizeof(MSG));

	while (DirectX9Interface::Message.message != WM_QUIT) {
		if (PeekMessage(&DirectX9Interface::Message, OverlayWindow::Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&DirectX9Interface::Message);
			DispatchMessage(&DirectX9Interface::Message);
		}
		HWND ForegroundWindow = GetForegroundWindow();
		if (ForegroundWindow == _HWND) {
			HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
			SetWindowPos(OverlayWindow::Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT TempRect;
		POINT TempPoint;
		ZeroMemory(&TempRect, sizeof(RECT));
		ZeroMemory(&TempPoint, sizeof(POINT));

		GetClientRect(_HWND, &TempRect);
		ClientToScreen(_HWND, &TempPoint);

		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = _HWND;

		POINT TempPoint2;
		GetCursorPos(&TempPoint2);
		io.MousePos.x = TempPoint2.x - TempPoint.x;
		io.MousePos.y = TempPoint2.y - TempPoint.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else {
			io.MouseDown[0] = false;
		}

		if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom) {
			OldRect = TempRect;
			ScreenWidth = TempRect.right;
			ScreenHeight = TempRect.bottom;
			DirectX9Interface::pParams.BackBufferWidth = ScreenWidth;
			DirectX9Interface::pParams.BackBufferHeight = ScreenHeight;
			SetWindowPos(OverlayWindow::Hwnd, (HWND)0, TempPoint.x, TempPoint.y, ScreenWidth, ScreenHeight, SWP_NOREDRAW);
			DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
		}
		Render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (DirectX9Interface::pDevice != NULL) {
		DirectX9Interface::pDevice->EndScene();
		DirectX9Interface::pDevice->Release();
	}
	if (DirectX9Interface::Direct3D9 != NULL) {
		DirectX9Interface::Direct3D9->Release();
	}
	DestroyWindow(OverlayWindow::Hwnd);
	UnregisterClass(OverlayWindow::WindowClass.lpszClassName, OverlayWindow::WindowClass.hInstance);
}

bool DirectXInit() {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9Interface::Direct3D9))) {
		return false;
	}

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = OverlayWindow::Hwnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = ScreenWidth;
	Params.BackBufferHeight =ScreenHeight;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	if (FAILED(DirectX9Interface::Direct3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, OverlayWindow::Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9Interface::pDevice))) {
		DirectX9Interface::Direct3D9->Release();
		return false;
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 18.0f);
	auto& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 10.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 12.0f; // Make all elements (checkboxes, etc) circles
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 20.0f; // Make grab a circle
	style.GrabRounding = 12.0f;
	style.PopupRounding = 7.f;
	style.Alpha = 1.0;

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.95f, 0.95f, 0.95f, 0.30f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.66f, 0.66f, 0.66f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(1.000f, 0.777f, 0.578f, 0.780f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.987f, 0.611f, 0.600f);
	colors[ImGuiCol_Button] = ImVec4(1.00f, 0.77f, 0.00f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.84f, 0.97f, 0.01f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(1.00f, 0.54f, 0.01f, 0.71f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.96f, 0.73f, 0.09f, 0.90f);
	colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.97f, 0.00f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.80f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	
	ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplWin32_Init(OverlayWindow::Hwnd);
	ImGui_ImplDX9_Init(DirectX9Interface::pDevice);
	DirectX9Interface::Direct3D9->Release();
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message) {
	case WM_DESTROY:
		if (DirectX9Interface::pDevice != NULL) {
			DirectX9Interface::pDevice->EndScene();
			DirectX9Interface::pDevice->Release();
		}
		if (DirectX9Interface::Direct3D9 != NULL) {
			DirectX9Interface::Direct3D9->Release();
		}
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (DirectX9Interface::pDevice != NULL && wParam != SIZE_MINIMIZED) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			DirectX9Interface::pParams.BackBufferWidth = LOWORD(lParam);
			DirectX9Interface::pParams.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void SetupWindow() {
	OverlayWindow::WindowClass = {
		sizeof(WNDCLASSEX), 0, WinProc, 0, 0, nullptr, LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr, OverlayWindow::Name, LoadIcon(nullptr, IDI_APPLICATION)
	};

	RegisterClassEx(&OverlayWindow::WindowClass);
	if (_HWND) {
		static RECT TempRect = { NULL };
		static POINT TempPoint;
		GetClientRect(_HWND, &TempRect);
		ClientToScreen(_HWND, &TempPoint);
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ScreenWidth = TempRect.right;
		ScreenHeight = TempRect.bottom;
	}

	OverlayWindow::Hwnd = CreateWindowEx(NULL, OverlayWindow::Name, OverlayWindow::Name, WS_POPUP | WS_VISIBLE, ScreenLeft, ScreenTop, ScreenWidth, ScreenHeight, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(OverlayWindow::Hwnd, &DirectX9Interface::Margin);
	SetWindowLong(OverlayWindow::Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	ShowWindow(OverlayWindow::Hwnd, SW_SHOW);
	UpdateWindow(OverlayWindow::Hwnd);
}

int main()
{
	cout << R"(
  ________   _________ ______ _____  _   _          _      
 |  ____\ \ / /__   __|  ____|  __ \| \ | |   /\   | |     
 | |__   \ V /   | |  | |__  | |__) |  \| |  /  \  | |     
 |  __|   > <    | |  |  __| |  _  /| . ` | / /\ \ | |     
 | |____ / . \   | |  | |____| | \ \| |\  |/ ____ \| |____ 
 |______/_/ \_\  |_|  |______|_|  \_\_| \_/_/    \_\______|
                                           
)";

	cout << "Checking Driver..." << endl;
	if (!Driver::Init())
	{
		cout << "Please Map Driver Manully Before Run Game & Cheat" << endl;
		Sleep(3000);
		return 0;
	}
	cout << "Driver Connected Done." << endl;
	Sleep(1000);
	cout << "Please Start Game" << endl;

	_HWND = FindWindow(NULL, L"Fortnite  ");
	
	bool WindowFocus = false;
	while (WindowFocus == false)
	{
	
		HWND hwnd_active = GetForegroundWindow();

		if (_HWND == hwnd_active) {
			_HWND = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(_HWND, &TempRect);
			ScreenWidth = TempRect.right - TempRect.left;
			ScreenHeight = TempRect.bottom - TempRect.top;
			ScreenLeft = TempRect.left;
			ScreenRight = TempRect.right;
			ScreenTop = TempRect.top;
			ScreenBottom = TempRect.bottom;

			WindowFocus = true;
		}
	}
	GetWindowThreadProcessId(_HWND, (LPDWORD)&Driver::ProcessID); // Cast INT32 to LPDWORD
	std::cout << "Found Game Running in PID: " << hex << Driver::ProcessID << std::endl;
	BaseAddress = Driver::GetBase();
	std::cout << "Found BaseAddress Game: " << hex << BaseAddress << std::endl;
	Driver::CR3();
	OverlayWindow::Name = L" ";
	SetupWindow();
	DirectXInit();


	while (TRUE)
	{
		MainLoop();
	}
}
