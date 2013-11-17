#ifndef TEST_MODELS_HH
#define TEST_MODELS_HH


#include <GL/GLEW.h>


namespace test {

    void makeBox(
                 GLuint& VBO_,
                 GLuint& IBO_,
                 GLuint& VAO_,
                 float xSize,
                 float ySize,
                 float zSize
                 );

    void makeUVSphere(
                     GLuint& VBO_,
                     GLuint& IBO_,
                     GLuint& VAO_,
                     size_t& numIndices_,
                     const unsigned int numSegments,
                     const unsigned int numRings
                     );

} // namespace test


#endif // TEST_MODELS_HH
