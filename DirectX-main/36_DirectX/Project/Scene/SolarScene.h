#pragma once
class SolarScene:public Scene
{
public:
	SolarScene();
	~SolarScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:

	Star* sun = nullptr;
	

};


