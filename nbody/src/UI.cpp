#include "UI.h"
#include "components/PhysicsComponent.h"
#include "components/PathComponent.h"
#include <imgui.h>
#include <render/entity/components/PlayerControlFPV.h>

namespace ui
{
	static int32_t entitySelectionIndex = 0;

	void update(std::shared_ptr<os::Scene> scene, TimeState *timeState, int32_t *exp)
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", timeState->delta, ImGui::GetIO().Framerate);

		if (ImGui::CollapsingHeader("Camera"))
		{
			std::shared_ptr<os::LogicalEntity> camera;
			for (auto &&ent : scene->getLogicalEnts())
				if (std::get<0>(ent) == "Camera")
					camera = std::get<1>(ent);

			if (camera.get() != nullptr)
			{
				auto cameraTransform = camera->getComponent<os::Transform<3, float_t>>("Transform");

				glm::vec3 temp = cameraTransform->getPosition();
				ImGui::InputFloat3("Camera position", (GLfloat *) &temp);
				cameraTransform->setPosition(temp);
				temp = cameraTransform->getRotation();
				ImGui::InputFloat3("Camera rotation", (GLfloat *) &temp);
				cameraTransform->setRotation(temp);

				auto playerControl = camera->getComponent<os::PlayerControlFPV>("Control");

				float_t tempFloat = playerControl->getMoveSpeed();
				ImGui::SliderFloat("Move speed", &tempFloat, 10'000'000.0f, 10'000'000'000.0f, "%.3e m/s", 3);
				playerControl->setMoveSpeed(tempFloat);

			} else
			{
				ImGui::Text("No LogicalEntity \"Camera\" found in scene");
			}
		}

		if (ImGui::CollapsingHeader("Time Controls"))
		{
			char deltaString[37] = "Scaled delta: %.3f";
			if (timeState->paused || timeState->reversed)
			{
				strcat(deltaString, " (");
				if (timeState->paused) strcat(deltaString, "PAUSED");
				if (timeState->paused && timeState->reversed) strcat(deltaString, ", ");
				if (timeState->reversed) strcat(deltaString, "REVERSED");
				strcat(deltaString, ")");
			}
			ImGui::Text(deltaString, timeState->delta * timeState->deltaMultiplier);

			ImGui::SliderFloat("Speed", &timeState->deltaMultiplier, 0.0f, 1e12f, "%.3e seconds/second", 10);

			if (ImGui::Button("Toggle pause"))
				timeState->paused = !timeState->paused;
			ImGui::SameLine();
			if (ImGui::Button("Toggle reverse"))
				timeState->reversed = !timeState->reversed;
		}

		if (ImGui::CollapsingHeader("Physics Settings"))
		{
			ImGui::InputInt("Exp", exp, 1);
		}

		if (ImGui::CollapsingHeader("Entity Details"))
		{
			worldList physicsEnts;
			for (worldEnt ent : scene->getWorldEnts())
				if (std::get<1>(ent)->getComponent<PhysicsComponent<3, double_t>>("Physics") != nullptr)
					physicsEnts.push_back(ent);

			if (physicsEnts.size() == 0)
			{
				ImGui::Text("No Entity with Physics component found in scene");
				return;
			}

			if (ImGui::Button("Previous"))
				entitySelectionIndex--;
			ImGui::SameLine();
			if (ImGui::Button("Next")) entitySelectionIndex++;

			if (entitySelectionIndex >= (int32_t) physicsEnts.size()) entitySelectionIndex = 0;
			if (entitySelectionIndex < 0)
				entitySelectionIndex = (int32_t) (physicsEnts.size() - 1);

			auto selectedEnt = physicsEnts[entitySelectionIndex];

			ImGui::SameLine();
			ImGui::Text("%d: \"%s\"", entitySelectionIndex, std::get<0>(selectedEnt).c_str());

			auto transform = std::get<1>(selectedEnt)->getComponent<os::Transform<3, double_t>>("Transform");
			auto physics = std::get<1>(selectedEnt)->getComponent<PhysicsComponent<3, double_t>>("Physics");
			auto path = std::get<1>(selectedEnt)->getComponent<PathComponent<3, double_t>>("Path");

			glm::vec3 tempvec = transform->getPosition();
			ImGui::InputFloat3("Entity position (m)", (GLfloat *) &tempvec);
			transform->setPosition(tempvec);

			tempvec = physics->getVelocity();
			ImGui::InputFloat3("Entity velocity (m/s)", (GLfloat *) &tempvec);
			physics->setVelocity(tempvec);

			tempvec = physics->getAcceleration();
			ImGui::InputFloat3("Entity acceleration(m/s/s)", (GLfloat *) &tempvec);

			tempvec = physics->getForce();
			ImGui::InputFloat3("Entity force (N)", (GLfloat *) &tempvec);

			float_t tempfloat = (float_t) physics->getMass();
			ImGui::SliderFloat("Entity mass (kg)", &tempfloat, 1.0f, 1e35f, "%.3e kg", 35.0f);
			physics->setMass(tempfloat); // yes I know this limits mass to float precision, i'll work something out


			if (path != nullptr && ImGui::TreeNode("Trail options"))
			{
				path->showUIOptions();
				ImGui::TreePop();
			}
		}

		ImGui::Render();
	}
}
