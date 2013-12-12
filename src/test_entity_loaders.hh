#ifndef TEST_ENTITY_LOADERS_HH
#define TEST_ENTITY_LOADERS_HH


#include "entity_loader.hh"
#include "test_renderers.hh"
#include "test_entities.hh"

#include <vector>


class Texture;
class Shader;
class Material;
class Mesh;


namespace Test {

    class TestEntityLoader : public EntityLoader {
    public:
        TestEntityLoader(void);
        ~TestEntityLoader(void);

        void loadEntities(void);

    private:
        Test::Camera* pCamera;
        Test::TestRenderer* pTestRenderer;
        //Test::Box* pBox;

        std::vector<Test::Edwerd*> vpEdwerdz;
    };

}


#endif // TEST_ENTITY_LOADERS_HH
