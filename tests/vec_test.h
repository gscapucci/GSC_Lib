#ifndef VEC_TEST_H
#define VEC_TEST_H


#include "../DataTypes/Vec.h"
#include <assert.h>

// Testes para operações de vetores
void test_vec_operations() {
    // Teste de adição de vetores (V2f32)   
    V2f32 v1 = {.components = {1.0f, 2.0f}};
    V2f32 v2 = {.components = {3.0f, 4.0f}};
    V2f32 v_add = V2f32_add(v1, v2);
    assert(VecX(v_add) == 4.0f && VecY(v_add) == 6.0f);  // Esperado: (4.0, 6.0)

    // Teste de subtração de vetores (V2f32)
    V2f32 v_sub = V2f32_sub(v1, v2);
    assert(VecX(v_sub) == -2.0f && VecY(v_sub) == -2.0f);  // Esperado: (-2.0, -2.0)

    // Teste de multiplicação por escalar (V2f32)
    V2f32 v_scale = V2f32_scale(v1, 2.0f);
    assert(VecX(v_scale) == 2.0f && VecY(v_scale) == 4.0f);  // Esperado: (2.0, 4.0)

    // Teste de produto escalar (V2f32)
    f32 dot = V2f32_dot(v1, v2);
    assert(dot == 11.0f);  // Esperado: 11.0

    // Teste de vetores 3D (V3f32)
    V3f32 v3 = {.components = {1.0f, 2.0f, 3.0f}};
    V3f32 v4 = {.components = {4.0f, 5.0f, 6.0f}};
    V3f32 v3_add = V3f32_add(v3, v4);
    assert(VecX(v3_add) == 5.0f && VecY(v3_add) == 7.0f && VecZ(v3_add) == 9.0f);  // Esperado: (5.0, 7.0, 9.0)

    // Teste de vetores 4D (V4f32)
    V4f32 v5 = {.components = {1.0f, 2.0f, 3.0f, 4.0f}};
    V4f32 v6 = {.components = {5.0f, 6.0f, 7.0f, 8.0f}};
    V4f32 v4_add = V4f32_add(v5, v6);
    assert(VecX(v4_add) == 6.0f && VecY(v4_add) == 8.0f && VecZ(v4_add) == 10.0f && VecW(v4_add) == 12.0f);  // Esperado: (6.0, 8.0, 10.0, 12.0)
}

// Testes para vetores de inteiros
void test_int_vec_operations() {
    // Teste de adição de vetores (V2i32)
    V2i32 iv1 = {.components = {1, 2}};
    V2i32 iv2 = {.components = {3, 4}};
    V2i32 iv_add = V2i32_add(iv1, iv2);
    assert(VecX(iv_add) == 4 && VecY(iv_add) == 6);  // Esperado: (4, 6)

    // Teste de subtração de vetores (V2i32)
    V2i32 iv_sub = V2i32_sub(iv1, iv2);
    assert(VecX(iv_sub) == -2 && VecY(iv_sub) == -2);  // Esperado: (-2, -2)

    // Teste de multiplicação por escalar (V2i32)
    V2i32 iv_scale = V2i32_scale(iv1, 2);
    assert(VecX(iv_scale) == 2 && VecY(iv_scale) == 4);  // Esperado: (2, 4)
}

void vec_test() {
    test_int_vec_operations();
    test_vec_operations();
}

#endif /* VEC_TEST_H */