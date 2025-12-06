#cmake_minimum_required(VERSION 3.22)
#project(imgui)

#set(CMAKE_CXX_STANDARD 23)

# ----------------------------------------------------------------------------

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)

# Core ImGui files
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)

set(IMGUI_HEADERS  # variable not used
        ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imgui_internal.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_DIR}/imstb_rectpack.h
        ${IMGUI_DIR}/imstb_textedit.h
        ${IMGUI_DIR}/imstb_truetype.h
)

# Choose which backend(s) you need based on your rendering system
# For OpenGL3 + your existing windowing system:
set(IMGUI_BACKEND_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        # ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
        # ${IMGUI_DIR}/backends/imgui_impl_wgpu.cpp
        # ${IMGUI_DIR}/backends/imgui_impl_sdlgpu3_shaders.h
        # ${IMGUI_DIR}/backends/imgui_impl_metal.mm
        #
        # Add your platform backend:
        # ${IMGUI_DIR}/backends/imgui_impl_android.cpp
        # ${IMGUI_DIR}/backends/imgui_impl_win32.cpp    # Windows
        # ${IMGUI_DIR}/backends/imgui_impl_osx.mm       # macOS
        # ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp     # if using GLFW
)

set(IMGUI_BACKEND_HEADERS  # variable not used
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.h
        ${IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h
        # ${IMGUI_DIR}/backends/imgui_impl_vulkan.h
        # ${IMGUI_DIR}/backends/imgui_impl_wgpu.h
        # ${IMGUI_DIR}/backends/imgui_impl_sdlgpu3_shaders.h
        # ${IMGUI_DIR}/backends/imgui_impl_metal.h
        #
        # Add corresponding headers:
        # ${IMGUI_DIR}/backends/imgui_impl_android.h
        # ${IMGUI_DIR}/backends/imgui_impl_win32.h
        # ${IMGUI_DIR}/backends/imgui_impl_osx.h
        # ${IMGUI_DIR}/backends/imgui_impl_glfw.h
)

# ----------------------------------------------------------------------------

# Create the library
add_library(imgui STATIC
        ${IMGUI_SOURCES}
        ${IMGUI_BACKEND_SOURCES}
)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}                # ${IMGUI_HEADERS}
        ${IMGUI_DIR}/backends       # ${IMGUI_BACKEND_HEADERS}
)

# Link OpenGL if using OpenGL backend
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# Platform-specific linking
if(WIN32)
    target_link_libraries(imgui PUBLIC imm32)
endif()

# ----------------------------------------------------------------------------
