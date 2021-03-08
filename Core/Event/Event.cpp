#include "Event.h"

Event *Event::create(const char *evenName, std::shared_ptr<CallbackUtils::CallbackBase> callback)
{
    Event *event = new Event();
    event->setEventName(evenName);
    event->addCallback(callback);
    return event;
}

Event *Event::create(Event *event)
{
    Event *newEvent = new Event();
    *newEvent = *event;
    return newEvent;
}

Event::~Event()
{

}

void Event::setEventName(const char *eventName)
{
    m_EventName = eventName;
}

void Event::setCallback(std::shared_ptr<CallbackUtils::CallbackBase> callback, int index)
{
    m_Listeners[index] = callback;
}

const char *Event::getEventName()
{
    return m_EventName.c_str();
}

void Event::addCallback(std::shared_ptr<CallbackUtils::CallbackBase> callback)
{
    m_Listeners.push_back(callback);
}

int Event::getNumCallback()
{
    return m_Listeners.size();
}

std::shared_ptr<CallbackUtils::CallbackBase> Event::getCallback(int index)
{
    return m_Listeners[index];
}

void Event::setParms(std::shared_ptr<CallbackUtils::CallbackParmBase> parms)
{
    m_Parms = parms;
}

std::shared_ptr<CallbackUtils::CallbackParmBase> Event::getParms()
{
    return m_Parms;
}

void Event::run()
{
    for(auto &i : m_Listeners)
    {
        i->run(m_Parms);
    }
}

void Event::run(std::shared_ptr<CallbackUtils::CallbackParmBase> parms)
{
    setParms(parms);
    run();
}

bool Event::operator==(Event event)
{
    std::string myEventName = this->m_EventName;
    std::string otherEventName = event.getEventName();
    return myEventName == otherEventName;
}

Event Event::operator=(Event event)
{
    this->m_EventName = event.getEventName();
    this->m_Parms = event.getParms();
    this->m_Listeners = event.m_Listeners;
    return *this;
}

Event::Event()
{
    m_Parms = nullptr;
}
