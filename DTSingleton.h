#pragma once

template <typename T>
class DTSingleton
{
public:
    static T * Instance()
    {
        if (!pT)
        {
            pT = new T;
        }
        return pT;
    }

    static void Destroy()
    {
        if (!pT)
        {
            delete pT;
        }
        pT = nullptr;
    }
protected:
        DTSingleton() {}
        DTSingleton(const DTSingleton& rhs);
        DTSingleton& operator=(const DTSingleton& rhs);
protected:
        static T * pT;
private:
};

template <typename T>
T * DTSingleton<T>::pT = nullptr;

