#pragma once
#include "chScript.h"

namespace ch
{
	class ReloadBarScr : public Script
	{
	public:
		ReloadBarScr();
		virtual ~ReloadBarScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	};
}


