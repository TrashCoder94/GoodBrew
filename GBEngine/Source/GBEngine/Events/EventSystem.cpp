#include "gbpch.h"
#include "EventSystem.h"
#include "Event.h"
#include "EventTypes.h"

namespace GB
{
	EventSystem* EventSystem::s_pInstance = nullptr;

	EventSystemListener::EventSystemListener() :
		m_EventType(EEventType::None),
		m_Delegate()
	{}

	EventSystemListener::~EventSystemListener()
	{
	}

	EventSystem::EventSystem() :
		m_EventListeners()
	{
		GB_CORE_ASSERT(!s_pInstance, "EventSystem already exists!");
		s_pInstance = this;
	}

	EventSystem::~EventSystem()
	{
		s_pInstance = nullptr;
	}

	EventSystem& EventSystem::Get()
	{
		return *s_pInstance;
	}

	void EventSystem::Bind(const EEventType eventType, BaseObject* pOwner, const std::function<bool(Event*)>& function)
	{
		EventSystemListener newListener;
		newListener.m_EventType = eventType;

		Delegate<BaseObject, bool, Event*> newDelegate;
		newDelegate.Bind(pOwner, function);
		newListener.m_Delegate = newDelegate;

		m_EventListeners.push_back(newListener);
	}

	void EventSystem::Unbind(const EEventType eventType, BaseObject* pOwner)
	{
		for (size_t iE = m_EventListeners.size() - 1; iE > 0; --iE)
		{
			EventSystemListener& eventListener = m_EventListeners.at(iE);
			if (eventListener.m_EventType == eventType && eventListener.m_Delegate.Unbind(pOwner))
			{
				m_EventListeners.erase(m_EventListeners.end() - iE);
				break;
			}
		}
	}

	void EventSystem::Broadcast(Event* event) const
	{
		if (m_EventListeners.empty())
		{
			return;
		}

		for (const EventSystemListener& eventListener : m_EventListeners)
		{
			if (eventListener.m_EventType == event->GetEventType())
			{
				if (eventListener.m_Delegate(event))
				{
					GB_CORE_LOG_INFO("Event {0} has been handled, so no more event listeners will receive this event!", event->ToString());
					return;
				}
			}
		}
	}
}