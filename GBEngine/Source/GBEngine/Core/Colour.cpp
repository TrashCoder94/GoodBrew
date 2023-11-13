#include "gbpch.h"
#include "Colour.h"

namespace GB
{
	Colour::Colour() :
		m_Colour(float4(1.0f))
	{}

	Colour::Colour(const float4& colour) :
		m_Colour(colour)
	{}

	Colour::~Colour()
	{}

	float4& Colour::GetColour()
	{
		return m_Colour;
	}

	const float4& Colour::GetColour() const
	{
		return m_Colour;
	}

	void Colour::SetColour(const float4 newColour)
	{
		m_Colour = newColour;
	}

	const float Colour::r() const
	{
		return m_Colour.x;
	}

	const float Colour::g() const
	{
		return m_Colour.y;
	}

	const float Colour::b() const
	{
		return m_Colour.z;
	}

	const float Colour::a() const
	{
		return m_Colour.w;
	}

	const float* Colour::data() const
	{
		return &m_Colour[0];
	}

	float* Colour::data()
	{
		return &m_Colour[0];
	}
}