#include "MeshComponent.h"

namespace os
{

	MeshComponent::MeshComponent(std::string objPath)
	{
		mMesh = std::make_shared<Mesh>(objPath);
	}

	void MeshComponent::draw(std::shared_ptr<Shader> shader)
	{
		mMesh->draw(shader);
	}

	const std::shared_ptr<Mesh> &MeshComponent::get()
	{
		return mMesh;
	}
}
