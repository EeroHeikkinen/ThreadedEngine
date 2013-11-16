#ifndef SCENE_GRAPH_HH
#define SCENE_GRAPH_HH


#include "component.hh"

#include <vector>


class SceneGraph {
public:
    typedef std::vector<RenderComponent*>::iterator iterator;

    SceneGraph(void) { }
    SceneGraph(const SceneGraph&) = delete;
    ~SceneGraph(void) { }

    iterator begin(void);
    iterator end(void);

    // Adds a new RenderComponent pointer to vpRenderComponents vector.
    void addRenderComponent(RenderComponent*);
    // Seeks for given RenderComponent pointer and if found, deletes it.
    // Automagically called by RenderComponent's destructor.
    void deleteRenderComponent(RenderComponent*);

    SceneGraph& operator=(const SceneGraph&) = delete;

private:
    std::vector<RenderComponent*> vpRenderComponents;
};


#endif // SCENE_GRAPH_HH
