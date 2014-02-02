#ifndef RESOURCE_LOADER_HH
#define RESOURCE_LOADER_HH

#include "resource.hh"

#include <string>
#include <memory>
#include <vector>


class ResourceLoader{
public:
    ResourceLoader(void) {}
    virtual ~ResourceLoader(void) {}

    virtual void addResourceInfo(const std::string& id, ResourceInfo& info) = 0;
    virtual void loadResource(const std::string& id = "") = 0;

    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;

protected:
    struct ResStruct {
        std::string id;
        std::unique_ptr<Resource> pRes;
        ResourceInfo info;

        ResStruct(const std::string& id_, std::unique_ptr<Resource> pRes_, ResourceInfo& info_) :
            id(id_), pRes(std::move(pRes_)), info(info_)
            {}
    };

    std::vector<ResStruct> vResStructs;
};


class StandardResourceLoader : public ResourceLoader {
public:
    void addResourceInfo(const std::string& id, ResourceInfo& info);
    void loadResource(const std::string& id = "");
};


#endif //RESOURCE_LOADER_HH
