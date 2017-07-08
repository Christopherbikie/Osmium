#include "MeshComponent.h"

namespace os
{

	MeshComponent::MeshComponent(const char *objPath)
	{
		mMesh = std::make_shared<Mesh>(objPath);
	}

	void MeshComponent::draw(Shader *shader)
	{
		mMesh->draw(shader);
	}

	const std::shared_ptr<Mesh> &MeshComponent::get()
	{
		return mMesh;
	}
}
