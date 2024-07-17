#include "serialize.hpp"

using namespace ASST;
struct Component {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("type", type);
    }

    string type = "invalid";
};
struct CameraComponent : public Component {
    CameraComponent()
        : Component({ "camera" }) {}

    template<typename Reflector>
    void reflect(Reflector& reflector) {
        Component::reflect(reflector);
        reflector.record("cameraType", cameraType);
        reflector.record("fov", fov);
        reflector.record("scale", zRange);
    }

    string cameraType = "unknown";
    float fov = 0;
    Array<float, 2> zRange;
};
struct Transform {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("position", position);
        reflector.record("rotation", rotation);
        reflector.record("scale", scale);
    }

    Array<float, 3> position = {};
    Array<float, 3> rotation = {};
    Array<float, 3> scale = {};
};
struct Entity {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("transform", transform);
        reflector.record("components", components);
        reflector.record("children", children);
    }

    Transform transform;
    Map<string, Component> components;
    Map<string, Entity> children;
};
struct Scene {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("name", name);
        reflector.record("root", root);
    }

    string name;
    Entity root;
};
int main() {
    //* serialize
    Scene scene;
    scene.name = "Main Scene";
    Entity cameraEntity;
    cameraEntity.transform.position[2] = -10;
    cameraEntity.components.emplace("CameraComponent", Component({ "camera" }));
    scene.root.children.emplace("Camera", cameraEntity);

    JSONSerializer::serialize("/home/flo/dev/asset/scene.json", scene);

    //* deserialize
    Scene scene2 = JSONSerializer::deserialize<Scene>("/home/flo/dev/asset/scene.json");

    return EXIT_SUCCESS;
}