#include "CallBackBase.h"

CallbackUtils::CallbackBasePtr CallbackUtils::makeCallback(std::function<void ()> func)
{
    std::shared_ptr<Callback0> callback (new Callback0(func));
    return callback;
}
