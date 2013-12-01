#ifndef SCENE_GRAPH_HH
#define SCENE_GRAPH_HH

#include "component.hh"

#include <tbb/tbb.h>


class SceneGraph{
public:
    typedef tbb::concurrent_vector<RenderComponent*>::iterator iterator;

    SceneGraph(void){}
    ~SceneGraph(void){}

    iterator begin(void);
    iterator end(void);

    // Adds a new RenderComponent pointer to vpRenderComponents vector.
    void addRenderComponent(RenderComponent*);
    void addRenderComponents(tbb::concurrent_vector<RenderComponent*>&);
    //void deleteRenderComponent(RenderComponent*);
    /*
    TODO
    implement properly
    */


    SceneGraph(const SceneGraph&) = delete;
    SceneGraph& operator=(const SceneGraph&) = delete;
private:
    tbb::concurrent_vector<RenderComponent*> vpRenderComponents;
};


#endif // SCENE_GRAPH_HH
