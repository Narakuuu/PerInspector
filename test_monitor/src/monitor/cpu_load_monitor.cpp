#include "monitor/cpu_load_monitor.h"

#include "utils/read_file.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
void CpuLoadMonitor::UpdateOnce(monitor::proto::MonitorInfo* monitor_info) {
  // create ReadFile obj and init ifstream
  ReadFile cpu_load_file(std::string("/proc/loadavg"));


  std::vector<std::string> cpu_load;
  // get all text-lines to cpu_load
  cpu_load_file.ReadLine(&cpu_load);
  // string to float
  load_avg_1_ = std::stof(cpu_load[0]);
  load_avg_3_ = std::stof(cpu_load[1]);
  load_avg_15_ = std::stof(cpu_load[2]);


  // create cpu_load_msg ptr to mutable_cpu_load obj 
  auto cpu_load_msg = monitor_info->mutable_cpu_load();
  // assign value
  cpu_load_msg->set_load_avg_1(load_avg_1_);
  cpu_load_msg->set_load_avg_3(load_avg_3_);
  cpu_load_msg->set_load_avg_15(load_avg_15_);

  return;
}

}  // namespace monitor