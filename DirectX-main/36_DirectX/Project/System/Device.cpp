#include "Framework.h"
#include "Device.h"

Device::Device()
{
	Initialize();
}

Device::~Device()
{
              device->Release();
       deviceContext->Release();
           swapChain->Release();
    renderTargetView->Release();
}

void Device::Initialize()
{
    //Descriptor: 설명서 : 함수에 들어갈 매개변수들을 모아둔 객체
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //0~1까지 사이의 수로 입력한다. unsigned normalized
    //R,G,B,A: 들어갈 변수가 들어갈 칸, 숫자: 들어올 자료형의 크기, bit 단위이다 8bits = 1byte, 
    //UNORM: 입력되는 숫자의 종류, float:실수형 전체, sint: signed int, uint: unsigned int, unorm: 0~1로 normalize된 것
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;//주사율 분자
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;//주사율 분모


    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = true;


    D3D11CreateDeviceAndSwapChain//swapchain과 device, deviceContext를 같이 생성한다.
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,//double pointer: 포인터의 포인터: 함수에서 동적할당하고 싶을 때 사용한다
        //-return을 사용해서 new를 반환하는게 추세
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer = nullptr;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    //swapchain에 쓰이는 정보를 가져다 backBuffer를 동적할당하는 작업, __uuidof: 객체의 고유ID를 꺼내는 명령어, 클래스가 무엇인지 전달

    //view가 들어가면 gpu쪽 리소스를 사용한다.
    device->CreateRenderTargetView
    (
        backBuffer, nullptr, &renderTargetView
    );

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
    //OM: Output Merger, OM조건을 설정한다. draw하기전에 모든 설정을 마무리해야한다.
    //Render Target: 화면 

    //viewPort//
    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    deviceContext->RSSetViewports(1, &viewPort);
}

void Device::ClearRTV()
{
    float clearColor[4] = { 0.0f,0.125f,0.3f,1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);//patblt
}

void Device::Present()
{
    swapChain->Present(0, 0);//bitblt 뒤에 있는것을 앞으로 당기는것
    //sync interval: vsync 여부 결정
}
