#include "TestApp.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include "app/Settings.h"


using namespace os;

void TestApp::run()
{
	shader = new os::Shader;
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
	};
	float_t texCoords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
	};

	vao = new VAO;
	vao->storeInBuffer(0, 3, 36, vertices);
	vao->storeInBuffer(1, 2, 36, texCoords);

	world = Scene();
	Entity ent = *world.addEntity();
	Entity cam = *world.addEntity("camera");

	std::shared_ptr<Transform<3, double_t>> transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
	ent.addComponent("Transform", transform);
	
	std::shared_ptr<Transform<3, double_t>> cameraTransform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
	std::shared_ptr<CameraPerspective> camera = std::make_shared<CameraPerspective>(CameraPerspective(60.0f, settings::getAspectRatio(), 0.3f, 100.0f));

	cam.addComponent("Transform", cameraTransform);
	cam.addComponent("Camera", camera);

	//camera = new CameraPerspective(60.0f, settings::getAspectRatio(), 0.3f, 100.0f);                 // Perspective camera
//	camera = new CameraOrthographic(glm::vec2(0.0), settings::getViewport() / 100.0f, 0.3f, 100.0f); // Orthographic camera

	texture = new Texture("res/images/default.png");

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		double_t delta = 1000.0f / ImGui::GetIO().Framerate;

		// Cube

		shader->use();

		double_t time = glfwGetTime();
		transform->setPosition(glm::dvec3(sin(5 * time), cos(4 * time), tan(time)));
//		transform->setRotation(glm::dvec3(0.0, time, sin(time)));
//		transform->setScale(glm::dvec3(sin(time * 3.0)));

//		cameraTransform->setPosition(glm::vec3(0.0f, 0.0f, time + 3.0f));

		shader->loadUniform("model", transform->getMatrix());
		shader->loadUniform("view", cameraTransform->getMatrix());
		shader->loadUniform("projection", camera->getMatrix());

		texture->bind(shader, "diffuse");
		vao->bind();
		shader->drawArrays(0, 36);
		vao->unbind();
		texture->unbind();

		// GUI

		ImGui::Text("Hello, world!");
		glm::vec2 viewport = settings::getViewport();
		ImGui::Text("Viewport: x: %.0f y: %.0f", viewport.x, viewport.y);

		static GLchar buf[64] = "";
		ImGui::InputText("Window Title", buf, 64);
		if (ImGui::Button("Set"))
			settings::setWindowTitle(buf);

		glm::vec3 clearColor = settings::getClearColour();
		ImGui::ColorEdit3("Clear color", (GLfloat *) &clearColor);
		settings::setClearColour(clearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", delta, ImGui::GetIO().Framerate);

		glm::vec3 temp = transform->getPosition(); // must create variable for this one because we have to cast to fvec3
		ImGui::InputFloat3("Cube position", (GLfloat *) &temp);
		ImGui::InputFloat3("Camera position", (GLfloat *) &cameraTransform->getPosition());

		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);
	}

	delete shader;
	delete vao;
	delete texture;
}

void TestApp::windowResizeCallback(glm::vec2 dimensions)
{

	std::shared_ptr<CameraPerspective> camera = std::static_pointer_cast<CameraPerspective>(mainCamera->getComponent("Camera"));

	camera->setAspectRatio(settings::getAspectRatio()); // Perspective camera
//	camera->setDimensions(dimensions / 100.0f);         // Orthographic camera
}
