#pragma once
class Star
{
public:
	Star();
	~Star();

	virtual void Update();
	void Render();

	XMFLOAT2& Scale()       { return scale; }
	XMFLOAT2& Translation() { return translation; }

	float& Dir()         { return dir; }
	XMMATRIX& SetParent()   { return parentWorld; }
	XMMATRIX& GetWorld()    { return world; }




private:
	Object* object = nullptr;

	XMMATRIX S, R, T;

	XMMATRIX      world;

	XMMATRIX      parentWorld;

	MatrixBuffer* worldBuffer;

protected:
	XMFLOAT2 scale = { 1.0f, 1.0f };//scale은 1로 초기화해야한다.
	XMFLOAT2 translation = { 0.0f, 0.0f };


	float angle = 0.0f;

	float dir = 1.0f;

	
};



