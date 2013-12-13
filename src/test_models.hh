#ifndef TEST_MODELS_HH
#define TEST_MODELS_HH

#include <GL/GLEW.h>


namespace Test{
    void makeBox(GLuint& VBO_,
                 GLuint& IBO_,
                 GLuint& VAO_,
                 unsigned int& numIndices_,
                 float xSize,
                 float ySize,
                 float zSize);

    void makeUVSphere(GLuint& VBO_,
                     GLuint& IBO_,
                     GLuint& VAO_,
                     unsigned int& numIndices_,
                     const unsigned int numSegments,
                     const unsigned int numRings);

} // namespace Test


#endif // TEST_MODELS_HH
