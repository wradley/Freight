target_sources(${CURR_APP_NAME}
    PRIVATE
        Collision/Collider.hpp
        Collision/CollisionDetector.cpp
        Collision/CollisionDetector.hpp
        Collision/Contact.cpp
        Collision/Contact.hpp

        ForceGenerator.cpp
        ForceGenerator.hpp
        Particle.cpp
        Particle.hpp
        ParticleForceManager.cpp
        ParticleForceManager.hpp
        PhysicsEvents.hpp
        PhysicsSystem.cpp
        PhysicsSystem.hpp
        Rigidbody.cpp
        Rigidbody.hpp
)