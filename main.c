///https://www.youtube.com/watch?v=MQgsDKId_yI
 
 
#include <iostream>
#include <Windows.h>
#include <time.h>
#define WIDTH 550
#if 1
#define HEIGHT WIDTH
#else
#define HEIGHT 600
#endif
struct vec4
{
    float x, y, z, w;
    vec4() { __asm mov eax, [this] __asm xorps xmm0, xmm0 __asm mov [eax], xmm0 }
    vec4(float _x, float _y, float _z, float _w) {__asm mov eax, [this] __asm movups xmm0, [_x] __asm movups [eax], xmm0 }
    vec4(float _x, float _y, float _z) { *(double*)&x = *(double*)&_x; z = _z; w = 0; }
    vec4(float _x, float _y) { *(double*)&x = *(double*)&_x; __asm xorps xmm0, xmm0 __asm movsd [eax+8], xmm0 }
    vec4(float f) { __asm mov eax, [this] __asm movss xmm0, [f] __asm movss xmm1, xmm0 __asm shufps xmm0, xmm1, 0 __asm movups [eax], xmm0 }
    inline vec4 operator+ (vec4 v)
    {
        vec4 ret;
        __asm mov eax, [this] __asm movups xmm0, [eax] __asm movups xmm1, [v] __asm addps xmm0, xmm1 __asm movups[ret], xmm0
        return ret;
    }
    inline vec4 operator- (vec4 v)
    {
        vec4 ret;
        __asm mov eax, [this] __asm movups xmm0, [eax] __asm movups xmm1, [v] __asm subps xmm0, xmm1 __asm movups[ret], xmm0
        return ret;
    }
    inline vec4 operator* (vec4 v)
    {
        vec4 ret;
        __asm mov eax, [this] __asm movups xmm0, [eax] __asm movups xmm1, [v] __asm mulps xmm0, xmm1 __asm movups[ret], xmm0
        return ret;
    }
    inline vec4 operator/ (vec4 v)
    {
        vec4 ret;
        __asm mov eax, [this] __asm movups xmm0, [eax] __asm movups xmm1, [v] __asm divps xmm0, xmm1 __asm movups[ret], xmm0
        return ret;
    }
};
struct vec3
{
    float x, y, z;
    vec3() { __asm mov eax, [this] __asm xorps xmm0, xmm0 __asm movups [eax], xmm0 }
    vec3(float _x, float _y, float _z) { *(double*)&x = *(double*)&_x; z = _z; }
    vec3(float _x, float _y) { *(double*)&x = *(double*)&_x; z = 0; }
    vec3(float f) { __asm mov eax, [this] __asm movss xmm0, [f] __asm movss [eax], xmm0 __asm movss [eax+4], xmm0 __asm movss [eax+8], xmm0 }
};
struct vec2
{
    float x, y;
    vec2()
    {
        __asm
        {
            mov eax, [this]
            xorps xmm0, xmm0
            movsd[eax], xmm0
        }
    }
    vec2(float _x, float _y)
    {
        *(double*)&x = *(double*)&_x;
    }
    vec2(float f) { x = y = f; }
    inline vec2 operator+ (vec2 v)
    {
        vec2 ret;
        __asm mov eax, [this] __asm movsd xmm0, [eax] __asm movsd xmm1, [v] __asm addps xmm0, xmm1 __asm movsd[ret], xmm0
        return ret;
    }
    inline vec2 operator- (vec2 v)
    {
        vec2 ret;
        __asm mov eax, [this] __asm movsd xmm0, [eax] __asm movsd xmm1, [v] __asm subps xmm0, xmm1 __asm movsd[ret], xmm0
        return ret;
    }
    inline vec2 operator* (vec2 v)
    {
        vec2 ret;
        __asm mov eax, [this] __asm movsd xmm0, [eax] __asm movsd xmm1, [v] __asm mulps xmm0, xmm1 __asm movsd[ret], xmm0
        return ret;
    }
    inline vec2 operator/ (vec2 v)
    {
        vec2 ret;
        __asm mov eax, [this] __asm movsd xmm0, [eax] __asm movsd xmm1, [v] __asm divps xmm0, xmm1 __asm movsd[ret], xmm0
        return ret;
    }
};
inline float dot(vec3 a, vec3 b)
{
    float ret;
    __asm
    {
        movups xmm0, a
        movups xmm0, b
        dpps xmm0, xmm1, 0x71
        movss ret, xmm0
    }
    return ret;
}
inline float dot(vec2 a, vec2 b)
{
    float ret;
    __asm
    {
        movsd xmm0, a
        movsd xmm0, b
        dpps xmm0, xmm1, 0x31
        movss ret, xmm0
    }
    return ret;
}
inline float magnitude(vec3 v)
{
    float ret;
    __asm
    {
        movups xmm0, v
        dpps xmm0, xmm0, 0x71
        movss ret, xmm0
    }
    return ret;
}
inline float magnitude(vec2 v)
{
    float ret;
    __asm
    {
        movups xmm0, v
        dpps xmm0, xmm0, 0x31
        movss ret, xmm0
    }
    return ret;
}
inline vec4 normalize(vec4 v)
{
    vec4 ret;
    __asm
    {
        movups xmm0, v
        movups xmm1, xmm0
        dpps xmm0, xmm0, 0x7F
        rsqrtps xmm0, xmm0
        mulps xmm0, xmm1
        movups ret, xmm0
    }
    return ret;
}
inline float length(vec3 v)
{
    float ret;
    __asm
    {
        movups xmm0, v
        dpps xmm0, xmm0, 0x71
        sqrtss xmm0, xmm0
        movss ret, xmm0
    }
    return ret;
}
inline vec4 negabs(vec4 v)
{
    vec4 ret;
    __asm
    {
        xorps xmm0, xmm0
        movups xmm1, [v]
        subps xmm0, xmm1
        minps xmm0, xmm1
        movups ret, xmm0
    }
    return ret;
}
inline vec4 abs(vec4 v)
{
    vec4 ret;
    __asm
    {
        xorps xmm0, xmm0
        movups xmm1, [v]
        subps xmm0, xmm1
        maxps xmm0, xmm1
        movups ret, xmm0
    }
    return ret;
}
inline vec3 abs(vec3 v)
{
    return vec3(v.x > 0 ? v.x : -v.x,
        v.y > 0 ? v.y : -v.y,
        v.z > 0 ? v.z : -v.z);
}
float clamp(float x, float minval, float maxval)
{
    return min(max(x, minval), maxval);
}
float smoothstep(float minval, float maxval, float x)
{
    float t = clamp((x - minval) / (maxval - minval), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}
inline float random()
{
    return (float)rand() / (float)RAND_MAX;
}
inline float random(float max)
{
    return random()*max;
}
inline float random(float min, float max)
{
    return min + random(max - min);
}
void mainImage(vec2 fragCoord, vec4& fragColor);
vec2 iResolution;
int main()
{
    time_t t = time(NULL);
    iResolution = vec2(WIDTH, HEIGHT);
    vec4 col;
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    SetWindowPos(GetConsoleWindow(), NULL, rect.right / 2 - WIDTH / 2, rect.bottom / 2 - HEIGHT / 2, WIDTH, HEIGHT, SWP_SHOWWINDOW);
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~(WS_MAXIMIZE | WS_SIZEBOX | WS_BORDER | WS_DLGFRAME | WS_HSCROLL | WS_VSCROLL));
    HDC hDC = GetDC(GetConsoleWindow());
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int k = 0; k < WIDTH; k++)
        {
            srand(t);
            mainImage(vec2(float(k), float(i)), col);
            SetPixelV(hDC, k, i, RGB(col.x * 255, col.y * 255, col.z * 255));
        }
    }
    while (true);
    return 0;
}
 
 
 
////////start///////// (example: voronoi diagrams)
 
void mainImage(vec2 fragCoord, vec4& fragColor)
{
    const int MAX = 50;
    vec2 points[MAX];
    vec4 colors[MAX];
    for (int i = 0; i < MAX; i++)
    {
        colors[i] = vec4(random(), random(), random(), 1);
        points[i] = vec2(random(iResolution.x), random(iResolution.y));
    }
    float maxdis = magnitude(fragCoord - points[0]);
    int k = 0;
    for (int i = 1; i < MAX; i++)
    {
        float dis = magnitude(fragCoord - points[i]);
        if (dis < maxdis)
        {
            maxdis = dis;
            k = i;
        }
    }
    fragColor = colors[k];
    for (int i = 0; i < MAX; i++)
    if (magnitude(fragCoord - points[i]) <= 10)
        fragColor = vec4(0, 0, 0, 1);
}
