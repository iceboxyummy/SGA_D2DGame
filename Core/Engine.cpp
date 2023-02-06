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

	context->InitializeSubSystems();

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