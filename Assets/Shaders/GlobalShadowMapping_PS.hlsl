#include "VertexData.hlsl"
#include "ConstantBuffer.hlsl"

float4 main(VertexInput_P3 input) {

    VertexOutput_P4 output;

    float HPos = float4(input.position, 1.0f);
    output.position = mul(HPos, modelMatrix);
    output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, lightViewProj);

    return output;
}