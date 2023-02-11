#pragma once

#include "Event.h"

namespace GB
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(const int keyCode, const EEventType type);

	public:
		const int GetKeyCode() const;

	protected:
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const int keyCode, const int repeatCount);

		const int GetRepeatCount() const;
		const std::string ToString() override;

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keyCode);

		const std::string ToString() override;
	};
}