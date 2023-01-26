#include "stdafx.h"
#include "Animation.h"

Animation::Animation(Context* const context)
	: context(context)
{
}

Animation::~Animation()
{
}

void Animation::SetSpriteTexture(const std::string& path)
{
	sprite_texture = std::make_shared<D3D11_Texture>(context->GetSubsystem<Graphics>());
	sprite_texture->Create(path);
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
	keyframes.emplace_back(keyframe);
}

void Animation::AddKeyframe(const D3DXVECTOR2& offset, const D3DXVECTOR2& size, const double& time)
{
	keyframes.emplace_back(offset, size, time);
}

const Keyframe* const Animation::GetKeyframeFromIndex(const uint& index)
{
	if (index >= keyframes.size())
	{
		assert(index < keyframes.size());
		return nullptr;
	}
	return &keyframes[index];
}