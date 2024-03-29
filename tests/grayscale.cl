bool is_alpha_channel(int x) {
    return x % 4 == 3;
}

__kernel void shrink(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    output[x/4] = input[x];
}

__kernel void grayscale_rgba(__global unsigned char* input, __global unsigned char* output) {
    int x = get_global_id(0);
    unsigned char grayscale = input[x/4 * 4] * 0.2126 + 
                                input[x/4 * 4 + 1] * 0.7152 + 
                                input[x/4 * 4 + 2] * 0.0722;
    output[x] = grayscale;

    if (is_alpha_channel(x)) {
        output[x] = input[x];
    }

}
