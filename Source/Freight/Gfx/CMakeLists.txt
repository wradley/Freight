if (NOT WIN32)
    return ()
endif()

target_sources(Freight
    PRIVATE

        _GL/GLShader.cpp
        _GL/GLShader.hpp

        2D/Attachment2D.cpp
        2D/Attachment2D.hpp
        2D/Camera2D.cpp
        2D/Camera2D.hpp
        2D/Env2D.cpp
        2D/Env2D.hpp
        2D/Node2D.cpp
        2D/Node2D.hpp
        2D/Sprite.cpp
        2D/Sprite.hpp
        2D/Text.cpp
        2D/Text.hpp

        3D/Env3D.cpp
        3D/Env3D.hpp

        Resources/FontManager.cpp
        Resources/FontManager.hpp
        Resources/ResourceManager.cpp
        Resources/ResourceManager.hpp
        Resources/TextureManager.cpp
        Resources/TextureManager.hpp 
        
)