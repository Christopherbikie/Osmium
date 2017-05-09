#include "PlayerControlFPV.h"
#include "../../../input/Keyboard.h"
#include "../../../input/Mouse.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace os
{
	PlayerControlFPV::PlayerControlFPV(std::shared_ptr<Transform<3, float_t>> transform) :
		mTransform(std::move(transform)),
	    mMoveSpeed(3.0f),
	    mSensitivity(0.01f)
	{ }

	void PlayerControlFPV::update(float_t delta)
	{
		delta /= 1000;

		// Rotation
		if (mouse::isCaptured())
		{
			glm::vec2 mouseDiff = ((glm::vec2) mouse::getMovement()) * mSensitivity;
			mTransform->getRotation() += glm::vec3(mouseDiff.y, mouseDiff.x, 0.0f);
		}

		// Position
		if (keyboard::isKeyDown(GLFW_KEY_W))
		{
			mTransform->getPosition().x += std::sin(mTransform->getRotation().y) * delta * mMoveSpeed;
			mTransform->getPosition().y -= std::sin(mTransform->getRotation().x) * delta * mMoveSpeed;
			mTransform->getPosition().z -= std::cos(mTransform->getRotation().y) * delta * mMoveSpeed;
		}
		if (keyboard::isKeyDown(GLFW_KEY_S))
		{
			mTransform->getPosition().x -= std::sin(mTransform->getRotation().y) * delta * mMoveSpeed;
			mTransform->getPosition().y += std::sin(mTransform->getRotation().x) * delta * mMoveSpeed;
			mTransform->getPosition().z += std::cos(mTransform->getRotation().y) * delta * mMoveSpeed;
		}
		if (keyboard::isKeyDown(GLFW_KEY_A))
		{
			mTransform->getPosition().x += std::sin((mTransform->getRotation().y - M_PI / 2)) * delta * mMoveSpeed;
			mTransform->getPosition().z -= std::cos((mTransform->getRotation().y - M_PI / 2)) * delta * mMoveSpeed;
		}
		if (keyboard::isKeyDown(GLFW_KEY_D))
		{
			mTransform->getPosition().x += std::sin((mTransform->getRotation().y + M_PI / 2)) * delta * mMoveSpeed;
			mTransform->getPosition().z -= std::cos((mTransform->getRotation().y + M_PI / 2)) * delta * mMoveSpeed;
		}
		if (keyboard::isKeyDown(GLFW_KEY_SPACE))
			mTransform->getPosition().y += delta * mMoveSpeed;
		if (keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT))
			mTransform->getPosition().y -= delta * mMoveSpeed;
	}
}
