// Program.cpp
#include"stdafx.h"
#include"Core/Window.h"
#include"Core/Engine.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	//std::cout << GUID_Generator::Generate();

	// 생성
	Window::Create(hInstance, 1000, 1000);
	Window::Show();

	Settings::Get().SetWindowHandle(Window::global_handle);
	Settings::Get().SetWindowInstance(Window::global_instance);
	Settings::Get().SetWidth(static_cast<float>(Window::GetWidth()));
	Settings::Get().SetHeight(static_cast<float>(Window::GetHeight()));

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	// 업데이트
	while (Window::Update())
	{
		engine->Update();
		engine->Render();
	}

	// 해제
	Window::Destroy();
}