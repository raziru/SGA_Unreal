#pragma once


class TutorialScene:public Scene
{
public:
	TutorialScene();
	~TutorialScene();
		// Scene을(를) 통해 상속됨
	void Update() override;
	void Render() override;

private:
	Object* object = nullptr;
	XMFLOAT2 translation;

	XMFLOAT4X4 S, R, T;

	XMMATRIX      worldMatrix;
	MatrixBuffer* worldBuffer;


	float theta = 0.0f;
	

};

