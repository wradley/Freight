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


void LoadComponents(const nlohmann::json &json, fr::EntID ent, fr::EventManager &em)
{
    for (auto &compJson : json["components"]) {
        // create component event
        if (compJson["component-type"].get<fr::String>() == "model") {
            auto evnt = new AddModelComponentEvent;
            evnt->entity = ent;
            evnt->meshFp = compJson["mesh"].get<fr::String>();
            evnt->colorFP = compJson["material"]["color"].get<fr::String>();
            if (compJson.find("transform") != compJson.end())
                evnt->transform = LoadTransform(compJson["transform"]);
            em.post<AddModelComponentEvent>(std::shared_ptr<const AddModelComponentEvent>(evnt));
        }

        else if (compJson["component-type"].get<fr::String>() == "camera") {
            auto evnt = new AddCameraComponentEvent;
            evnt->entity = ent;
            evnt->nearPlane = compJson["near-plane"].get<fr::Real>();
            evnt->farPlane = compJson["far-plane"].get<fr::Real>();
            evnt->fieldOfViewY = compJson["field-of-view-y"].get<fr::Real>();
            if (compJson.find("transform") != compJson.end())
                evnt->transform = LoadTransform(compJson["transform"]);
            em.post<AddCameraComponentEvent>(std::shared_ptr<const AddCameraComponentEvent>(evnt));
        }

        else if (compJson["component-type"].get<fr::String>() == "collider") {
            auto evnt = new AddColliderComponentEvent;
            evnt->entity = ent;
            if (compJson.find("transform") != compJson.end())
                evnt->transform = LoadTransform(compJson["transform"]);
            if (compJson["type"].get<fr::String>() == "box")
                evnt->type = AddColliderComponentEvent::ColliderType::BOX;
            else
                evnt->type = AddColliderComponentEvent::ColliderType::NIL;
            em.post<AddColliderComponentEvent>(std::shared_ptr<const AddColliderComponentEvent>(evnt));
        }

        else if (compJson["component-type"].get<fr::String>() == "particle") {
            auto evnt = new AddParticleComponentEvent;
            evnt->entity = ent;
            if (compJson.find("inverse-mass") != compJson.end())
                evnt->inverseMass = compJson["inverse-mass"].get<fr::Real>();

            for (auto &genJson : compJson["generators"]) {
                if (genJson["type"].get<fr::String>() == "spring") {
                    AddParticleForceGeneratorsEvent::Generator gen;
                    gen.entity = ent;
                    gen.type = AddParticleForceGeneratorsEvent::SPRING_GENERATOR;
                    gen.spring.restLength = genJson["rest-length"].get<fr::Real>();
                    gen.spring.springConstant = genJson["spring-constant"].get<fr::Real>();
                    gen.spring.source = genJson["source"].get<fr::EntID>();
                    evnt->addForceGenerators.generators.push_back(gen);
                }
            }

            em.post<AddParticleComponentEvent>(std::shared_ptr<const AddParticleComponentEvent>(evnt));
        }
    }
}


void ReplaceParameters(nlohmann::json &entJson, const nlohmann::json &parameters)
{
    if (entJson.is_string()) {
        fr::String str = entJson.get<fr::String>();
        if (str.size() > 0 && str[0] == '$') {
            if (parameters.find(str) != parameters.end())
                entJson = parameters[str];
        }
    }

    if (!entJson.is_array() && !entJson.is_object()) return;

    for (auto &child : entJson) {
        ReplaceParameters(child, parameters);
    }
}


void LoadEntities(const nlohmann::json &json, fr::EventManager &em)
{
    //static fr::EntID nextID = 0;

    for (auto &entJson : json) {
        // create ent event
        auto evnt = new AddEntityEvent;
        evnt->entity = entJson["ent-id"].get<fr::EntID>();
        evnt->parent = evnt->entity;
        if (entJson.find("transform") != entJson.end())
            evnt->transform = LoadTransform(entJson["transform"]);

        if (entJson.find("tags") != entJson.end()) {
            for (auto &tagJson : entJson["tags"]) {
                evnt->tags.push_back(tagJson.get<fr::String>());
            }
        }

        em.post<AddEntityEvent>(std::shared_ptr<const AddEntityEvent>(evnt));

        nlohmann::json entInstJson;
        if (entJson.find("file") != entJson.end()) {
            fr::Filepath fp(entJson["file"].get<std::string>());
            std::ifstream ifs(fp.absolutePath());
            fr::String content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            entInstJson = nlohmann::json::parse(content);
            if (entJson.find("parameters") != entJson.end()) {
                ReplaceParameters(entInstJson, entJson["parameters"]);
            }
        }

        LoadComponents(entInstJson, entJson["ent-id"].get<fr::EntID>(), em);
    }

    int test = 1 + 2;
}


void LevelLoader::load(const fr::Filepath &filename)
{
    std::ifstream ifs(filename.absolutePath());
    fr::String content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    
    nlohmann::json json = nlohmann::json::parse(content);

    LoadEntities(json["ents"], fr::EventManager::Instance());
}

