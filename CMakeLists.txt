cmake_minimum_required(VERSION 2.6)
project (FRONTIERENGINE)

include_directories(
	src
	contrib/glm
	contrib/stb_image
	contrib/tinyobj
)


if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
    contrib/msvc-windows-x86/openal-soft/include
    contrib/msvc-windows-x86/ogg/include
    contrib/msvc-windows-x86/vorbis/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/ogg/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/vorbis/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(game
	src/game/main.cpp
	src/game/asteroidbehavior.cpp
	src/game/asteroidbehavior.h
	src/game/PlayerController.cpp
	src/game/PlayerController.h
	src/game/ProjectileBehavior.cpp
	src/game/ProjectileBehavior.h
	src/game/AsteroidSpawner.cpp
	src/game/AsteroidSpawner.h
)

add_library(frontier

	src/myengine/Camera.cpp
	src/myengine/Camera.h
	src/myengine/Core.cpp
	src/myengine/Core.h
	src/myengine/Entity.cpp
	src/myengine/Entity.h
	src/myengine/Component.cpp
	src/myengine/Component.h
	src/myengine/Input.cpp
	src/myengine/Input.h
	src/myengine/Environment.cpp
	src/myengine/Environment.h
	src/myengine/Timer.cpp
	src/myengine/Timer.h
	src/myengine/MeshRenderer.cpp
	src/myengine/MeshRenderer.h
	src/myengine/Resource.cpp
	src/myengine/Resource.h
	src/myengine/Resources.cpp
	src/myengine/Resources.h
	src/myengine/Shader.cpp
	src/myengine/Shader.h
	src/myengine/Texture.cpp
	src/myengine/Texture.h
	src/myengine/Transform.cpp
	src/myengine/Transform.h
	src/myengine/MyEngine.h
	src/myengine/Mesh.cpp
	src/myengine/Mesh.h
	src/myengine/Model.cpp
	src/myengine/Model.h
	src/myengine/Sound.cpp
	src/myengine/Sound.h
	src/myengine/AudioPlayer.cpp
	src/myengine/AudioPlayer.h
	src/myengine/Skybox.cpp
	src/myengine/Skybox.h
	src/myengine/CubemapTexture.cpp
	src/myengine/CubemapTexture.h
	src/myengine/Collider.cpp
	src/myengine/Collider.h
	src/myengine/UIImage.cpp
	src/myengine/UIImage.h
	src/myengine/UIButton.cpp
	src/myengine/UIButton.h
	src/myengine/Prefab.cpp
	src/myengine/Prefab.h
	src/myengine/Pooler.cpp
	src/myengine/Pooler.h
)

if(MSVC)
  target_link_libraries(frontier
    SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile
  )
else()
  target_link_libraries(frontier
    SDL2 GLU GLEW GL AL ogg vorbis vorbisfile
  )
endif()

target_link_libraries(game frontier)

ADD_DEPENDENCIES(game frontier)

if(MSVC)
  add_custom_command(TARGET frontier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:frontier>"
  )

  add_custom_command(TARGET frontier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:frontier>"
  )

  add_custom_command(TARGET frontier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/bin/OpenAL32.dll"
      "$<TARGET_FILE_DIR:frontier>"
  )
endif()


