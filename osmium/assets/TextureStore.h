#pragma once

#include <memory>
#include "../render/graphics/Texture.h"

namespace os
{
	namespace textureStore
	{
		std::shared_ptr<Texture> get(std::string path);

		std::map<std::string, std::weak_ptr<Texture>> getTextureMap();
	}
}
