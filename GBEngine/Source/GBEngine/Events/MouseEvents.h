#pragma once

#include "Event.h"

namespace GB
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y);

		float GetX() const;
		float GetY() const;

		const std::string ToString() override;

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset);

		float GetXOffset() const;
		float GetYOffset() const;
		const std::string ToString() override;

	private:
		float m_XOffset;
		float m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(const int button, const EEventType type);

	public:
		int GetMouseButton() const;

	protected:
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int button);

		const std::string ToString() override;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int button);

		const std::string ToString() override;
	};
}