#pragma once

#include "IComponent.h"

class TargetTraceComponent : public IComponent
{
private:
	enum State
	{
		Trace,
		Avoid
	};

public:
	using IComponent::IComponent;
	~TargetTraceComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetTarget(const std::shared_ptr<const class Actor> target);

private:
	std::weak_ptr<const class Actor> target;
	Stopwatch Timer;
	float speed = 50.0f;
	State current_state = State::Trace;
};