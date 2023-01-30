#include "stdafx.h"
#include "Animation.h"

Animation::Animation(Context* const context)
	: context(context)
{
}

Animation::~Animation()
{
}

bool Animation::SaveFile(const std::string& path)
{
	Xml::XMLDocument doc;

	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);

	Xml::XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);

	root->SetAttribute("Name", animation_name.c_str());
	root->SetAttribute("Type", static_cast<uint>(repeat_type));

	root->SetAttribute("TextureSizeX", sprite_texture_size.x);
	root->SetAttribute("TextureSizeY", sprite_texture_size.y);

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* element = doc.NewElement("Keyframe");
		root->LinkEndChild(element);

		element->SetAttribute("OffsetX", keyframe.offset.x);
		element->SetAttribute("OffsetY", keyframe.offset.y);

		element->SetAttribute("SizeY", keyframe.size.y);
		element->SetAttribute("SizeY", keyframe.size.y);

		element->SetAttribute("Time", keyframe.time);
	}

	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(path.c_str());
	
	/*
		doc
		�� decl
		�� Animation -> repeat_type, sprite_size.....
			�� Ű������1 -> Ű������ ������
			�� Ű������2 -> Ű������ ������
			�� Ű������3 -> Ű������ ������
	*/
}

bool Animation::LoadFromFile(const std::string& path)
{
	Xml::XMLDocument doc;

	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}

	Xml::XMLElement* root = doc.FirstChildElement();

	animation_name = root->Attribute("Name");
	repeat_type = static_cast<RepeatType>(root->UnsignedAttribute("Type"));

	sprite_texture_size.x = root->FloatAttribute("TextureSizeX");
	sprite_texture_size.y = root->FloatAttribute("TextureSizeY");

	return true;
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