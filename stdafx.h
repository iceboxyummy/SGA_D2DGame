#pragma once
// stdafx.h

#define NOMINMAX

#ifdef _DEBUG

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#endif // _DEBUG

//STD
#include<Windows.h>
#include<assert.h>
#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<random>
#include<chrono>
#include<functional>
#include<memory>

//DX
#include<d3dcompiler.h>
#include<d3d11.h>
#include<D3DX10math.h>
#include<D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")


using uint = unsigned int;

// ��ũ�� �Լ�
#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}

//Math
#include"Math/Math.h"

//Timer
#include"Timer/Timer.h"

//Intersect
#include"Intersect/Intersect.h"

// Utility
#include"Utility/Geometry_Generator.h"
#include"Utility/GUID_Generator.h"

//Framework
#include"Core/Settings.h"
#include"Core/Object.h"
#include"Core/Graphics.h"

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