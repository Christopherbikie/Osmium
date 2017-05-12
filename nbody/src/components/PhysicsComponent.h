#pragma once

template <int D, typename T>
class PhysicsComponent : public os::BaseComponent
{
public:
	PhysicsComponent(std::shared_ptr<os::Transform<D, T>> transform, T mass, glm::vec<D, T> velocity = glm::vec<D, T>((T) 0)) :
			mTransform(transform),
			mMass(mass),
	        mVelocity(velocity),
			mAcceleration(glm::vec<D, T>(0.0f)),
			mForce(glm::vec<D, T>(0.0f))
	{ }

	inline T getMass() { return mMass; }
	inline glm::vec<D, T> &getVelocity() { return mVelocity; }
	inline glm::vec<D, T> &getAcceleration() { return mAcceleration; }
	inline glm::vec<D, T> &getForce() { return mForce; }

	inline void setMass(T mass) { mMass = mass; }
	inline void setVelocity(const glm::vec<D, T> &velocity) { mVelocity = velocity; }
	inline void setAcceleration(const glm::vec<D, T> &acceleration) { mAcceleration = acceleration; }
	inline void setForce(const glm::vec<D, T> &force) { mForce = force; }

private:
	std::shared_ptr<os::Transform<D, T>> mTransform;

	T mMass;
	glm::vec<D, T> mVelocity;
	glm::vec<D, T> mAcceleration;
	glm::vec<D, T> mForce;
};
