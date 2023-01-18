#include "stdafx.h"
#include "TargetTraceComponent.h"
#include "TransformComponent.h"
#include "Scene/Actor.h"

void TargetTraceComponent::Initialize()
{
	Timer.Start();
}

void TargetTraceComponent::Update()
{
	if (target.expired() == true) return;

	D3DXVECTOR3 my_position = transform->GetPosition();

	D3DXVECTOR3 target_position = target.lock()->GetTransform()->GetPosition();

	/*if (my_position.x >= target_position.x) my_position.x--;
	else my_position.x++;

	if (my_position.y >= target_position.y) my_position.y--;
	else my_position.y++;*/

	// A - B = B에서 A로 향하는 벡터
	D3DXVECTOR3 vector = target_position - my_position;

	// 피타고라스의 정리를 이용한 길이 구하기
	// 길이(빗변)^2 = 밑변^2 + 높이^2 
	// -> √빗변^2 = -> √(밑변^2 + 높이^2)
	// -> 빗변 = √(밑변^2 + 높이^2)
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	// 단위 벡터로 만들어 순수한 방향값으로 바꾼다.
	D3DXVECTOR3 direction;
	D3DXVec3Normalize(&direction, &vector);


	// 다음 위치 갱신
	D3DXVECTOR3 move_position;
	move_position = my_position + direction * speed * Timer.GetElapsedTimeSec();

	Timer.Start();

	transform->SetPosition(move_position);
}

void TargetTraceComponent::Destroy()
{
}

void TargetTraceComponent::SetTarget(const std::shared_ptr<const class Actor> target)
{
	if (actor == target.get()) return;

	this->target = target;
}