#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

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

class Registry
{

};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif