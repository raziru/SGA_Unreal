#pragma once
class Object
{
public:
	Object(XMFLOAT4 color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	~Object();

	void Render();


private:
	vector<VertexColor> vertices;
	vector<UINT>         indices;

	VertexBuffer* vertexBuffer;
	 IndexBuffer*  indexBuffer;
	VertexShader* vertexShader;

	PixelShader* pixelShader;
};

