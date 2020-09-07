////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-04-28
//  brief:  xxx
//
#ifndef __CALLBACKPARMBASE_H
#define __CALLBACKPARMBASE_H

#include <shared_mutex>
#include <memory>

namespace CallbackUtils
{
    class CallbackParmBase
    {
    public:
        CallbackParmBase()
        {
            m_ParmNumber= 0;
        }
        template<class T>
        static std::shared_ptr<CallbackParmBase> cast(std::shared_ptr<T> value)
        {
            return std::dynamic_pointer_cast<CallbackParmBase>(value);
        }

        int getParmNumber(){return m_ParmNumber;}
    protected:
        int m_ParmNumber;               //  参数的数量
    };
    typedef std::shared_ptr<CallbackParmBase> CallbackParmBasePtr;

    template<class PARM1>
    class CallbackParm1:public CallbackParmBase
    {
    public:
        /// \brief  初始化第一参数
        CallbackParm1<PARM1>(PARM1 parm1)
        {
            m_Parm1= parm1;
            m_ParmNumber = 1;
        }

        /// \brief  返回第一参数
        PARM1 getParm1()
        {
            return m_Parm1;
        }

    private:
        PARM1 m_Parm1;
    };

    template<class PARM1, class PARM2>
    class CallbackParm2:public CallbackParm1<PARM1>
    {
    public:
        /// \brief  初始化第一参数
        CallbackParm2<PARM1, PARM2>(PARM1 parm1, PARM2 parm2):
            CallbackParm1(parm1)
        {
            m_Parm2= parm2;
            m_ParmNumber = 2;
        }

        /// \brief  返回第二参数
        PARM2 getParm2()
        {
            return m_Parm2;
        }

    private:
        PARM2 m_Parm2;
    };

    template<class PARM1, class PARM2, class PARM3>
    class CallbackParm3:public CallbackParm2<PARM1, PARM2>
    {
    public:
        /// \brief  初始化第一参数
        CallbackParm3<PARM1, PARM2, PARM3>(PARM1 parm1, PARM2 parm2, PARM3 parm3):
            CallbackParm2(parm2)
        {
            m_Parm3= parm3;
            m_ParmNumber = 3;
        }

        /// \brief  返回第二参数
        PARM3 getParm3()
        {
            return m_Parm3;
        }

    private:
        PARM3 m_Parm3;
    };

    template<class PARM1>
    CallbackParmBasePtr makeCallbackParm(PARM1 parm1)
    {
        std::shared_ptr<CallbackParm1<PARM1>> callbackParm1 (new CallbackParm1<PARM1>(parm1));
        return CallbackParmBase::cast(callbackParm1);
    }

    template<class PARM1, class PARM2>
    CallbackParmBasePtr makeCallbackParm(PARM1 parm1, PARM2 parm2)
    {
        std::shared_ptr<CallbackParm2<PARM1, PARM2>> callbackParm2 (new CallbackParm2<PARM1, PARM2>(parm1, parm2));
        return CallbackParmBase::cast(callbackParm2);
    }

    template<class PARM1, class PARM2, class PARM3>
    CallbackParmBasePtr makeCallbackParm(PARM1 parm1, PARM2 parm2, PARM3 parm3)
    {
        std::shared_ptr<CallbackParm3<PARM1, PARM2, PARM3>> callbackParm3 (new CallbackParm3<PARM1, PARM2, PARM3>(parm1, parm2, parm3));
        return CallbackParmBase::cast(callbackParm3);
    }

}
#endif // __CALLBACKPARMBASE_H
