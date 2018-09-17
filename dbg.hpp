#ifndef DBG_HPP
#define DBG_HPP

#include <iostream>
#include <stdio.h>
#include <vector>

#ifdef NO_DEBUG
#define dbg(M, ...)
#else

#define debug(M, ...) {\
    fprintf(stderr, "DEBUG %s:%d: ", __FILE__, __LINE__);\
    fprintf(stderr, M, ##__VA_ARGS__);\
    fprintf(stderr, "\n");\
}

#endif // NO_DEBUG

template <class T>
void print_vector(std::vector<T> v){
    for (uint i = 0; i < v.size(); i++)
        std::cout << v[i] << std::endl;
}

#endif // DBG_HPP
