#pragma once
class SRTScene:public Scene
{
public:
	SRTScene();
	~SRTScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;


private:
	Object* object;

	XMFLOAT2 scale       = {1.0f, 1.0f};//scale은 1로 초기화해야한다.
	XMFLOAT2 translation = {0.0f, 0.0f};


	float angle = 0.0f;
	
	XMMATRIX      world;
	//XMMATRIX      world2;

	XMMATRIX S, R, T;
	
	
	MatrixBuffer* worldBuffer;
	
	

};


