__kernel void step2k (__global int** mat1, __global int** mat2, __global int** matR)
{
    int matSize = 100;
    //calc result
    for (int i=0; i<matSize; i++) {
        for (int j=0; j<matSize; j++) {
            matR[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

/*
__kernel void helloworld(__global char* in, __global char* out)
{
	int num = get_global_id(0);
	out[num] = in[num] + 1;
}
*/
