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

	Star* sun = nullptr;
	

};


