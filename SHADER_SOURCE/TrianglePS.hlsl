
struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

float4 PS_TEST(VTX_OUT _in)
{
    return _in.vColor;
}