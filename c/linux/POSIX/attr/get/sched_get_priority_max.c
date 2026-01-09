/*
#include <sched.h>

// 获取调度策略的最高优先级值
int sched_get_priority_max(int policy);
    // parameter:
        - policy: 调度策略

    // return:
        - 成功返回调度策略的最高优先级值
          失败返回 -1，并设置 errno

    // note:
        - 调度策略
            - SCHED_OTHER
            - SCHED_FIFO
            - SCHED_RR
 */


#include <sched.h>
#include <stdio.h>

int main() {
    // SCHED_OTHER 调度策略的最低和最高优先级值
    printf("SCHED_OTHER min: %d max: %d\n",
           sched_get_priority_min(SCHED_OTHER),
           sched_get_priority_max(SCHED_OTHER));

    // SCHED_FIFO 调度策略的最低和最高优先级值
    printf("SCHED_FIFO min: %d max: %d\n",
           sched_get_priority_min(SCHED_FIFO),
           sched_get_priority_max(SCHED_FIFO));

    // SCHED_RR 调度策略的最低和最高优先级值
    printf("SCHED_PR min: %d max: %d\n",
           sched_get_priority_min(SCHED_RR),
           sched_get_priority_max(SCHED_RR));
}