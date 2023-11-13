#pragma once

#include "GBEngine/Core/Base.h"

namespace GB
{
	class Colour
	{
	public:
		Colour();
		explicit Colour(const float4& colour);
		~Colour();

		float4& GetColour();
		const float4& GetColour() const;
		void SetColour(const float4 newColour);

		const float r() const;
		const float g() const;
		const float b() const;
		const float a() const;
		const float* data() const;
		float* data();

	private:
		float4 m_Colour;
	};
}