cbuffer World : register(b0)
    //const buffer, shader 내부에서는 바뀌지 않는 상수, b0 슬롯으로 넘겨줄때 레지스터 위치만 보고 가져간다.
{
    matrix world;
}
//layoutbuffer, indexbuffer외에는 모두 const buffer이다.

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Proj : register(b2)
{
    matrix proj;
}

struct VertexInput
{
    float4 pos   : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

VertexOutput main( VertexInput input )
{ 
    VertexOutput output;
    output.pos = mul( input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.color = input.color;
    
	return output;
}