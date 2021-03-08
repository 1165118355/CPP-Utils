#include "DTSubThreadTask.h"

DTSubThreadTask *DTSubThreadTask::create(std::function<void ()> task, std::string taskName)
{
    DTSubThreadTask *utask = new DTSubThreadTask();
    utask->addCallback(task);
    utask->setName(taskName);
    return utask;
}

DTSubThreadTask::DTSubThreadTask()
{
    m_TaskProgress = 0;
}

void DTSubThreadTask::addCallback(std::function<void ()> task)
{
    m_Tasks.push_back(task);
}

void DTSubThreadTask::setName(std::string name)
{
    m_TaskName = name;
}

std::string DTSubThreadTask::getName()
{
    return m_TaskName;
}

void DTSubThreadTask::setProgress(float progress)
{
    m_TaskProgress = progress;
}

float DTSubThreadTask::getProgress()
{
    return m_TaskProgress;
}

void DTSubThreadTask::run()
{
    for(int i=0; i<m_Tasks.size(); ++i)
    {
        m_Tasks[i]();
    }
    emit taskComplate(m_TaskName.c_str());
}
