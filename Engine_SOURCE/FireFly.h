#pragma once
#include "chScript.h"

namespace ch
{
	class FireFly : public Script
	{
	public:
		FireFly();
		virtual ~FireFly();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


	private:
		Transform* tr;
		float timer;
		float brightness;
		bool increasing;
	};

}


