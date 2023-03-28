__kernel void shrink(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x/4] = input[x];
}

__kernel void grayscale_rgba(__global unsigned char* input, __global unsigned char* output) {
    output[0] = input[0] * 0.2126 + input[1] * 0.7152 + input[2] * 0.0722;
}