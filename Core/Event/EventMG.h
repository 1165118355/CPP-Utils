////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-04-28
//  brief:  xxx
//
#ifndef EVENTMG_H
#define EVENTMG_H

#include "Utils/DTSingleton.h"

#include "EventEnum.h"
#include <vector>
#include <queue>
#include <memory>

#include "Event.h"
#include "Utils/CallbackUtils/CallbackParmBase.h"
#include "Utils/CallbackUtils/CallbackBase.h"

class EventMG:public DTSingleton<EventMG>
{
public:
    /// \brief  嚣张的析构函数
    ~EventMG();

    /// \brief  更新函数，每帧都检查m_EventsRun里面是否有等待执行的事件，如果有则执行
    void update();

    /// \brief 注册一个事件
    void registeredEvent(const char *eventName, std::shared_ptr<CallbackUtils::CallbackBase> callback);

    /// \brief  发射一个事件,参数请使用MakeCallbackParm()函数;
    void emitEvent(const char *eventName, std::shared_ptr<CallbackUtils::CallbackParmBase> parm1=std::shared_ptr<CallbackUtils::CallbackParmBase>());

	/// \brief  发射一个事件,参数请使用MakeCallbackParm()函数;
	void emitEventForthwith(const char* eventName, std::shared_ptr<CallbackUtils::CallbackParmBase> parm1 = std::shared_ptr<CallbackUtils::CallbackParmBase>());

    /// \brief  清理所有
    void clear();

    /// \brief  注册的事件中是否已经存在这个事件
    Event *findRegistEvent(const char *eventName);


private:
    friend class DTSingleton<EventMG>;

    std::vector<Event*> m_EventsReg;
    std::queue<Event*> m_EventsRun;
	std::mutex m_RunEventLock;
};

#endif // EVENTMG_H
