#include "stdafx.h"
#include "AnimatorComponent.h"

AnimatorComponent::AnimatorComponent(Context* const context, Actor* const actor, TransformComponent* const transform)
	: IComponent(context, actor, transform)
{
	timer = context->GetSubsystem<Timer>();
}

void AnimatorComponent::Initialize()
{
}

void AnimatorComponent::Update()
{
	if (current_animation.expired() == true || IsPlaying() == false) return;

	frame_counter += timer->GetDeltaTimeMS();

	if (frame_counter > GetCurrentKeyframe()->time)
	{
		current_frame_number++;

		switch (current_animation.lock()->GetRepeatType())
		{
		case RepeatType::Once:
		{
			if (current_frame_number >= current_animation.lock()->GetKeyframeCount())
			{
				current_frame_number = current_animation.lock()->GetKeyframeCount() - 1;
				Pause();
			}
			break;
		}

		case RepeatType::Loop:
		{
			current_frame_number %= current_animation.lock()->GetKeyframeCount();

			break;
		}
		}
		frame_counter = 0.0;
	}
}

void AnimatorComponent::Destroy()
{
}

const std::shared_ptr<class Animation> AnimatorComponent::GetCurrentAnimation() const
{
	return current_animation.expired() ? nullptr : current_animation.lock();
}

void AnimatorComponent::SetCurrentAnimation(const std::string& animation_name)
{
	if (animations.find(animation_name) == animations.end())
	{
		assert(false);
		return;
	}
	current_animation = animations[animation_name];

	current_frame_number = 0;
	frame_counter = 0.0f;
}

const Keyframe* const AnimatorComponent::GetCurrentKeyframe() const
{
	if (current_animation.expired() == true)
	{
		assert(false);
		return nullptr;
	}
	return current_animation.lock()->GetKeyframeFromIndex(current_frame_number);
}

void AnimatorComponent::AddAnimation(const std::string& animation_name, const std::shared_ptr<class Animation>& animation)
{
	if (animations.find(animation_name) != animations.end())
	{
		assert(false);
		return;
	}
	animations[animation_name] = animation;
}

void AnimatorComponent::Play()
{
	animation_mode = AnimationMode::Play;
	frame_counter = 0.0f;
}

void AnimatorComponent::Stop()
{
	animation_mode = AnimationMode::Stop;
	current_frame_number = 0;
	frame_counter = 0.0f;
}

void AnimatorComponent::Pause()
{
	animation_mode = AnimationMode::Pause;
}