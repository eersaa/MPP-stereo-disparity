__kernel void shrink(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x/4] = input[x];
}

__kernel void grayscale_rgba(__global unsigned char* input, __global unsigned char* output) {
    unsigned char grayscale = input[0] * 0.2126 + input[1] * 0.7152 + input[2] * 0.0722;
    int x = get_global_id(0);
    output[x] = grayscale;
    output[3] = input[3];
    output[7] = input[7];

}