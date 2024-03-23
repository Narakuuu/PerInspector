#pragma once

#include <QApplication>
#include <thread>
#include "client/rpc_client.h"
#include "monitor_widget.h"

int main(int argc, char* argv[]) {
  // start
  QApplication app(argc, argv);
  monitor::MonitorWidget moitor_widget;
  // create rpc_client
  monitor::RpcClient rpc_client;
  monitor::proto::MonitorInfo monitor_info;


  // get data to monitor_info
  rpc_client.GetMonitorInfo(&monitor_info);
  
  //get board name
  std::string name = monitor_info.name();
  
  // show content
  QWidget* widget = moitor_widget.ShowAllMonitorWidget(name);
  widget->show();


  // use thread  update data
  std::unique_ptr<std::thread> thread_;
  thread_ = std::make_unique<std::thread>([&]() {
    while (true) {
      monitor_info.Clear();
      // get data
      rpc_client.GetMonitorInfo(&monitor_info);
      // update
      moitor_widget.UpdateData(monitor_info);
      // sleep 2s
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });
  thread_->detach();

  return app.exec();
}