#ifndef TEST_RESOURCE_LOADERS_HH
#define TEST_RESOURCE_LOADERS_HH

#include "resource_loader.hh"


namespace Test {

    class TestResourceLoader : public ResourceLoader {
    public:
        TestResourceLoader(void) {}

        bool loadFromTXT(const std::string& fileName);
    };

}


#endif // TEST_RESOURCE_LOADERS_HH
