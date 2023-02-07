#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	context = new Context();

	context->RegisterSubsystem<Timer>();
	context->RegisterSubsystem<InputManager>();

	context->RegisterSubsystem<Graphics>();
	context->RegisterSubsystem<SceneManager>();

	context->RegisterSubsystem<Renderer>();
	context->RegisterSubsystem<ResourceManager>();

	bool hr = context->InitializeSubSystems();

	if (hr == true)
		LOG_INFO("시스템 세팅 성공");
	else
		LOG_INFO("시스템 세팅 실패");		

	LOG_TARGET_FILE();
	LOG_WARNING("플레이어가 비정상적인 위치에 도달함 :%d %d %d", 10, 20, 30);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(Settings::Get().GetWindowhandle());
	auto graphics = context->GetSubsystem<Graphics>();
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
}

Engine::~Engine()
{
	SAFE_DELETE(context)
}

void Engine::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	context->UpdateSubsystems();
}

void Engine::Render()
{
	Renderer* renderer = context->GetSubsystem<Renderer>();
	renderer->Update();
}