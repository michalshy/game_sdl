#include "editor.h"

#include "imgui.h"
#include "backends/imgui_impl_sdlrenderer2.h"

bool Editor::Init(SDL_Window* window, SDL_Renderer* renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    return true;
}

void Editor::OnFrame()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Editor::Run()
{
    if (m_Demo) ImGui::ShowDemoWindow(&m_Demo);
}

void Editor::PreRender()
{
    ImGui::Render();
}

void Editor::PostRender()
{
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void Editor::Exit()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Editor::PollEvents(SDL_Event& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

