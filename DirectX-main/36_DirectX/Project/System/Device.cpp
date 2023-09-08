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
    //Descriptor: ���� : �Լ��� �� �Ű��������� ��Ƶ� ��ü
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //0~1���� ������ ���� �Է��Ѵ�. unsigned normalized
    //R,G,B,A: �� ������ �� ĭ, ����: ���� �ڷ����� ũ��, bit �����̴� 8bits = 1byte, 
    //UNORM: �ԷµǴ� ������ ����, float:�Ǽ��� ��ü, sint: signed int, uint: unsigned int, unorm: 0~1�� normalize�� ��
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;//�ֻ��� ����
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;//�ֻ��� �и�


    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = true;


    D3D11CreateDeviceAndSwapChain//swapchain�� device, deviceContext�� ���� �����Ѵ�.
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,//double pointer: �������� ������: �Լ����� �����Ҵ��ϰ� ���� �� ����Ѵ�
        //-return�� ����ؼ� new�� ��ȯ�ϴ°� �߼�
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer = nullptr;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    //swapchain�� ���̴� ������ ������ backBuffer�� �����Ҵ��ϴ� �۾�, __uuidof: ��ü�� ����ID�� ������ ��ɾ�, Ŭ������ �������� ����

    //view�� ���� gpu�� ���ҽ��� ����Ѵ�.
    device->CreateRenderTargetView
    (
        backBuffer, nullptr, &renderTargetView
    );

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
    //OM: Output Merger, OM������ �����Ѵ�. draw�ϱ����� ��� ������ �������ؾ��Ѵ�.
    //Render Target: ȭ�� 

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
    swapChain->Present(0, 0);//bitblt �ڿ� �ִ°��� ������ ���°�
    //sync interval: vsync ���� ����
}
