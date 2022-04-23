// g++ -o mm256_mul_ps mm256_mul_ps.cpp -mavx
#include <immintrin.h>
#include <random>
#include <iostream>

float mul_vector(std::vector<float> &a, int vector_size) {
    __m256 result8 = _mm256_set1_ps(1.0f);
    __m256 value;
    for(size_t i = 0; i < vector_size; i += 8) {
        value = _mm256_load_ps(&a[i]);
        result8 = _mm256_mul_ps(result8, value);
    }
    float result[8];
    _mm256_store_ps(result, result8);
    float final_result = 1.0f;
    for (size_t i = 0; i < 8; ++i) {
        final_result *= result[i];
    }
    return final_result;
}

int main(){
    int vector_size = 1024;
    std::vector<float> a(vector_size);
    std::mt19937 gen(0);
    std::uniform_real_distribution<> dis(1.0f, 1.01f);
    for (size_t i = 0; i < vector_size; i += 1) {
        a[i] = dis(gen);
    }
    std::cout << mul_vector(a, vector_size) << std::endl;
    return 0;
}