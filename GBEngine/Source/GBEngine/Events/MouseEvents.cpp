#include "gbpch.h"
#include "MouseEvents.h"
#include "EventTypes.h"

namespace GB
{
	MouseMovedEvent::MouseMovedEvent(const float x, const float y) : Event(EEventType::MouseMoved),
		m_MouseX(x),
		m_MouseY(y)
	{}

	float MouseMovedEvent::GetX() const
	{
		return m_MouseX;
	}

	float MouseMovedEvent::GetY() const
	{
		return m_MouseY;
	}

	const std::string MouseMovedEvent::ToString()
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
		return ss.str();
	}

	MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset) : Event(EEventType::MouseScrolled),
		m_XOffset(xOffset),
		m_YOffset(yOffset)
	{}

	float MouseScrolledEvent::GetXOffset() const
	{
		return m_XOffset;
	}

	float MouseScrolledEvent::GetYOffset() const
	{
		return m_YOffset;
	}

	const std::string MouseScrolledEvent::ToString()
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	MouseButtonEvent::MouseButtonEvent(const int button, const EEventType type) : Event(type),
		m_Button(button)
	{}

	int MouseButtonEvent::GetMouseButton() const
	{
		return m_Button;
	}

	MouseButtonPressedEvent::MouseButtonPressedEvent(const int button) : MouseButtonEvent(button, EEventType::MouseButtonPressed)
	{}

	const std::string MouseButtonPressedEvent::ToString()
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button, EEventType::MouseButtonReleased)
	{}

	const std::string MouseButtonReleasedEvent::ToString()
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}
}