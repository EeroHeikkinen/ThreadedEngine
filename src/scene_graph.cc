#include "scene_graph.hh"


SceneGraph::iterator SceneGraph::begin(void){
    return vpRenderComponents.begin();
}

SceneGraph::iterator SceneGraph::end(void){
    return vpRenderComponents.end();
}

void SceneGraph::addRenderComponent(RenderComponent* pRenderComponent){
    vpRenderComponents.push_back(pRenderComponent);
}

void SceneGraph::deleteRenderComponent(RenderComponent* pRenderComponent){
    for (auto it = vpRenderComponents.begin(); it != vpRenderComponents.end(); it++){
        if (*it == pRenderComponent){
            vpRenderComponents.erase(it);
            return;
        }
    }
}
