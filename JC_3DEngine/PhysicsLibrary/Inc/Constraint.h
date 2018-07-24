#pragma once

namespace Physics
{
	class Particle;

	class Constraint
	{

	public:
		virtual ~Constraint() {}

		virtual void Apply() const = 0;
		virtual void DebugDraw() const {}

	};

	class Fixed :public Constraint
	{
	public:

		Fixed(Particle* p);
		Fixed(Particle* p, const MathLibrary::Vector3& location);

		void Apply() const override;
		void DebugDraw() const override;

	protected:

		Particle* mParticle;
		MathLibrary::Vector3 mLocation;
	};

	class Spring : public Constraint
	{
		Spring(Particle* a, Particle* b, float restLength = -1.0f);

		void Apply() const override;
		void DebugDraw() const override;

	protected:

		Particle* mparticleA;
		Particle* mparticleB;

		float mRestLength;

	};
}
