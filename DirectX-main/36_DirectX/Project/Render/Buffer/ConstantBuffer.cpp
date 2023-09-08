#include "Framework.h"
#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
	:data(data),dataSize(dataSize)
{
	
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth           = dataSize;
    bufferDesc.Usage               = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags      = 0;
    bufferDesc.MiscFlags           = 0;
    bufferDesc.StructureByteStride = 0;

   
    DEVICE->CreateBuffer(&bufferDesc, nullptr, &constantBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
    constantBuffer->Release();
}

void ConstantBuffer::VSSetBuffer(UINT slot)
{
    DC->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);//DX에서 resource는 buffer이다.

    DC->VSSetConstantBuffers(slot, 1, &constantBuffer);
}

void ConstantBuffer::PSSetBuffer(UINT slot)
{
    DC->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);//DX에서 resource는 buffer이다.

    DC->PSSetConstantBuffers(slot, 1, &constantBuffer);

}
