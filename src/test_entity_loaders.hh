#ifndef TEST_ENTITY_LOADERS_HH
#define TEST_ENTITY_LOADERS_HH

class Texture;
class Shader;
class Material;
class Mesh;


namespace Test
{
    class TestEntityLoader{
    public:
        TestEntityLoader(void){}
        ~TestEntityLoader(void);

        void loadEntities(void);
    private:
        Texture* pTexture;
        Shader* pShader;
        Material* pMaterial;
        Mesh* pMesh;
    };
} //namespace Test


#endif // TEST_ENTITY_LOADERS_HH
