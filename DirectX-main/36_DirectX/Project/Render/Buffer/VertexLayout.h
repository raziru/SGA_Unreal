#pragma once
struct VertexColor
{
	VertexColor(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		pos.z = 0.0f;
	}

	VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
		:pos(pos), color(color)
	{

	}
	XMFLOAT3 pos = {};
	XMFLOAT4 color = {};
};