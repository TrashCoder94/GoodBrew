#include "gbpch.h"
#include "Event.h"
#include "EventTypes.h"

namespace GB
{
	Event::Event(const EEventType& eventType) : m_EventType(eventType)
	{}

	Event::~Event()
	{}

	const EEventType Event::GetEventType()
	{
		return m_EventType;
	}

	const std::string Event::ToString()
	{
		return GB_STRINGIFY_MACRO(m_EventType);
	}
}