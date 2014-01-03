#ifndef RESOURCE_HH
#define RESOURCE_HH


class ResourceInfo {
public:
    virtual ~ResourceInfo(void) {};
};


class Resource {
public:
    virtual Resource* getPtr(void) const = 0;
    virtual bool load(void) = 0;
};


#endif // RESOURCE_HH
