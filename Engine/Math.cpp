#include "Math.h"
#include <math.h>

#include <algorithm>

void Math::SetXMFLOAT4(XMFLOAT4 xmf4, float x, float y, float z, float w)
{
    xmf4.x = x;
    xmf4.y = y;
    xmf4.z = z;
    xmf4.w = w;
}
void Math::SetXMFLOAT3(XMFLOAT3 xmf3, float x, float y, float z)
{
    xmf3.x = x;
    xmf3.y = y;
    xmf3.z = z;
}

XMINT3 Math::ToXMINT(XMFLOAT3 vec)
{
    return { (int)vec.x, (int)vec.y, (int)vec.z };
}

XMFLOAT3 Math::SubXMFLOAT3(XMFLOAT3 vec, XMFLOAT3 vec2)
{
    return XMFLOAT3(vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z);
}

float Math::CalcDist(XMFLOAT3 vec, XMFLOAT3 vec2)
{
    XMFLOAT3 vec3 = SubXMFLOAT3(vec, vec2);

    return sqrtf( (vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z) );
}

XMFLOAT3 Math::VectorToFloat3(XMVECTOR v)
{
    return XMFLOAT3();
}

XMFLOAT3 VectorToFloat3(XMVECTOR v)
{
    XMFLOAT3 xmf3;
    XMStoreFloat3(&xmf3, v);

    return xmf3;
}