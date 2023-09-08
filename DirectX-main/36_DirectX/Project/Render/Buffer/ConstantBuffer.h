#pragma once
class ConstantBuffer//���̴� ���ο��� ����ϻ� c++������ ��� ���Ѵ�
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

