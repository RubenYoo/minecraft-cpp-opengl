#pragma once
#include "Test.h"
#include <GL/glew.h>


namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		GLfloat m_ClearColor[4];
	};

}
