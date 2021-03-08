#include <functional>

#include "EventMG.h"
#include "Core/Event/Event.h"



EventMG::~EventMG()
{
    clear();
}

void EventMG::update()
{
    //  为了防止在运行过程中又调用其他的发送事件造成双重锁，所以这里把队列存到一个临时队列里
	m_RunEventLock.lock();
    auto tmep = m_EventsRun;
    while(!m_EventsRun.empty())
        m_EventsRun.pop();
    m_RunEventLock.unlock();

    while(!tmep.empty())
    {
        Event *event = tmep.front();
        event->run();
        delete event;
        tmep.pop();
    }
}

void EventMG::registeredEvent(const char *eventName, std::shared_ptr<CallbackUtils::CallbackBase> callback)
{
    auto event = findRegistEvent(eventName);
    if(!event)
    {
        event = Event::create(eventName, callback);
        m_EventsReg.push_back(event);
    }
    else
    {
        event->addCallback(callback);
    }
}


Event *EventMG::findRegistEvent(const char *eventName)
{
    for(int i=0; i<m_EventsReg.size(); ++i)
    {
        std::string regEventName = m_EventsReg[i]->getEventName();
        if(regEventName == eventName)
        {
            return m_EventsReg[i];
        }
    }
    return nullptr;
}

void EventMG::emitEvent(const char *eventName, std::shared_ptr<CallbackUtils::CallbackParmBase> parm1)
{
    Event *registeEvent = findRegistEvent(eventName);
    if(registeEvent)
    {
        Event *runEvent = Event::create(registeEvent);
        runEvent->setParms(parm1);

		m_RunEventLock.lock();
        m_EventsRun.push(runEvent);
		m_RunEventLock.unlock();
    }
}

void EventMG::emitEventForthwith(const char* eventName, std::shared_ptr<CallbackUtils::CallbackParmBase> parm1)
{
	Event* registeEvent = findRegistEvent(eventName);
	if (registeEvent)
	{
		registeEvent->setParms(parm1);
		registeEvent->run();
        registeEvent->setParms(CallbackUtils::CallbackParmBasePtr());
	}
}

void EventMG::clear()
{
    for(int i=0; i<m_EventsReg.size(); ++i)
    {
        delete m_EventsReg[i];
    }
    m_EventsReg.clear();
}
