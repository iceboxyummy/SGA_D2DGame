#pragma once

#include "IComponent.h"

enum class AnimationMode : uint
{
	Play, 
	Stop,
	Pause
};

class AnimatorComponent : public IComponent
{
public:
	AnimatorComponent(
		class Context* const context,
		class Actor* const actor,
		class TransformComponent* const transform
	);

	~AnimatorComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	const AnimationMode& GetAnimationMode() const { return animation_mode; }
	void SetAnimationMode(const AnimationMode& mode) { this->animation_mode = mode; }

	const uint& GetCurerntFrameNumber() const { return current_frame_number; }
	void SetCurrentFrameNumber(const uint& number) { this->current_frame_number = number; }

	const std::shared_ptr<class Animation> GetCurrentAnimation() const;
	void SetCurrentAnimation(const std::string& animation_name);

	const std::map<std::string, std::shared_ptr<class Animation>>& GetAnimations() const { return animations; }
	const Keyframe* const GetCurrentKeyframe() const;

	void AddAnimation(const std::string& animation_name, const std::shared_ptr<class Animation>& animation);

	void Play();
	void Stop();
	void Pause();

	bool IsPlaying() const { return animation_mode == AnimationMode::Play; }

private:
	class Timer* timer = nullptr;
	AnimationMode animation_mode = AnimationMode::Play;
	uint current_frame_number = 0;
	float frame_counter = 0.0f;

	std::weak_ptr<class Animation> current_animation;
	std::map<std::string, std::shared_ptr<class Animation>>animations;
};