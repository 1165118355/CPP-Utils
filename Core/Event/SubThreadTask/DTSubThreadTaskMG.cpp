#include "DTSubThreadTaskMG.h"
#include <windows.h>

DTSubThreadTaskMG *DTSubThreadTaskMG::m_Instance = nullptr;

DTSubThreadTaskMG *DTSubThreadTaskMG::get()
{
    if(nullptr == m_Instance)
    {
        m_Instance = new DTSubThreadTaskMG();
    }
    return m_Instance;
}

DTSubThreadTaskMG::DTSubThreadTaskMG(QObject *parent)
    :QThread(parent)
{

}

void DTSubThreadTaskMG::run()
{
    while(true)
    {
        for(int i=0; i<m_TasksDelete.size(); ++i)
        {
            delete m_TasksDelete[i];
        }
        m_TasksDelete.clear();
        if(m_Tasks.empty())
        {
            Sleep(500);
        }
        else
        {
            DTSubThreadTask *task = m_Tasks.front();
            task->start();
            m_Tasks.pop();
            m_TasksRunning.push_back(task);
        }
    }
}

void DTSubThreadTaskMG::onTaskRunnningComplate(const char *taskName)
{
    m_TaskName = taskName;
    int index = -1;
    for(int i=0; i<m_TasksRunning.size(); ++i)
    {
        if(m_TasksRunning[i]->getName() == taskName)
        {
            index= i;
            break;
        }
    }
    if(-1 != index)
    {
        m_TasksDelete.push_back(m_TasksRunning[index]);
        m_TasksRunning.erase(m_TasksRunning.begin() + index);
        emit taskDone(m_TaskName.c_str());
    }
}

DTSubThreadTask *DTSubThreadTaskMG::add(std::function<void ()> task, std::string name)
{
    DTSubThreadTask *utask = DTSubThreadTask::create(task, name);
    m_Tasks.push(utask);
    connect(utask, SIGNAL(taskComplate(const char*)), this, SLOT(onTaskRunnningComplate(const char *)));
    return utask;
}

DTSubThreadTask *DTSubThreadTaskMG::add(DTSubThreadTask *task)
{
    connect(task, SIGNAL(taskComplate(const char*)), this, SLOT(onTaskRunnningComplate(const char *)));
    m_Tasks.push(task);
    return task;
}
