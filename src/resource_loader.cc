#include "resource_loader.hh"
#include "device.hh"
#include "make_unique.hh"
#include "test_models.hh" // TEMP


void StandardResourceLoader::addResourceInfo(const std::string& id, ResourceInfo& info) {
    if (id == "") {
        /*
        TODO
        Throw an exception (resource loading failed)
        */
        return; // TEMP
    }

    for (auto resStruct : vResStructs) {
        if (resStruct.id == id) {
            /*
            TODO
            Throw an exception (resource loading failed)
            */
            return; // TEMP
        }
    }

    ResStruct newResStruct(id, std::unique_ptr<Resource>(nullptr), info);
    vResStructs.push_back(newResStruct);
}

void StandardResourceLoader::loadResource(const std::string& id) {

    auto it = vResStructs.begin();
    for (; it != vResStructs.end(); it++) {
        if (it->id == id) {
            std::unique_ptr<Resource> pNewRes = make_unique<Resource>();
            it->pRes = std::move(pNewRes);
        }
    }

    if (it == vResStructs.end()) {
        /*
        TODO
        Throw an exception (resource loading failed)
        */
    }
}
