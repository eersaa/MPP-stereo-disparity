// OpenCL kernel. Each work item takes care of one element of c
__kernel void vecAdd(  __global double *a,                    
                       __global double *b,                     
                       const unsigned int n)                   
{                                                             
    //Get our global thread ID                                
    int id = get_global_id(0);                                
                                                               
    //Make sure we do not go out of bounds                    
    if (id < n){
        //code here  
        
    }                                        
                                       
} 