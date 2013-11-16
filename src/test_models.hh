#ifndef TEST_MODELS_HH
#define TEST_MODELS_HH


#include <GL/GLEW.h>


namespace test {

    GLuint makeCube(GLuint&, GLuint&, GLuint&);

    int makeUVSphere(
                     GLuint&,
                     GLuint&,
                     GLuint&,
                     size_t&,
                     const unsigned int,
                     const unsigned int
                     );

} // namespace test


#endif // TEST_MODELS_HH
