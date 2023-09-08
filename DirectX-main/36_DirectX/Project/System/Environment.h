#pragma once
class Environment:public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	void Update();

	void Set();

private:
	XMMATRIX       viewMatrix;
	XMMATRIX projectionMatrix;

	MatrixBuffer*       viewBuffer;
	MatrixBuffer* projectionBuffer;

};

