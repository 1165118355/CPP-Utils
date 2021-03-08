////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-04-28
//  brief:  xxx
//

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <memory>
#include <vector>
#include "Utils/CallbackUtils/CallbackBase.h"
#include "Utils/CallbackUtils/CallbackParmBase.h"

class Event
{
public:
    /// \brief  创建一个事件
    static Event *create(const char *evenName, std::shared_ptr<CallbackUtils::CallbackBase> callback);
    static Event *create(Event *event);
    ~Event();

    /// \brief  获取事件名称
    const char *getEventName();

    /// \brief  获取回调
    void addCallback(std::shared_ptr<CallbackUtils::CallbackBase> callback);
    int getNumCallback();
    std::shared_ptr<CallbackUtils::CallbackBase> getCallback(int index);

    /// \brief  设置参数，在调用run的时候会起作用
    void setParms(std::shared_ptr<CallbackUtils::CallbackParmBase> parms);
    std::shared_ptr<CallbackUtils::CallbackParmBase> getParms();

    /// \brief  执行回调（带参数的会覆盖掉run会调用的参数）
    void run();
    void run(std::shared_ptr<CallbackUtils::CallbackParmBase> parms);

    /// \brief  重载一下逻辑等，判断条件是事件名称是否一样
    bool operator==(Event event);
    Event operator=(Event event);
protected:
    Event();

    /// \brief  设置事件名
    void setEventName(const char *eventName);

    /// \brief  设置回调
    void setCallback(std::shared_ptr<CallbackUtils::CallbackBase> callback, int index);
private:
    std::string m_EventName;
    std::vector<std::shared_ptr<CallbackUtils::CallbackBase>> m_Listeners;
    std::shared_ptr<CallbackUtils::CallbackParmBase> m_Parms;
};

#endif // EVENT_H
