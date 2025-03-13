#include "GSC_Lib.h"


int main() {
    Vec v1 = vec_init(3, VT_F32);
    Vec res = vec_init(3, VT_F32);

    // Preenche v1 com alguns valores
    f32* data = (f32*)v1.data;
    data[0] = 1.0f;
    data[1] = 2.0f;
    data[2] = 3.0f;

    // Define o escalar
    f32 scalar = 2.5f;

    // Multiplica v1 pelo escalar e armazena o resultado em res
    vec_mul_scalar(&res, &v1, &scalar);

    // Exibe o resultado
    for (usize i = 0; i < res.dim; i++) {
        printf("%f ", ((f32*)res.data)[i]);
    }
    // Saída esperada: 2.500000 5.000000 7.500000
    return 0;
    return 0;
}