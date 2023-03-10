#pragma once
// stdafx.h

#define NOMINMAX

#define DIRECTINPUT_VERSION 0x0800

#ifdef _DEBUG

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#endif // _DEBUG

#pragma warning(disable : 4506)

//STD
#include<Windows.h>
#include<assert.h>
#include<iostream>
#include<vector>
#include<sstream>
#include<map>
#include<unordered_map>
#include<random>
#include<chrono>
#include<functional>
#include<memory>
#include<typeinfo>
#include<mutex>
#include<fstream>

//DX
#include<d3dcompiler.h>
#include<d3d11.h>
#include<D3DX10math.h>
#include<D3DX11async.h>
#include<dinput.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using uint = unsigned int;

// 매크로 함수
#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}

//Math
#include"Math/Math.h"

// Utility
#include"Utility/Geometry_Generator.h"
#include"Utility/GUID_Generator.h"
#include"Utility/Xml.h"
#include"Utility/ImGui/imgui.h"
#include"Utility/ImGui/imgui_impl_win32.h"
#include"Utility/ImGui/imgui_impl_dx11.h"
#include"Utility/Logsystem.h"

//Framework
#include"Core/Settings.h"
#include"Core/Object.h"

// Main System
#include"Core/Context.h"

// Subsystem
#include"Core/SubSystem/Graphics.h"
#include"Core/SubSystem/SceneManager.h"
#include"Core/SubSystem/Renderer/Renderer.h"
#include"Core/SubSystem/Timer.h"
#include"Core/SubSystem/ResourceManager.h"
#include"Core/SubSystem/InputManager.h"

#include"Core/D3D11/Vertex/D3D11_Vertex.h"
#include"Core/D3D11/Vertex/D3D11_Geometry.h"

#include"Core/D3D11/InputAssembler/D3D11_VertexBuffer.h"
#include"Core/D3D11/InputAssembler/D3D11_IndexBuffer.h"
#include"Core/D3D11/InputAssembler/D3D11_InputLayout.h"

#include"Core/D3D11/Shader/D3D11_Shader.h"
#include"Core/D3D11/Shader/D3D11_ConstantBuffer.h"
#include"Core/D3D11/Shader/D3D11_Texture.h"
#include"Core/D3D11/Shader/D3D11_SamplerState.h"

#include"Core/D3D11/Rasterizer/D3D11_RasterizerState.h"
#include"Core/D3D11/Rasterizer/D3D11_Viewport.h"

#include"Core/D3D11/OutputMerger/D3D11_Blend_state.h"

#include"Core/D3D11/D3D11_Pipeline.h"

// Resource
#include "Resource/Animation.h"