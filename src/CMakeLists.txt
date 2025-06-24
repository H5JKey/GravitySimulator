file(GLOB SOURCES
    "*.cpp"
)

add_executable(GravitySimulator 
    ${SOURCES}
)

target_link_libraries(GravitySimulator PRIVATE ImGui-SFML::ImGui-SFML)

if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET example_exe POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:example_exe>)
  endif()
endif()

