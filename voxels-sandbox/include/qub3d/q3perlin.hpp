#pragma once

#include <glm/glm.hpp>

class Q3PerlinNoiseGenerator {
private:
    float fade(float t);
    int inc(int num);
    float grad(int hash, float x, float y, float z);
    float lerp(float a, float b, float x);
public:
    Q3PerlinNoiseGenerator();
    
    float perlin(glm::vec3 pos);
    float octavePerlin(glm::vec3 pos, int octaves, float persitance);
private:
    int m_p[512];
    int m_repeat;
};