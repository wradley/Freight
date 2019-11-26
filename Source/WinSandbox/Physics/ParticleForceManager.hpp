#pragma once
#include "Freight/pch.hpp"
#include "Particle.hpp"

/*
    Manager does not own any pointers. You are responsible for deleting them.
*/
class ParticleForceManager
{
public:

    ParticleForceManager();
    ~ParticleForceManager();

    void addGenerator(ParticleForceGenerator *g, Particle *p);
    void removeGenerator(ParticleForceGenerator *g, Particle *p);
    void removeGeneratorsFor(Particle *p);
    void removeAllGenerators();

    void update(fr::Real deltaTime);

private:

    struct GeneratorParticlePair
    { 
        ParticleForceGenerator *generator;
        Particle *particle;
    };

    std::vector<GeneratorParticlePair> mGenerators;

    void removePairAt(std::vector<GeneratorParticlePair>::iterator it);

};