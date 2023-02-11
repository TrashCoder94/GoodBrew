#include "gbpch.h"
#include "KeyEvents.h"
#include "EventTypes.h"

namespace GB
{
	KeyEvent::KeyEvent(const int keyCode, const EEventType type) : Event(type),
		m_KeyCode(keyCode)
	{}

	const int KeyEvent::GetKeyCode() const
	{
		return m_KeyCode;
	}

	KeyPressedEvent::KeyPressedEvent(const int keyCode, const int repeatCount) : KeyEvent(keyCode, EEventType::KeyPressed),
		m_RepeatCount(repeatCount)
	{}

	const int KeyPressedEvent::GetRepeatCount() const
	{
		return m_RepeatCount;
	}

	const std::string KeyPressedEvent::ToString()
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}

	KeyReleasedEvent::KeyReleasedEvent(const int keyCode) : KeyEvent(keyCode, EEventType::KeyReleased)
	{}

	const std::string KeyReleasedEvent::ToString()
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}
}