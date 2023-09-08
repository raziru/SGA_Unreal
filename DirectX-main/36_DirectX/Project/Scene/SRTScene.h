#pragma once
class SRTScene:public Scene
{
public:
	SRTScene();
	~SRTScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;


private:
	Object* object;

	XMFLOAT2 scale       = {1.0f, 1.0f};//scale�� 1�� �ʱ�ȭ�ؾ��Ѵ�.
	XMFLOAT2 translation = {0.0f, 0.0f};


	float angle = 0.0f;
	
	XMMATRIX      world;
	//XMMATRIX      world2;

	XMMATRIX S, R, T;
	
	
	MatrixBuffer* worldBuffer;
	
	

};


