#include "VertexData.hlsl"
#include "ConstantBuffer.hlsl"

VertexOutput_P4N4T4L4 main(VertexInput_P3N3T3 input) {

    VertexOutput_P4N4T4L4 output;
    float4 HPos = float4(input.position, 1.0f);

    // position
    output.position = mul(HPos, modelMatrix);
	output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // normal
    float4 HNormal = float4(input.normal, 0.0);
    output.worldNormal = normalize(mul(HNormal, modelMatrix));
    output.worldNormal = normalize(mul(output.worldNormal, worldMatrix));

    // texcoord
    output.texCoord = float4(input.texCoord.xyz, 1);
    
    // lightPosition
    output.lightPosition = mul(HPos, modelMatrix);
    output.lightPosition = mul(output.lightPosition, worldMatrix);
    output.lightPosition = mul(output.lightPosition, lightViewProj);
	return output;
}