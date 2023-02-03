#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Update()
{
	D3DXVECTOR3 position = transform->GetPosition();

	auto input = context->GetSubsystem<InputManager>();

	input->GetKeyState(DIK_W) == KEY_HOLD || input->GetKeyState(DIK_W) == KEY_DOWN;
	input->GetKeyState(DIK_S);
	input->GetKeyState(DIK_A);
	input->GetKeyState(DIK_D);

	if (GetAsyncKeyState('W') & 0x8000) position.y += 3;
	if (GetAsyncKeyState('S') & 0x8000) position.y -= 3;
	if (GetAsyncKeyState('D') & 0x8000) position.x += 3;
	if (GetAsyncKeyState('A') & 0x8000) position.x -= 3;

	if (input->GetMouseState(MOUSE_LEFT) == KEY_DOWN)
	{
		position.x = input->GetMousePosition().x;
		position.y = input->GetMousePosition().y;
	}

	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}