////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-04-28
//  brief:  xxx
//
#ifndef __CALLBACKBASE_H
#define __CALLBACKBASE_H

#include <functional>
#include "Utils/CallbackUtils/CallbackParmBase.h"
#include <assert.h>

//  介绍：回调基类，用来接收makeCallback的返回值，要用的时候调用execute就可以了什么都不用管
//  用意：其实Unigine已经有一套Callback机制了（Unigine::CallbackBase）但是他的代码没办法将参数存起来，过一段时间之后再运行。所以我根据他原来的机制进行了改进添加了CallbackParmBase进行参数存储。
namespace CallbackUtils
{
    class CallbackBase
    {
    public:
        CallbackBase()
        {
            m_ParmNumber = -1;
        }

        template<class T>
        static std::shared_ptr<CallbackBase> cast(std::shared_ptr<T> value)
        {
            return std::dynamic_pointer_cast<CallbackBase>(value);
        }

        void run(std::shared_ptr<CallbackParmBase> parm)
        {
            if(parm)
            {
                int parameterNumber = parm->getParmNumber();
                if(parameterNumber != m_ParmNumber)
                {
                    printf("ERROR: %s function parameter number %d != %d parameter number\n", typeid(CallbackBase).name(), m_ParmNumber, parameterNumber);
                    assert(0);
                    return;
                }
            }
            execute(parm);
        }

        /// \brief  跑起来，跑起来
        virtual void execute(std::shared_ptr<CallbackParmBase> parm)=0;
    protected:
        int m_ParmNumber;
    };
    typedef std::shared_ptr<CallbackBase> CallbackBasePtr;

    class Callback0 :
            public CallbackBase
    {
    public:
        Callback0(std::function<void()> callback)
        {
            m_ParmNumber = 0;
            m_Callback = callback;
        }
        virtual void execute(std::shared_ptr<CallbackParmBase> parm)
        {
            m_Callback();
        }
		std::function<void()> getFunction() { return m_Callback; }


    private:
        std::function<void()> m_Callback;
    };

    template<class PARM1>
    class Callback1 :
            public CallbackBase
    {
    public:
        Callback1(std::function<void(PARM1)> func)
        {
            m_ParmNumber = 1;
            m_Callback = func;
        }
        virtual void execute(std::shared_ptr<CallbackParmBase> parm)
        {
            std::shared_ptr<CallbackParm1<PARM1>> callbackParm = std::static_pointer_cast<CallbackParm1<PARM1>>(parm);
            try
            {
                PARM1 parm1 = callbackParm->getParm1();
                m_Callback(parm1);
            }
            catch(...)
            {
                printf("Parm1:%s does not match the function\n", typeid(PARM1).name());
                assert(0);
            }
        }
		std::function<void(PARM1)> getFunction() {return m_Callback;}
    private:
        std::function<void(PARM1)> m_Callback;
    };

    template<class PARM1, class PARM2>
    class Callback2 :
            public CallbackBase
    {
    public:
        Callback2(std::function<void(PARM1, PARM2)> func)
        {
            m_ParmNumber = 2;
            m_Callback = func;
        }
        virtual void execute(std::shared_ptr<CallbackParmBase> parm)
        {try
            {
                std::shared_ptr<CallbackParm2<PARM1,PARM2>> callbackParm = std::static_pointer_cast<CallbackParm2<PARM1,PARM2>> (parm);
                PARM1 parm1 = callbackParm->getParm1();
                PARM2 parm2 = callbackParm->getParm2();
                m_Callback(parm1, parm2);
            }
            catch(...)
            {
                printf("Parm1:%s , Parm2:%s does not match the function\n", typeid(PARM1).name(), typeid(PARM2).name());
                assert(0);
            }
        }
		std::function<void(PARM1, PARM2)> getFunction() { return m_Callback; }
    private:
        std::function<void(PARM1, PARM2)> m_Callback;
    };


    template<class PARM1, class PARM2, class PARM3>
    class Callback3 :
            public CallbackBase
    {
    public:
        Callback3(std::function<void(PARM1, PARM2, PARM3)> func)
        {
            m_ParmNumber = 3;
            m_Callback = func;
        }
        virtual void execute(std::shared_ptr<CallbackParmBase> parm)
        {
            std::shared_ptr<CallbackParm3<PARM1,PARM2,PARM3>> callbackParm = std::static_pointer_cast<CallbackParm3<PARM1,PARM2,PARM3>> (parm);
            PARM1 parm1 = callbackParm->getParm1();
            PARM2 parm2 = callbackParm->getParm2();
            PARM2 parm3 = callbackParm->getParm3();
            m_Callback(parm1, parm2, parm3);
        }
    private:
        std::function<void(PARM1, PARM2, PARM3)> m_Callback;
    };

    /// \brief  不知道为什么，把他的定义写在这里总是报错重定义，于是我把他的定义放在了cpp文件里面
    CallbackBasePtr makeCallback(std::function<void ()> func);

    template<class PARM1>
    CallbackBasePtr makeCallback(std::function<void(PARM1)> func)
    {
        std::shared_ptr<Callback1<PARM1>> callback (new Callback1<PARM1>(func));
        return CallbackBase::cast(callback);
    }

    template<class PARM1, class PARM2>
    CallbackBasePtr makeCallback(std::function<void(PARM1, PARM2)> func)
    {
        std::shared_ptr<Callback2<PARM1, PARM2>> callback (new Callback2<PARM1, PARM2>(func));
        return CallbackBase::cast(callback);
    }

    template<class PARM1, class PARM2, class PARM3>
    CallbackBasePtr makeCallback(std::function<void(PARM1, PARM2, PARM3)> func)
    {
        std::shared_ptr<Callback3<PARM1, PARM2, PARM3>> callback (new Callback3<PARM1, PARM2, PARM3>(func));
        return CallbackBase::cast(callback);
    }


    ////////////////////////////////////////


    template <class Cls>
    CallbackBasePtr makeCallback(Cls *obj, void(Cls::*func)())
    {
        auto function = std::bind(func, obj);
        std::shared_ptr<Callback0> callback (new Callback0(function));
        return callback;
    }

    template <class Cls, class A0>
	std::shared_ptr<Callback1<A0>> makeCallback(Cls *obj, void(Cls::*func)(A0 par1))
    {
        auto function = std::bind(func, obj, std::placeholders::_1);
        std::shared_ptr<Callback1<A0>> callback (new Callback1<A0>(function));
        return callback;
    }

    template <class Cls, class A0, class A1>
    CallbackBasePtr makeCallback(Cls *obj, void(Cls::*func)(A0 par1,A1 par2))
    {
        auto function = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2);
        std::shared_ptr<Callback2<A0,A1>> callback (new Callback2<A0,A1>(function));
        return callback;
    }

}
#endif // __CALLBACKBASE_H
