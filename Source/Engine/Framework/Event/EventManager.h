#pragma once
#include "Framework/Singleton.h"
#include "Event.h"

#include <functional>
#include <list>
#include <map>

#define EVENT_SUBSCRIBE(id, function)	kiko::EventManager::Instance().Subscribe(id, this, std::bind(&function, this, std::placeholders::_1));
#define EVENT_UNSUBSCRIBE(id)			kiko::EventManager::Instance().Unsubscribe(id, this);

namespace kiko
{
	class IEventListener
	{
		
	};

	class EventManager : public Singleton<EventManager>
	{
	public:
		using eventFunction = std::function<void(const Event&)>;

		struct EventDispatcher
		{
			IEventListener* listener = nullptr; // Object that can listen for events
			eventFunction function; // Function that is called on event
		};

		void Update(float dt);

		void Subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data, void* sender = nullptr, float time = 0);

		friend class Singleton;

	private:
		EventManager() = default;
		std::map<Event::id_t, std::list<EventDispatcher>> m_dispatchers;
	};
}