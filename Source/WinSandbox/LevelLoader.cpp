#include "LevelLoader.hpp"
#include <json.hpp>
#include "LoadEvents.hpp"


LevelLoader::LevelLoader(std::shared_ptr<fr::EventManager> em) : mEventManager(em)
{}


LevelLoader::~LevelLoader()
{}


void LoadComponents(const fr::Filepath &fp, EntID ent, std::shared_ptr<fr::EventManager> em)
{
    std::ifstream ifs(fp.absolutePath());
    fr::String content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    nlohmann::json json = nlohmann::json::parse(content);

    auto test = json.dump();

    for (auto &compJson : json["components"]) {
        // create component event
        if (compJson["component-type"].get<std::string>() == "model") {
            auto evnt = new LoadModelComponentEvent;
            evnt->entity = ent;
            evnt->meshFp = compJson["mesh"].get<std::string>();
            evnt->colorFP = compJson["material"]["color"].get<std::string>();
            evnt->transform.position[0] = compJson["transform"]["position"][0];
            evnt->transform.position[1] = compJson["transform"]["position"][1];
            evnt->transform.position[2] = compJson["transform"]["position"][2];
            evnt->transform.rotation[0] = compJson["transform"]["rotation"][0];
            evnt->transform.rotation[1] = compJson["transform"]["rotation"][1];
            evnt->transform.rotation[2] = compJson["transform"]["rotation"][2];
            evnt->transform.rotation[3] = compJson["transform"]["rotation"][3];
            evnt->transform.scale[0] = compJson["transform"]["scale"][0];
            evnt->transform.scale[1] = compJson["transform"]["scale"][1];
            evnt->transform.scale[2] = compJson["transform"]["scale"][2];
            em->post<LoadModelComponentEvent>(std::shared_ptr<const LoadModelComponentEvent>(evnt));
        }
    }
}


void LoadEntities(const nlohmann::json &json, std::shared_ptr<fr::EventManager> em)
{
    static EntID nextID = 0;

    for (auto &entJson : json) {
        // create ent event
        auto evnt = new LoadEntityEvent;
        evnt->entity = nextID;
        evnt->transform.position[0] = entJson["transform"]["position"][0];
        evnt->transform.position[1] = entJson["transform"]["position"][1];
        evnt->transform.position[2] = entJson["transform"]["position"][2];
        evnt->transform.rotation[0] = entJson["transform"]["rotation"][0];
        evnt->transform.rotation[1] = entJson["transform"]["rotation"][1];
        evnt->transform.rotation[2] = entJson["transform"]["rotation"][2];
        evnt->transform.rotation[3] = entJson["transform"]["rotation"][3];
        evnt->transform.scale[0] = entJson["transform"]["scale"][0];
        evnt->transform.scale[1] = entJson["transform"]["scale"][1];
        evnt->transform.scale[2] = entJson["transform"]["scale"][2];
        em->post<LoadEntityEvent>(std::shared_ptr<const LoadEntityEvent>(evnt));
        LoadComponents(entJson["file"].get<std::string>(), nextID++, em);
    }
}


void LevelLoader::load(const fr::Filepath &filename)
{
    std::ifstream ifs(filename.absolutePath());
    fr::String content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    
    nlohmann::json json = nlohmann::json::parse(content);

    LoadEntities(json["ents"], mEventManager);
}

