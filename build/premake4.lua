solution "mortified"
    configurations { "debug", "release" }

    project "mortified"
        kind "ConsoleApp"
        language "C++"
        files { "../src/**.hpp", "../src/**.cpp" }
        includedirs {
            "../src/**", "../ext/boost/include", "../ext/Box2D/include",
            "../ext/elemel/include", "../ext/rapidxml/include",
            "../ext/SDL/include"
        }
        libdirs { "../ext/Box2D/lib", "../ext/SDL/lib" }
        links { "Box2D", "SDL", "SDL_image", "SDL_mixer", "SDL_ttf" }
        defines { "GL_GLEXT_PROTOTYPES" }

        configuration "debug"
           defines { "DEBUG" }
           flags { "Symbols" }
           targetdir "bin/debug"

        configuration "release"
           defines { "NDEBUG" }
           flags { "Optimize" }
           targetdir "bin/release"

        configuration "macosx"
           links { "OpenGL.framework" }
