__kernel void shrink(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x/4] = input[x];
}

__kernel void grayscale_rgba(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x] = input[x];
}