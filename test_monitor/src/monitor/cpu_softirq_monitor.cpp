#include "monitor/cpu_softirq_monitor.h"

#include "utils/read_file.h"
#include "utils/utils.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
void CpuSoftIrqMonitor::UpdateOnce(monitor::proto::MonitorInfo* monitor_info) {
  ReadFile softirqs_file(std::string("/proc/softirqs"));
  
  // store once line text
  std::vector<std::string> one_softirq;

  // stroe all line text
  std::vector<std::vector<std::string>> softirq;

   
  while (softirqs_file.ReadLine(&one_softirq)) {
    softirq.push_back(one_softirq);
    one_softirq.clear();
  }

  // softirp[0].size()  == cpu number
  for (int i = 0; i < softirq[0].size() - 1; i++) {
    std::string name = softirq[0][i];

    struct SoftIrq info;

    info.cpu_name = name;
    //softirq[1]: Hi
    info.hi = std::stoll(softirq[1][i + 1]);
    //softirq[2]:TIMER
    info.timer = std::stoll(softirq[2][i + 1]);
    info.net_tx = std::stoll(softirq[3][i + 1]);
    info.net_rx = std::stoll(softirq[4][i + 1]);
    info.block = std::stoll(softirq[5][i + 1]);
    info.irq_poll = std::stoll(softirq[6][i + 1]);
    info.tasklet = std::stoll(softirq[7][i + 1]);
    info.sched = std::stoll(softirq[8][i + 1]);
    info.hrtimer = std::stoll(softirq[9][i + 1]);
    info.rcu = std::stoll(softirq[10][i + 1]);
    info.timepoint = boost::chrono::steady_clock::now();

    // unordered_map<std::string, struct SoftIrq> cpu_softirqs_
    auto iter = cpu_softirqs_.find(name);

    if (iter != cpu_softirqs_.end()) {
      // get old data
      struct SoftIrq& old = (*iter).second;
      double period = Utils::SteadyTimeSecond(info.timepoint, old.timepoint);

      
      // create one_softirq_msg ptr to soft_irq obj
      auto one_softirq_msg = monitor_info->add_soft_irq();

      // caculate growth rate
      one_softirq_msg->set_cpu(info.cpu_name);
      one_softirq_msg->set_hi((info.hi - old.hi) / period);
      one_softirq_msg->set_timer((info.timer - old.timer) / period);
      one_softirq_msg->set_net_tx((info.net_tx - old.net_tx) / period);
      one_softirq_msg->set_net_rx((info.net_rx - old.net_rx) / period);
      one_softirq_msg->set_block((info.block - old.block) / period);
      one_softirq_msg->set_irq_poll((info.irq_poll - old.irq_poll) / period);
      one_softirq_msg->set_tasklet((info.tasklet - old.tasklet) / period);
      one_softirq_msg->set_sched((info.sched - old.sched) / period);
      one_softirq_msg->set_hrtimer((info.hrtimer - old.hrtimer) / period);
      one_softirq_msg->set_rcu((info.rcu - old.rcu) / period);
    }
    cpu_softirqs_[name] = info;
  }
  return;
}

}  // namespace monitor