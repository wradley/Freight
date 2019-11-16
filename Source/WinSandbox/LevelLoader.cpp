#include "LevelLoader.hpp"
#include <json.hpp>
#include "LoadEvents.hpp"


LevelLoader::LevelLoader()
{}


LevelLoader::~LevelLoader()
{}


fr::Transform LoadTransform(const nlohmann::json &json)
{
    fr::Transform transform;

    if (json.find("position") != json.end()) {
        transform.position[0] = json["position"][0].get<fr::Real>();
        transform.position[1] = json["position"][1].get<fr::Real>();
        transform.position[2] = json["position"][2].get<fr::Real>();
    }

    if (json.find("rotation") != json.end()) {
        transform.rotation[0] = json["rotation"][0].get<fr::Real>();
        transform.rotation[1] = json["rotation"][1].get<fr::Real>();
        transform.rotation[2] = json["rotation"][2].get<fr::Real>();
        transform.rotation[3] = json["rotation"][3].get<fr::Real>();
    }

    if (json.find("scale") != json.end()) {
        transform.scale[0] = json["scale"][0].get<fr::Real>();
        transform.scale[1] = json["scale"][1].get<fr::Real>();
        transform.scale[2] = json["scale"][2].get<fr::Real>();
    }

    return transform;
}


void LoadComponents(const fr::Filepath &fp, EntID ent, fr::EventManager &em)
{
    std::ifstream ifs(fp.absolutePath());
    fr::String content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    nlohmann::json json = nlohmann::json::parse(content);

    auto test = json.dump();

    for (auto &compJson : json["components"]) {
        // create component event
        if (compJson["component-type"].get<fr::String>() == "model") {
            auto evnt = new LoadModelComponentEvent;
            evnt->entity = ent;
            evnt->meshFp = compJson["mesh"].get<fr::String>();
            evnt->colorFP = compJson["material"]["color"].get<fr::String>();
            if (compJson.find("transform") != compJson.end())
                evnt->transform = LoadTransform(compJson["transform"]);
            em.post<LoadModelComponentEvent>(std::shared_ptr<const LoadModelComponentEvent>(evnt));
        }

        else if (compJson["component-type"].get<fr::String>() == "camera") {
            auto evnt = new LoadCameraComponentEvent;
            evnt->entity = ent;
            evnt->nearPlane = compJson["near-plane"].get<fr::Real>();
            evnt->farPlane = compJson["far-plane"].get<fr::Real>();
            evnt->fieldOfViewY = compJson["field-of-view-y"].get<fr::Real>();
            if (compJson.find("transform") != compJson.end())
                evnt->transform = LoadTransform(compJson["transform"]);
            em.post<LoadCameraComponentEvent>(std::shared_ptr<const LoadCameraComponentEvent>(evnt));
        }

        else if (compJson["component-type"].get<fr::String>() == "collider") {
            auto evnt = new LoadColliderComponentEvent;
            evnt->entity = ent;
            if (compJson.find("transform") != compJson.end())
                evnt->transform = LoadTransform(compJson["transform"]);
            if (compJson["type"].get<fr::String>() == "box")
                evnt->type = LoadColliderComponentEvent::ColliderType::BOX;
            else
                evnt->type = LoadColliderComponentEvent::ColliderType::NIL;
            em.post<LoadColliderComponentEvent>(std::shared_ptr<const LoadColliderComponentEvent>(evnt));
        }
    }
}


void LoadEntities(const nlohmann::json &json, fr::EventManager &em)
{
    static EntID nextID = 0;

    for (auto &entJson : json) {
        // create ent event
        auto evnt = new LoadEntityEvent;
        evnt->entity = nextID;
        evnt->parent = evnt->entity;
        if (entJson.find("transform") != entJson.end())
            evnt->transform = LoadTransform(entJson["transform"]);

        if (entJson.find("tags") != entJson.end()) {
            for (auto &tagJson : entJson["tags"]) {
                evnt->tags.push_back(tagJson.get<fr::String>());
            }
        }

        em.post<LoadEntityEvent>(std::shared_ptr<const LoadEntityEvent>(evnt));
        LoadComponents(entJson["file"].get<std::string>(), nextID++, em);
    }
}


void LevelLoader::load(const fr::Filepath &filename)
{
    std::ifstream ifs(filename.absolutePath());
    fr::String content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    
    nlohmann::json json = nlohmann::json::parse(content);

    LoadEntities(json["ents"], fr::EventManager::Instance());
}

