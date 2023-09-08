#pragma once
class ConstantBuffer//쉐이더 내부에서 상수일뿐 c++에서는 계속 변한다
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	~ConstantBuffer();

	void VSSetBuffer(UINT slot);
	void PSSetBuffer(UINT slot);


private:
	ID3D11Buffer* constantBuffer;

	void* data;
	UINT  dataSize;
};

