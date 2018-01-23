#pragma once

#include "Common/d3dApp.h"
#include "Common/MathHelper.h"
#include "Common/UploadBuffer.h"
#include "Common/GeometryGenerator.h"
#include "FrameResource.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

const int gNumFrameResources = 3;

//Lightweight structure stores parameters to draw a shape. This will vary from app-to-app.
struct RenderItem {

	RenderItem() = default;

	//World matrix of the shape that describe the object's local space relative to the world space,
	//which defines the position, orientation and scale of the object in the world.
	XMFLOAT4X4 World = MathHelper::Identity4x4();

	//Dirty flag indicating the object data has changed and we need to update the constant buffer.
	//Because we have an object cbuffer for each FrameResource, we have to apply the update to each FrameResource.
	//Thus, when we modify object data we should set NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
	int NumFramesDirty = gNumFrameResources;

	//Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT objCBIndex = -1;

	MeshGeometry* Geo = nullptr;

	//Primitive topology.
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	//DrawIndexedInstanced parameters.
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	int BaseVertexLocation = 0;

};