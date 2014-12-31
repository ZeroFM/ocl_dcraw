#ifdef __cplusplus   
#define EXPORT extern "C" __declspec (dllexport)   
#else   
#define EXPORT __declspec (dllexport)   
#endif   
  
EXPORT int  InterpolateImage(int argc, const char **argv, short** image_ptr, int* width_ptr, int* height_ptr);     
EXPORT int  SaveImage();   
EXPORT int  OclInit();
EXPORT void  CleanUp();

