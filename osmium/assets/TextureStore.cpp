#include <iostream>
#include <imgui.h>
#include "TextureStore.h"

namespace os
{
	namespace textureStore
	{
		static std::map<std::string, std::weak_ptr<Texture>> textures;

		std::shared_ptr<Texture> get(std::string path)
		{
			auto it = textures.find(path);
			std::shared_ptr<Texture> sptr;
			if (it != textures.end() && (sptr = (*it).second.lock()))
				return sptr;

			sptr = std::make_shared<Texture>(path);
			std::weak_ptr<Texture> storeptr = sptr;
			textures[path] = storeptr;

			return sptr;
		}

		std::map<std::string, std::weak_ptr<Texture>> getTextureMap()
		{
			return textures;
		}

		void setColumnWidths()
		{
			float windowWidth = ImGui::GetWindowWidth();
			ImGui::SetColumnOffset(1, 64 + ImGui::GetStyle().ItemSpacing.x);
			ImGui::SetColumnOffset(4, windowWidth - 1 * 96);
			ImGui::SetColumnOffset(3, windowWidth - 2 * 96);
			ImGui::SetColumnOffset(2, windowWidth - 3 * 96);
		}

		void showDebugWindow()
		{
			ImGui::SetNextWindowSize(ImVec2(800, 400));
			ImGui::Begin("Textures");

			static bool enableCompact = false;
			ImGui::Checkbox("Compact view", &enableCompact);
			int previewSize = enableCompact ? 12 : 64;

			ImGui::Text("Textures: %lu", textures.size());

			int totalBytes = 0;
			for (auto &&texture : textures)
				if (!texture.second.expired())
					totalBytes += texture.second.lock()->getSizeBytes();
			ImGui::SameLine(120);
			ImGui::Text("Total bytes: %d MB", totalBytes / (1024 * 1024));

			ImGui::BeginChild("##header", ImVec2(0, ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y));
			ImGui::Columns(5, "table");
			setColumnWidths();

			ImGui::Text("Preview"); ImGui::NextColumn();
			ImGui::Text("Path"); ImGui::NextColumn();
			ImGui::Text("Dimensions"); ImGui::NextColumn();
			ImGui::Text("Bytes"); ImGui::NextColumn();
			ImGui::Text("References"); ImGui::NextColumn();

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
			ImGui::BeginChild("##scrollingregion", ImVec2(0, -1));
			ImGui::Columns(5);
			setColumnWidths();

			static std::string selected = "";

			for (auto &&texturePair : textures)
			{
				std::string path = texturePair.first;
				ImGui::PushID(path.c_str());

				char referenceCount[12];
				sprintf(referenceCount, "%li", texturePair.second.use_count());

				auto texture = texturePair.second.lock();

				if (enableCompact)
				{
					if (ImGui::Selectable("##dummy", path == selected, ImGuiSelectableFlags_SpanAllColumns))
						selected = path;
					ImGui::SameLine();
				}
				if (texturePair.second.expired())
					ImGui::Text("Unloaded");
				else
				{
					auto size = glm::fvec2(texture->getDimensions());
					auto maxSize = size.x > size.y ? size.x : size.y;
					size /= maxSize;
					size *= previewSize;
					ImGui::Image((void *) texture->getLocation(), ImVec2(size.x, size.y), ImVec2(0, 0), ImVec2(1, 1),
					             ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
				}
				ImGui::NextColumn();

				ImGui::Text(path.c_str());
				ImGui::NextColumn();

				if (texturePair.second.expired())
				{
					ImGui::Text("-"); ImGui::NextColumn();
					ImGui::Text("-"); ImGui::NextColumn();
				} else
				{
					auto dimensions = texture->getDimensions();
					ImGui::Text("%dx%d", dimensions.x, dimensions.y);
					ImGui::NextColumn();

					int bytes = texture->getSizeBytes();
					totalBytes += bytes;
					ImGui::Text("%d", bytes);
					ImGui::NextColumn();
				}

				ImGui::Text(referenceCount);
				ImGui::NextColumn();

				ImGui::PopID();
			}

			ImGui::Columns(1);
			ImGui::EndChild();
			ImGui::Separator();

			ImGui::End();
		}
	}
}
