/*****************************************************************************/
/*                             Spike SourceCode                              */
/*                                                                           */
/* File created by: Fahim Fuad                                               */
/* Other editors: None                                                       */
/*                                                                           */
/*   Licensed under the Apache License, Version 2.0 (the "License");         */
/*   you may not use this file except in compliance with the License.        */
/*   You may obtain a copy of the License at                                 */
/*                                                                           */
/*       http://www.apache.org/licenses/LICENSE-2.0                          */
/*                                                                           */
/*   Unless required by applicable law or agreed to in writing, software     */
/*   distributed under the License is distributed on an "AS IS" BASIS,       */
/*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*/
/*   See the License for the specific language governing permissions and     */
/*   limitations under the License.                                          */
/*****************************************************************************/
#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Spike/Renderer/Mesh.h"


Sandbox2D::Sandbox2D()
    :Layer("Sandbox2D"), m_CameraController(30.0f, 1.778f, 0.1f, 1000.0f), m_Mesh(Spike::Ref<Spike::Mesh>::Create("Spike-Editor/assets/meshes/i.fbx")),
    m_Mesh2(Spike::Ref<Spike::Mesh>::Create("Spike-Editor/assets/meshes/i.fbx"))
{
}

void Sandbox2D::OnAttach()
{
    LE_PROFILE_FUNCTION();
    m_CheckerboardTexture = Spike::Texture2D::Create("Spike-Editor/assets/textures/Checkerboard.png");

}
void Sandbox2D::OnDetach()
{
    LE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Spike::Timestep ts)
{
    LE_PROFILE_FUNCTION();
    // Update
     m_CameraController.OnUpdate(ts);
    // Render
     Spike::Renderer2D::ResetStats();
    {
        LE_PROFILE_SCOPE("Renderer Preparation");
        Spike::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Spike::RenderCommand::Clear();
    }

    {
        Spike::Renderer::BeginScene(m_CameraController);
        Spike::Renderer::SubmitMesh(m_Mesh, glm::translate(glm::mat4(1.0f), m_Position));
        Spike::Renderer::SubmitMesh(m_Mesh2, glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 10.0f, 1.0f)));
        Spike::Renderer::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    LE_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::DragFloat3("Position", glm::value_ptr(m_Position));
    ImGui::End();
}

void Sandbox2D::OnEvent(Spike::Event& e)
{
    m_CameraController.OnEvent(e);
}
