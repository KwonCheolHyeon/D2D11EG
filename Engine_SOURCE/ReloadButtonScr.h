#pragma once
#include "chScript.h"

namespace ch
{
	class ReloadButtonScr : public Script
	{
	public:
		ReloadButtonScr();
		virtual ~ReloadButtonScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


	};
}


