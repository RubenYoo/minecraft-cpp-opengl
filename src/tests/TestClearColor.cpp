#include "TestClearColor.h"
#include <imgui/imgui.h>

namespace test
{
	TestClearColor::TestClearColor()
		: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear color", m_ClearColor);
        /*
        {
            ImGui::Begin("Modifications");

            ImGui::Text("Translation for first block:");
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("X##TranslationA", &translationA.x, -5.0f, 5.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Y##TranslationA", &translationA.y, -5.0f, 5.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Z##TranslationA", &translationA.z, -5.0f, 5.0f);
            ImGui::PopItemWidth();

            ImGui::Separator();

            ImGui::Text("Translation for second block:");
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("X##TranslationB", &translationB.x, -2.0f, 2.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Y##TranslationB", &translationB.y, -2.0f, 2.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Z##TranslationB", &translationB.z, -2.0f, 2.0f);
            ImGui::PopItemWidth();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        */
	}
}