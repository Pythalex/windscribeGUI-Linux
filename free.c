#include "free.h"

void s_free(void* ptr){
    if (ptr)
        free(ptr);
}

void s_free_2D_array(void** ptr, int length){
    if (ptr) {
        for (int i = 0; i < length; i++){
            s_free(ptr[i]);
        }
        // NULL ptr already checked
        free(ptr);
    }
}