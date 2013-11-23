#ifndef TEST_RESOURCE_LOADERS_HH
#define TEST_RESOURCE_LODAERS_HH


#include "resource_loader.hh"
#include "test_renderers.hh"
#include "test_entities.hh"

#include <vector>


namespace Test {

    class TestResourceLoader : public ResourceLoader {
    public:
        TestResourceLoader(void);
        ~TestResourceLoader(void);

        void loadResources(void);

    private:
        Test::Camera* pCamera;//TEMP
        Test::TestRenderer* pTestRenderer;//TEMP
        Test::Sphere* pSphere;//TEMP
        Test::Box* pBox;//TEMP
    };

}


#endif // TEST_RESOURCE_LOADERS_HH
