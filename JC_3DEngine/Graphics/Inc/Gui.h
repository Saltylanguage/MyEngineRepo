//====================================================================================================
// Filename:	Gui.h
// Created by:	Peter Chan
//====================================================================================================

#pragma once
#include <Externals\ImGui\Inc\imgui.h>

namespace Graphics {
namespace Gui {

void Initialize(HWND window);
void Terminate();
void BeginRender(float deltaTime);
void EndRender();

} // namespace Gui
} // namespace Graphics