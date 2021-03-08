#ifndef USUBTHREADTASK_H
#define USUBTHREADTASK_H

#include <QThread>
#include <functional>

class DTSubThreadTask:public QThread
{
    Q_OBJECT
public:
    /// \brief  创建一个子任务
    ///
    /// \parm   task        任务本身，他可以是一个lamda表达式
    /// \parm   taskName    任务名字，用于和别的任务进行区分，当任务管理器完成该任务时，会发出完成任务的信号并带上该名称
    ///
    /// \return 返回任务实例
    static DTSubThreadTask *create(std::function<void()> task, std::string taskName);

    /// \brief  设置任务的执行函数，他可以试一个lamda表达式
    void addCallback(std::function<void()> task);

    /// \brief  设置任务的名称
    void setName(std::string name);
    std::string getName();

    /// \brief  设置任务的进度
    ///
    /// \pram   progress    进度  范围是0~100
    void setProgress(float progress);
    float getProgress();

    /// \brief  执行该任务
    void run();
signals:
    void taskComplate(const char *taskName);
private:
    DTSubThreadTask();

private:
    std::function<void()> m_Task;       //  任务本身(任务执行体)
    std::vector<std::function<void()>> m_Tasks;
    std::string m_TaskName;                                 //  任务名称
    float m_TaskProgress;                                   //  任务的进度
};

#endif // USUBTHREADTASK_H
