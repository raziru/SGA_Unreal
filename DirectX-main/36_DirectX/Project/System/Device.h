#pragma once
class Device:public Singleton<Device>
{
	friend class Singleton;//대상 class에게 private를 열어주는 것 Device->Singleton은 불가능함
private:
	Device();
	~Device();

	void Initialize();

public:
	void ClearRTV();//render target view
	void Present();

	ID3D11Device*        GetDevice(){ return device; }
	ID3D11DeviceContext* GetDC()    { return deviceContext; }

private:
	ID3D11Device*        device;       //무언가를 만드는 역할, CPU를 다루는 객체
	ID3D11DeviceContext* deviceContext;//무언가를 그리는 역할, GPU를 다루는 객체

	IDXGISwapChain*         swapChain;
	ID3D11RenderTargetView* renderTargetView;
};

