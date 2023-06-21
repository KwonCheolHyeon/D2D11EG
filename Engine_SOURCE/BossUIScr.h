#pragma once
#include "chScript.h"
namespace ch
{
	class BossUIScr : public Script
	{
	public:
		BossUIScr();
		virtual ~BossUIScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		




	};
}


