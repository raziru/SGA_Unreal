#pragma once
class SolarScene:public Scene
{
public:
	SolarScene();
	~SolarScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:

	Star* sun     = nullptr;
	Star* mecury  = nullptr;
	Star* venus   = nullptr;
	Star* earth   = nullptr;
	Star* mars    = nullptr;
	Star* jupiter = nullptr;
	Star* saturn  = nullptr;
	Star* uranus  = nullptr;
	Star* neptune = nullptr;
	Star* pluto   = nullptr;






	

};


