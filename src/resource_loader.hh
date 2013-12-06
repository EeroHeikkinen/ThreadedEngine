#ifndef RESOURCE_LOADER_HH
#define RESOURCE_LOADER_HH


#include <tbb/tbb.h>


class Texture;
class Shader;
class Material;
class Mesh;


class ResourceLoader {
public:
    ResourceLoader(void);



protected:
    void addTexture(Texture* texture);
    void addShader(Shader* shader);
    void addMaterial(Material* material);
    void addMesh(Mesh* mesh);

private:
    tbb::concurrent_vector<Texture*> vpTextures;
    tbb::concurrent_vector<Shader*> vpShaders;
    tbb::concurrent_vector<Material*> vpMaterials;
    tbb::concurrent_vector<Mesh*> vpMeshes;
};


#endif // RESOURCE_LOADER_HH
