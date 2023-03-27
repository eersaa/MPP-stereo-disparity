__kernel void grayscale(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x/4] = input[x];
}

__kernel void grayscale_rg(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x/4] = (unsigned char)input[x] * 0.2126;
}