#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Author: Inan Evin
# www.inanevin.com
# 
# Copyright (C) 2018 Inan Evin
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
# and limitations under the License.
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.6)
project(LinaEditor)

#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------

set(LINAEDITOR_SOURCES 

# Core
src/Core/EditorApplication.cpp
src/Core/GUILayer.cpp
src/Core/EditorCommon.cpp
src/Core/CentralDockingSpace.cpp
src/Core/ShortcutManager.cpp
src/Core/ImGuiCommon.cpp


# ECS
src/ECS/Systems/EditorCameraSystem.cpp

#Drawers
src/Drawers/EntityDrawer.cpp
src/Drawers/ComponentDrawer.cpp
src/Drawers/ClassDrawer.cpp
src/Drawers/MaterialDrawer.cpp
src/Drawers/ModelDrawer.cpp
src/Drawers/TextureDrawer.cpp


# Panels
src/Panels/EditorPanel.cpp
src/Panels/EntitiesPanel.cpp
src/Panels/SystemsPanel.cpp
src/Panels/ResourcesPanel.cpp
src/Panels/LevelPanel.cpp
src/Panels/PropertiesPanel.cpp
src/Panels/LogPanel.cpp
src/Panels/HeaderPanel.cpp
src/Panels/ProfilerPanel.cpp
src/Panels/GlobalSettingsPanel.cpp
src/Panels/MainToolbarPanel.cpp
src/Panels/ResourceSelectorPanel.cpp
src/Panels/ProgressPanel.cpp
src/Panels/PreviewPanel.cpp
src/Panels/TextEditorPanel.cpp

# Utility
src/Utility/EditorUtility.cpp

# Widgets
src/Widgets/MenuButton.cpp
src/Widgets/WidgetsUtility.cpp
src/Widgets/ToolbarItem.cpp
src/Widgets/Snackbar.cpp

# ImGui
src/imgui/imgui_impl_opengl3.cpp
src/imgui/imgui_impl_glfw.cpp
src/imgui/imgui.cpp
src/imgui/imgui_demo.cpp
src/imgui/imgui_draw.cpp
src/imgui/imgui_widgets.cpp
src/imgui/imgui_tables.cpp
src/imgui/imguizmo/ImCurveEdit.cpp
src/imgui/imguizmo/ImGradient.cpp
src/imgui/imguizmo/ImGuizmo.cpp
src/imgui/imguizmo/ImSequencer.cpp
src/imgui/implot/implot_demo.cpp
src/imgui/implot/implot.cpp
src/imgui/implot/implot_items.cpp
src/imgui/imguicolortextedit/TextEditor.cpp

)

set_source_files_properties( src/imgui/imgui_impl_opengl3.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imgui_impl_glfw.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imgui.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imgui_demo.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imgui_draw.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imgui_widgets.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imgui_tables.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imguizmo/ImCurveEdit.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imguizmo/ImGradient.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imguizmo/ImGuizmo.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/imguizmo/ImSequencer.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/implot/implot_demo.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/implot/implot.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )
set_source_files_properties( src/imgui/implot/implot_items.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON )

set(LINAEDITOR_HEADERS

# Core
include/Core/GUILayer.hpp
include/Core/EditorCommon.hpp
include/Core/EditorApplication.hpp
include/Core/CustomFontIcons.hpp
include/Core/CentralDockingSpace.hpp
include/Core/ShortcutManager.hpp
include/Core/ImGuiCommon.hpp

# ECS
include/ECS/Systems/EditorCameraSystem.hpp

#Drawers
include/Drawers/EntityDrawer.hpp
include/Drawers/ComponentDrawer.hpp
include/Drawers/ClassDrawer.hpp
include/Drawers/MaterialDrawer.hpp
include/Drawers/ModelDrawer.hpp
include/Drawers/TextureDrawer.hpp

# Panels
include/Panels/MainToolbarPanel.hpp
include/Panels/EditorPanel.hpp
include/Panels/EntitiesPanel.hpp
include/Panels/SystemsPanel.hpp
include/Panels/ResourcesPanel.hpp
include/Panels/LevelPanel.hpp
include/Panels/PropertiesPanel.hpp
include/Panels/LogPanel.hpp
include/Panels/HeaderPanel.hpp
include/Panels/ProfilerPanel.hpp
include/Panels/GlobalSettingsPanel.hpp
include/Panels/ResourceSelectorPanel.hpp
include/Panels/ProgressPanel.hpp
include/Panels/ProgressPanel.hpp
include/Panels/TextEditorPanel.hpp


# Utility
include/Utility/EditorUtility.hpp

# Widgets
include/Widgets/MenuButton.hpp
include/Widgets/WidgetsUtility.hpp
include/Widgets/ToolbarItem.hpp
include/Widgets/Snackbar.hpp

# ImGui
include/imgui/dirent.h
include/imgui/imconfig.h
include/imgui/imgui.h
include/imgui/imgui_impl_glfw.h
include/imgui/imgui_impl_opengl3.h
include/imgui/imgui_impl_opengl3_loader.h
include/imgui/imgui_internal.h
include/imgui/imstb_rectpack.h
include/imgui/imstb_textedit.h
include/imgui/imstb_truetype.h
include/imgui/imguizmo/ImCurveEdit.h
include/imgui/imguizmo/ImGradient.h
include/imgui/imguizmo/ImGuizmo.h
include/imgui/imguizmo/ImSequencer.h
include/imgui/implot/implot.h
include/imgui/implot/implot_internal.h
include/imgui/imguicolortextedit/TextEditor.h

CMakeLists.txt

)

#--------------------------------------------------------------------
# Create executable project
#--------------------------------------------------------------------
add_library(${PROJECT_NAME} ${LINAEDITOR_SOURCES} ${LINAEDITOR_HEADERS})
add_library(Lina::Editor ALIAS ${PROJECT_NAME}) 
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD_MODE BATCH UNITY_BUILD_BATCH_SIZE 16)

#--------------------------------------------------------------------
# Options & Definitions
#--------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/IconFontCPPHeaders/include)

include(../CMake/ProjectSettings.cmake)


#--------------------------------------------------------------------
# Links
#--------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} 
PRIVATE Engine
)

#--------------------------------------------------------------------
# Folder structuring in visual studio
#--------------------------------------------------------------------
if(MSVC_IDE)
	foreach(source IN LISTS LINAEDITOR_HEADERS LINAEDITOR_SOURCES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${LINAEDITOR_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
				source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()