#pragma once

namespace GB
{
	enum class EEventType;

	class Event
	{
	public:
		Event(const EEventType& eventType);
		virtual ~Event();

		const EEventType GetEventType();
		virtual const std::string ToString();

	private:
		EEventType m_EventType;
	};
}