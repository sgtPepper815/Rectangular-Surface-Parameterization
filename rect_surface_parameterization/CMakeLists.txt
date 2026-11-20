# CMakeList.txt: CMake-Projekt für "rect_surface_parameterization". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (rect_surface_parameterization "main.cpp" "glfwbuilder.h" "settings.h" "shader.h" "model.h" "renderer.h" "parameterization.h" "vec.h" "parameterization.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rect_surface_parameterization PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.

add_subdirectory(external/glad)
add_subdirectory(external/glfw-3.5.1)
add_subdirectory(external/glm)

target_link_libraries(rect_surface_parameterization PRIVATE glad)
target_link_libraries(rect_surface_parameterization PRIVATE glfw)
target_link_libraries(rect_surface_parameterization PRIVATE glm)

add_custom_command(TARGET rect_surface_parameterization POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shader"
    "${CMAKE_CURRENT_BINARY_DIR}/shader"
)
