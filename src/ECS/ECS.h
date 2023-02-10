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

class Component
{

};

class Entity
{
    private:
        int id;

    public:
        Entity(int id) : id(id) {};
        int GetId() const;
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
        Signature& GetComponentSignature() const;
};

class Registry
{

};

#endif