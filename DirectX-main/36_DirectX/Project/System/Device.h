#pragma once
class Device:public Singleton<Device>
{
	friend class Singleton;//��� class���� private�� �����ִ� �� Device->Singleton�� �Ұ�����
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
	ID3D11Device*        device;       //���𰡸� ����� ����, CPU�� �ٷ�� ��ü
	ID3D11DeviceContext* deviceContext;//���𰡸� �׸��� ����, GPU�� �ٷ�� ��ü

	IDXGISwapChain*         swapChain;
	ID3D11RenderTargetView* renderTargetView;
};

