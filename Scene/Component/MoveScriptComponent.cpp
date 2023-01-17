#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Update()
{
	D3DXVECTOR3 position = transform->GetPosition();

	if (GetAsyncKeyState('W') & 0x8000) position.y += 3;
	if (GetAsyncKeyState('S') & 0x8000) position.y -= 3;
	if (GetAsyncKeyState('D') & 0x8000) position.x += 3;
	if (GetAsyncKeyState('A') & 0x8000) position.x -= 3;

	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}