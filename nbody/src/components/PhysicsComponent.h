#pragma once

template <int D, typename T>
class PhysicsComponent : public os::BaseComponent
{
public:
	PhysicsComponent(std::shared_ptr<os::Transform<D, T>> transform, T mass, glm::vec<D, T> velocity = glm::vec<D, T>((T) 0)) :
			mTransform(transform),
			mMass(mass),
	        mVelocity(velocity),
	        mForce(glm::vec<D, T>(0.0f))
	{ }

	inline T getMass() { return mMass; }
	inline glm::vec<D, T> &getVelocity() { return mVelocity; }
	inline glm::vec<D, T> &getForce() { return mForce; }

	inline void setMass(T mMass) { PhysicsComponent::mMass = mMass; }
	inline void setVelocity(const glm::vec<D, T> &mVelocity) { PhysicsComponent::mVelocity = mVelocity; }
	inline void setForce(const glm::vec<D, T> &mForce) { PhysicsComponent::mForce = mForce; }

private:
	std::shared_ptr<os::Transform<D, T>> mTransform;

	T mMass;
	glm::vec<D, T> mVelocity;
	glm::vec<D, T> mForce;
};
