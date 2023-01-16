#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"

Execute::Execute()
{
	Graphics::Get().Initialize();
	Graphics::Get().CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

	//================================================================================================
	// [Camera]
	//================================================================================================
	camera_buffer = new D3D11_ConstantBuffer(graphics);
	camera_buffer->Create<CAMERA_DATA>();

	//================================================================================================
	// [Pipeline]
	//================================================================================================
	pipeline = new D3D11_Pipeline(&Graphics::Get());

}

Execute::~Execute()
{
	
	SAFE_DELETE(pipeline);
	SAFE_DELETE(camera_buffer);
}

void Execute::Update()
{
	for (const auto& actor : actors)
		actor->Update();
	

}

void Execute::Render()
{

	Graphics::Get().Begin();
	{
		pipeline->SetConstantBuffer(0, ShaderScope_VS, camera_buffer);

		for (const auto& actor : actors)
			actor->Render(pipeline);
	}
	Graphics::Get().End();
}
