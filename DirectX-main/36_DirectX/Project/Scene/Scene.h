#pragma once
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

private:

};

