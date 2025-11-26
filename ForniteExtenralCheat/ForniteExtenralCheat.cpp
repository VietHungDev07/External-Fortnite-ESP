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
namespace DATA
{
	//World:
	 uintptr_t Uworld;


	//LocalPlayer
	 uintptr_t OwningGameInstance;
	 uintptr_t LocalPlayers;
	 uintptr_t PlayerController;
	 uintptr_t AcknowledgedPawn;

	//Aactor:
	 uintptr_t GameState;
	 uintptr_t PlayerArray;
	 uintptr_t PawnPrivate;

	//Camera;
	 uintptr_t PlayerCameraManager;
	 FMinimalViewInfo CameraCachePrivate;

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

	int size = Aactor::GetPlayerArraySize();


	for (int i = 0; i < size; i++)
	{

		auto AactorAddress = Aactor::GetActorAddress(i);
		uintptr_t mesh = Bone::GetMesh(AactorAddress);

		FVector2D Bone1 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 66));
		FVector2D Bone2 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 9));
		FVector2D Bone3 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 38));
		FVector2D Bone4 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 10));
		FVector2D Bone5 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 39));
		FVector2D Bone6 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 62));
		FVector2D Bone7 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 33));
		FVector2D Bone8 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 7));
		FVector2D Bone9 =  Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 3));
		FVector2D Bone10 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 71));
		FVector2D Bone11 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 78));
		FVector2D Bone12 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 79));
		FVector2D Bone13 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 72));
		FVector2D Bone14 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 75));
		FVector2D Bone15 = Camera::ProjectWorldToScreen(Bone::GetBoneWithRotation(mesh, 82));
		
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone1.x, Bone1.y), ImVec2(Bone2.x, Bone2.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone1.x, Bone1.y), ImVec2(Bone3.x, Bone3.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone2.x, Bone2.y), ImVec2(Bone4.x, Bone4.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone3.x, Bone3.y), ImVec2(Bone5.x, Bone5.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone5.x, Bone5.y), ImVec2(Bone6.x, Bone6.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone4.x, Bone4.y), ImVec2(Bone7.x, Bone7.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone1.x, Bone1.y), ImVec2(Bone8.x, Bone8.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone8.x, Bone8.y), ImVec2(Bone9.x, Bone9.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone9.x, Bone9.y), ImVec2(Bone10.x, Bone10.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone9.x, Bone9.y), ImVec2(Bone11.x, Bone11.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone10.x, Bone10.y), ImVec2(Bone13.x, Bone13.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone11.x, Bone11.y), ImVec2(Bone12.x, Bone12.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone13.x, Bone13.y), ImVec2(Bone14.x, Bone14.y), ImColor(255, 255, 255), 1.0f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Bone12.x, Bone12.y), ImVec2(Bone15.x, Bone15.y), ImColor(255, 255, 255), 1.0f);


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
		//InputHandler();
		ImGui::SetNextWindowSize(ImVec2(300, 300));
		ImGui::Begin("DIT ME THANG YUN CHAN", 0);


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
	//if (BaseAddress < 3)
	{
		std::cout << "Found BaseAddress Game: " << hex << BaseAddress << std::endl;
	}
	Driver::CR3();
	//else
	//{
	//	cout << "Cannot Found BaseAdress Game ReTry Again" << endl;
	//	Sleep(3000);
	//	return 0;
	//
	//}
	OverlayWindow::Name = L" ";
	SetupWindow();
	DirectXInit();


	while (TRUE)
	{
		MainLoop();
	}
}
