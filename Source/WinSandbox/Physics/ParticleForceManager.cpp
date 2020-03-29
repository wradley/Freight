#include "ParticleForceManager.hpp"


ParticleForceManager::ParticleForceManager()
{
}


ParticleForceManager::~ParticleForceManager()
{
}


void ParticleForceManager::addGenerator(ParticleForceGenerator *g, Particle *p)
{
    GeneratorParticlePair gpp;
    gpp.generator = g;
    gpp.particle = p;
    mGenerators.push_back(gpp);
}


void ParticleForceManager::removeGenerator(ParticleForceGenerator *g, Particle *p)
{
    for (auto it = mGenerators.begin(); it != mGenerators.end(); ++it) {
        if (it->generator == g && it->particle == p) {
            removePairAt(it);
        }
    }
}


void ParticleForceManager::removeGeneratorsFor(Particle *p)
{
    for (auto it = mGenerators.begin(); it != mGenerators.end(); ++it) {
        if (it->particle == p) {
            removePairAt(it);
        }
    }
}


void ParticleForceManager::removeAllGenerators()
{
    mGenerators.clear();
}


void ParticleForceManager::update(fr::Real dt)
{
    // apply forces
    for (auto &[g, p] : mGenerators)
        g->update(p, dt);

    // integrate particles and remove finished generators
    for (auto it = mGenerators.begin(); it != mGenerators.end(); ++it) {
        it->particle->integrate(dt);
        if (it->generator->isFinished()) {
            removePairAt(it);
        }
    }
}


void ParticleForceManager::removePairAt(std::vector<GeneratorParticlePair>::iterator it)
{
    if (std::next(it) != mGenerators.end()) // if not last element
        *it = *std::prev(mGenerators.end()); // swap
    mGenerators.pop_back();
}
