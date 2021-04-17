//
// Created by sriney on 4/9/21.
//

#include <iostream>

#define ASSERT(x) if  (!(x)) std::cout << "break";
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();


bool GLLogCall(const char* function, const char* file, int line);
