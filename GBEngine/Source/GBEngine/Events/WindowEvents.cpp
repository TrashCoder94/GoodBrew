#include "gbpch.h"
#include "WindowEvents.h"
#include "EventTypes.h"

namespace GB
{
	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height) : Event(EEventType::WindowResize),
		m_Width(width),
		m_Height(height)
	{}

	unsigned int WindowResizeEvent::GetWidth() const
	{
		return m_Width;
	}

	unsigned int WindowResizeEvent::GetHeight() const
	{
		return m_Height;
	}

	const std::string WindowResizeEvent::ToString()
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << GetWidth() << ", " << GetHeight();
		return ss.str();
	}

	WindowCloseEvent::WindowCloseEvent() : Event(EEventType::WindowClose)
	{
	}

	WindowFocusEvent::WindowFocusEvent() : Event(EEventType::WindowFocus)
	{
	}

	WindowLostFocusEvent::WindowLostFocusEvent() : Event(EEventType::WindowLostFocus)
	{
	}
}