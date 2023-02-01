#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	context = new Context();

	context->RegisterSubsystem<Timer>();

	context->RegisterSubsystem<Graphics>();
	context->RegisterSubsystem<SceneManager>();

	context->RegisterSubsystem<Renderer>();
	context->RegisterSubsystem<ResourceManager>();

	context->InitializeSubSystems();
}

Engine::~Engine()
{
	SAFE_DELETE(context)
}

void Engine::Update()
{
	context->UpdateSubsystems();
}

void Engine::Render()
{
	Renderer* renderer = context->GetSubsystem<Renderer>();
	renderer->Update();
}