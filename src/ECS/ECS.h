#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>

const unsigned int MAX_COMPONENTS = 32;

/* SIGNATURE
   The Signature allows us to keep track of the components of a given entity,
   and also to know which entities a given system is interested in.
*/
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
    protected:
        static int nextId;
};

// Used to assign a unique Id to a component type
template <typename T>
class Component : public IComponent
{
    // Returns the unique Id of Component<T>
    static int GetId()
    {
        static auto id = nextId++;
        return id;
    }
};

class Entity
{
    private:
        int id;

    public:
        Entity(int id) : id(id) {};
        Entity(const Entity& entity) = default;
        int GetId() const;

        Entity& operator =(const Entity& other) = default;
        bool operator ==(const Entity& other) const { return id == other.id; }
        bool operator !=(const Entity& other) const { return id != other.id; }
        bool operator >(const Entity& other) const { return id > other.id; }
        bool operator <(const Entity& other) const { return id < other.id; }
        bool operator >=(const Entity& other) const { return id >= other.id; }
        bool operator <=(const Entity& other) const { return id <= other.id; }
};

/* SYSTEM
   The system is the logic that processes all the entities with a specific signature.
*/
class System
{
    private:
        Signature componentSignature;
        std::vector<Entity> entities;
    
    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        // Defines the component type that entities must have
        // in order to be considered by the system
        template <typename TComponent> void RequireComponent();
};

/* POOL
   A Pool is just a vector (contiguous data) of elements of type T.
*/
class IPool
{
    public:
        virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
    private:
        std::vector<T> data;

    public:
        Pool(int size = 100) { Resize(size); }
        virtual ~Pool() = default;

        bool isEmpty() const { return data.empty(); }
        int GetSize() const { return data.size(); }
        void Resize(int newSize) { data.resize(newSize); }
        void Clear() { data.clear(); }
        void Add(T obj) { data.push_back(obj); }
        void Set(int n, T obj) { data[n] = obj; }
        T& Get(int n) const { return static_cast<T&>(data[n]); }

        T& operator[](int n) const { return data[n]; }
};

/* REGISTRY
   The registry manages the creation and destruction of entities and
   is the responsible for adding systems and components.
*/
class Registry
{
    private:
        int numEntities = 0;

        // Each pool contains all the data for a certain component type
        // Vector index = component type id, Pool index = entity id
        std::vector<IPool*> componentPools;

        // Component signatures (vector index = entity id)
        std::vector<Signature> entityComponentSignature;

        // Map of active systems (index = system type id)
        std::unordered_map<std::type_index, System*> systems;

    public:
        Registry() = default;
        ~Registry() = default;
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif