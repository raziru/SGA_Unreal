#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void SetShader();

private:
	ID3D11InputLayout* inputLayout;

	ID3D11VertexShader* vertexShader;
	
	ID3DBlob* blob;

};

