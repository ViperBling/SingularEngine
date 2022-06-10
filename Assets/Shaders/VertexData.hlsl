struct VertexInput_P3N3T3
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 texCoord : TEXCOORD;
};

struct VertexOutput_P4N4T4L4
{
    float4 position : SV_POSITION;
    float4 worldNormal : NORMAL;
    float4 texCoord : TEXCOORD0;
    float4 lightPosition : TEXCOORD1;
};

struct VertexInput_P3
{
    float3 position : POSITION;
};

struct VertexOutput_P4
{
    float4 position : SV_POSITION;
};

struct VertexInput_P3N3
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct VertexOutput_P4N4L4
{
    float4 position : SV_POSITION;
	float4 worldNormal : NORMAL;
	float4 lightPosition : TEXCOORD0;
};

struct VertexInput_P3T3
{
    float3 position : POSITION;
	float3 texCoord : TEXCOORD;
};

struct VertexOutput_P4T4
{
	float4 position : SV_POSITION;
    float4 texCoord : TEXCOORD;
};
