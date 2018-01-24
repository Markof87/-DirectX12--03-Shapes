#include "ShapesApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {

	//Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try {

		ShapesApp theApp(hInstance);
		if (!theApp.Initialize()) return 0;

		return theApp.Run();

	}

	catch (DxException e) {

		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;

	}

}

ShapesApp::ShapesApp(HINSTANCE hInstance) : D3DApp(hInstance) {}

ShapesApp::~ShapesApp() {
	if (md3dDevice != nullptr) FlushCommandQueue();
}

bool ShapesApp::Initialize() {

	if (!D3DApp::Initialize()) return false;

	//Reset the command list to prepare for initialization commands.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	BuildRootSignature();
	BuildShadersAndInputLayout();
	BuildShapeGeometry();
	BuildRenderItems();
	BuildFrameResource();
	BuildDescriptorHeaps();
	BuildConstantBufferViews();
	BuildPSO();

	//Execute the initialization commands.
	ThrowIfFailed(mCommandList->Close());
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	//Wait until initialization is complete.
	FlushCommandQueue();

	return true;

}

