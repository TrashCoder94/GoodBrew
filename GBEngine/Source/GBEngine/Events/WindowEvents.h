#pragma once

#include "Event.h"

namespace GB
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		const std::string ToString() override;

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent();
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent();
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent();
	};
}
