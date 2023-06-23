#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

// 컴포넌트 추상 클래스
class Component {
public:
    virtual ~Component() {}
    virtual void update(float deltaTime) = 0;
};

// 컴포넌트 클래스들
class ComponentA : public Component {
public:
    void update(float deltaTime) override {
        std::cout << "Component A updated" << std::endl;
    }
};

class ComponentB : public Component {
public:
    void update(float deltaTime) override {
        std::cout << "Component B updated" << std::endl;
    }
};

class ComponentC : public Component {
public:
    void update(float deltaTime) override {
        std::cout << "Component C updated" << std::endl;
    }
};

// 엔티티 클래스
class Entity {
private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

public:
    template <typename T, typename... Args>
    void addComponent(Args&&... args) {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    T* getComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    void update(float deltaTime) {
        for (auto& component : components) {
            component.second->update(deltaTime);
        }
    }
};

// 시스템 클래스들
class SystemA {
private:
    std::vector<Entity*> entities;

public:
    void registerEntity(Entity* entity) {
        entities.push_back(entity);
    }

    void update(float deltaTime) {
        for (auto entity : entities) {
            ComponentA* componentA = entity->getComponent<ComponentA>();
            ComponentB* componentB = entity->getComponent<ComponentB>();

            if (componentA && componentB) {
                componentA->update(deltaTime);
                componentB->update(deltaTime);
            }
        }
    }
};

class SystemB {
private:
    std::vector<Entity*> entities;

public:
    void registerEntity(Entity* entity) {
        entities.push_back(entity);
    }

    void update(float deltaTime) {
        for (auto entity : entities) {
            ComponentA* componentA = entity->getComponent<ComponentA>();
            ComponentC* componentC = entity->getComponent<ComponentC>();

            if (componentA && componentC) {
                componentA->update(deltaTime);
                componentC->update(deltaTime);
            }
        }
    }
};

int main() {
    // 엔티티 생성
    Entity entity1;
    Entity entity2;

    // 엔티티에 컴포넌트 추가
    entity1.addComponent<ComponentA>();
    entity1.addComponent<ComponentB>();
    entity2.addComponent<ComponentA>();
    entity2.addComponent<ComponentC>();

    // 시스템 생성
    SystemA systemA;
    SystemB systemB;

    // 시스템에 엔티티 등록
    systemA.registerEntity(&entity1);
    systemA
