#include "scene_graph.hh"


SceneGraph::iterator SceneGraph::begin(void){
    return vpRenderComponents.begin();
}

SceneGraph::iterator SceneGraph::end(void){
    return vpRenderComponents.end();
}

void SceneGraph::addRenderComponent(RenderComponent* pComponent){
    vpRenderComponents.push_back(pComponent);
}

//most likely not needed as every component adds itself
/*void SceneGraph::addRenderComponents(tbb::concurrent_vector<RenderComponent*>& vpComponents){
    for (auto it = vpComponents.begin(); it != vpComponents.end(); it++) {
        vpRenderComponents.push_back(*it);
    }
}*/

/*void SceneGraph::deleteRenderComponent(RenderComponent* pRenderComponent){
    for (auto it = vpRenderComponents.begin(); it != vpRenderComponents.end(); it++){
        if (*it == pRenderComponent){
            vpRenderComponents.erase(it);
            return;
        }
    }
}*/
