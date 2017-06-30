#include <iostream>
#include "TextureStore.h"

namespace os
{
	namespace textureStore
	{
		std::map<std::string, std::weak_ptr<Texture>> mTextures;

		std::shared_ptr<Texture> get(std::string path)
		{
			auto it = mTextures.find(path);
			std::shared_ptr<Texture> sptr;
			if (it != mTextures.end() && (sptr = (*it).second.lock()))
				return sptr;

			sptr = std::make_shared<Texture>(path);
			std::weak_ptr<Texture> storeptr = sptr;
			mTextures[path] = storeptr;

			return sptr;
		}

		std::map<std::string, std::weak_ptr<Texture>> getTextureMap()
		{
			return mTextures;
		}
	}
}
