#include "editor.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

bool Editor::Init(SDL_Window* window, SDL_GLContext* context)
{
    m_Context = context;
    m_Window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    const char* glsl_version = "#version 330";
    
    
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void Editor::OnFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
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
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO& io = ImGui::GetIO(); 
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        // Make sure we restore current context if RenderPlatformWindowsDefault changed it.
        SDL_GL_MakeCurrent(m_Window, m_Context);
    }
}

void Editor::Exit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Editor::PollEvents(SDL_Event& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

