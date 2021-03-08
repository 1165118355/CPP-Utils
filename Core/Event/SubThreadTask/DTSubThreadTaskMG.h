////////////////////////////
/// *    子线程任务管理器
///
/// *   -david.zhu
/// *   2018年11月16日 15:02:41
/// *   FBX导入

#ifndef USUBTHREADTASKMG_H
#define USUBTHREADTASKMG_H

#include <QThread>
#include <queue>

#include "DTSubThreadTask.h"

class DTSubThreadTaskMG :public QThread
{
    Q_OBJECT
public:
    static DTSubThreadTaskMG *get();

    /// \brief  添加一个子线程任务
    DTSubThreadTask *add(std::function<void()> task, std::string name);
    DTSubThreadTask *add(DTSubThreadTask *task);

    /// \brief  设置子线程检测频率
    void setFrequency(int num);
protected:
    /// \brief  喵帕斯
    void run();

protected slots:
    void onTaskRunnningComplate(const char *taskName);

signals:
    /// \brief  任务变动发出该信号
    void taskActivity(const char *taskName, float progress);

    /// \brief  任务完成发出该信号
    void taskDone(const char *taskName);
private:
    DTSubThreadTaskMG(QObject *parent=nullptr);
private:
    static DTSubThreadTaskMG *m_Instance;                       //  管理器实例
    std::queue<DTSubThreadTask *> m_Tasks;                      //  任务队列
    std::vector<DTSubThreadTask *> m_TasksRunning;              //  正在执行中的任务
    std::vector<DTSubThreadTask *> m_TasksDelete;              //  等待删除的任务
    std::string m_TaskName;
};

#endif // USUBTHREADTASKMG_H
