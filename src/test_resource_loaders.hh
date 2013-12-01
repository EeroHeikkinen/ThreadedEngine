#ifndef TEST_RESOURCE_LOADERS_HH
#define TEST_RESOURCE_LODAERS_HH


#include "resource_loader.hh"
#include "test_renderers.hh"
#include "test_entities.hh"

#include <vector>


class Texture;
class Shader;
class Material;
class Mesh;


namespace Test {

    class TestResourceLoader : public ResourceLoader {
    public:
        TestResourceLoader(void);
        ~TestResourceLoader(void);

        void loadResources(void);

    private:
        Test::Camera* pCamera;
        Test::TestRenderer* pTestRenderer;
        //Test::Box* pBox;

        Texture* pTexture;
        Shader* pShader;
        Material* pMaterial;
        Mesh* pMesh;

        std::vector<Test::SingleMeshEntity*> vpSingleMeshEntities;
    };

}


#endif // TEST_RESOURCE_LOADERS_HH
