#ifndef TEST_MODELS_HH
#define TEST_MODELS_HH


#include <GL/GLEW.h>


namespace test {

    void makeCube(GLuint&, GLuint&, GLuint&);

    void makeUVSphere(
                     GLuint&,
                     GLuint&,
                     GLuint&,
                     size_t&,
                     const unsigned int,
                     const unsigned int
                     );

} // namespace test


#endif // TEST_MODELS_HH
