#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_stdlib.h>

#include <nlohmann/json.hpp>

#include <scr/GL.hpp>
#include <scr/Gui.hpp>
#include <scr/Json.hpp>
#include <scr/Project.hpp>
#include <scr/ScratchScript.hpp>
#include <scr/Sprite.hpp>
#include <scr/Window.hpp>

#include <cstdio>

void
gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                          const void *userParam)
{
    fprintf(stderr, "[OpenGL 0x%08X] %s\n", id, message);
    if (type == GL_DEBUG_TYPE_ERROR)
        throw;
}

scr::Project project;

ImTextureID draw_viewport(int width, int height, bool cleanup)
{
    static bool init = false;

    static scr::Framebuffer *fbo;
    static scr::Texture *color;
    static scr::Renderbuffer *depth;

    static scr::VertexArray *vao;
    static scr::Buffer *vbo;
    static scr::Buffer *ibo;
    static scr::Program *program;

    static int prevWidth = 0;
    static int prevHeight = 0;

    static const GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.5f,
                                       -0.5f, 1.0f, 0.0f};
    static const GLuint indices[] = {0, 1, 2, 2, 3, 0};

    if (cleanup)
    {
        delete fbo;
        delete color;
        delete depth;

        delete vao;
        delete vbo;
        delete ibo;
        delete program;

        return 0;
    }

    if (width > 0 && height > 0 && (prevWidth != width || prevHeight != height))
    {
        prevWidth = width;
        prevHeight = height;

        if (init)
        {
            delete depth;

            fbo->Bind();

            color->Bind()->Image2D(0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0)->Unbind();

            depth = new scr::Renderbuffer(GL_RENDERBUFFER);
            depth->Bind()->Storage(GL_DEPTH_COMPONENT, width, height)->Unbind();
            fbo->AddRenderbuffer(GL_DEPTH_ATTACHMENT, depth);

            fbo->Unbind();
        }
    }

    if (!init && width > 0 && height > 0)
    {
        init = true;

        fbo = new scr::Framebuffer(GL_FRAMEBUFFER);
        fbo->Bind();

        color = new scr::Texture(GL_TEXTURE_2D);
        color
                ->Bind()
                ->Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
                ->Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
                ->Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
                ->Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
                ->Image2D(0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0)
                ->Unbind();
        fbo->AddTexture2D(GL_COLOR_ATTACHMENT0, color, 0);

        depth = new scr::Renderbuffer(GL_RENDERBUFFER);
        depth->Bind()->Storage(GL_DEPTH_COMPONENT, width, height)->Unbind();
        fbo->AddRenderbuffer(GL_DEPTH_ATTACHMENT, depth);

        fbo->Unbind();

        vao = new scr::VertexArray();
        vao->Bind();

        vbo = new scr::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
        vbo->Bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));
        vbo->Data(sizeof(vertices), vertices)->Unbind();

        vao->Unbind();

        ibo = new scr::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
        ibo->Bind()->Data(sizeof(indices), indices)->Unbind();

        program = new scr::Program("shaders/sprite.vsh", "shaders/sprite.fsh");
    }

    if (init)
    {
        //
        // TODO:
        // construct model matrix for each sprite:
        //   - scale to fit costume
        //   - scale with size
        //   - rotate with direction
        //   - translate by position // DONE
        // on frame draw each sprite:
        //   - bind costume texture
        //   - set uniform uTexture
        //   - set uniform uM
        //

        fbo->Bind();
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto w2 = width * 0.5f;
        auto h2 = height * 0.5f;
        glm::mat4 proj = glm::ortho(-w2, w2, -h2, h2);

        vao->Bind();
        ibo->Bind();
        program->Bind();

        glUniform1i(program->Uniform("uTexture"), 1);
        glUniformMatrix4fv(program->Uniform("uP"), 1, false, &proj[0][0]);

        for (auto &sprite: project.Sprites)
        {
            if (!sprite.Show || sprite.IsStage)
                continue;

            auto tex = sprite.GetCostume().Tex;
            if (!tex)
                continue;

            glActiveTexture(GL_TEXTURE1);
            tex->Bind();

            glUniformMatrix4fv(program->Uniform("uM"), 1, false, &sprite.Model[0][0]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            tex->Unbind();
            glActiveTexture(GL_TEXTURE0);
        }

        program->Unbind();
        ibo->Unbind();
        vao->Unbind();

        glDisable(GL_BLEND);
        fbo->Unbind();
    }
    else
    {
        return (void *) (intptr_t) 0;
    }

    return (void *) (intptr_t) color->Handle();
}

int main(int argc, const char **argv)
{
    if (!scr::Window::Init())
        return 1;

    scr::Window window("Scratch Script", 800, 600);
    if (!window)
        return 2;

    const auto error = glewInit();
    if (error != GLEW_OK)
    {
        fprintf(stderr, "[ScratchScript] Failed to init GLEW\n");
        const auto description = glewGetErrorString(error);
        fprintf(stderr, "[GLEW 0x%08X] %s\n", error, description);
        return 3;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gl_debug_message_callback, NULL);

    ImGui::CreateContext();
    auto &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // hangs and crashes
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontFromFileTTF("resources/fonts/Gothic3.ttf", 24);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("resources/fonts/SpaceMono-Regular.ttf", 24);
    io.Fonts->AddFontFromFileTTF("resources/fonts/SpaceMono-Bold.ttf", 24);
    io.Fonts->AddFontFromFileTTF("resources/fonts/SpaceMono-BoldItalic.ttf", 24);
    io.Fonts->AddFontFromFileTTF("resources/fonts/SpaceMono-Italic.ttf", 24);
    io.Fonts->Build();

    ImGui::StyleColorsDark();
    auto &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(*window, true);
    ImGui_ImplOpenGL3_Init();

    size_t selected = 0;
    TextEditor editor;

    std::ifstream stream("resources/test/project.json");
    if (!stream.is_open())
    {
        fprintf(stderr, "Failed to open file\n");
        return 4;
    }
    else
    {
        nlohmann::json json;
        stream >> json;
        project = json;

        window.SetTitle(project.Name);

        for (auto &sprite: project.Sprites)
        {
            for (auto &costume: sprite.Costumes)
                costume.Load();
            sprite.ApplyModel();
        }

        stream.close();
    }

    editor.SetTextLines(project.Sprites[selected].Script.Lines);

    while (window.Update())
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();

        size_t prevSelected = selected;

        scr::ShowViewport(draw_viewport);
        scr::ShowResources(project.Sprites[selected], editor);
        scr::ShowSprites(project, selected);
        scr::ShowProperties(project.Sprites[selected]);

        if (selected != prevSelected)
        {
            project.Sprites[prevSelected].Script.Lines = editor.GetTextLines();
            editor.SetTextLines(project.Sprites[selected].Script.Lines);
        }

        ImGui::Render();

        int width, height;
        window.GetFramebufferSize(&width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            const auto backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    draw_viewport(0, 0, true);

    window.Destroy();
    scr::Window::Terminate();

    return 0;
}
