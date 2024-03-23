#include "cpu_load_model.h"

namespace monitor {
CpuLoadModel::CpuLoadModel(QObject* parent) : MonitorInterModel(parent) {
  // column name
  header_ << tr("load_1");
  header_ << tr("load_3");
  header_ << tr("load_15");
}

int CpuLoadModel::rowCount(const QModelIndex& parent) const {
  return monitor_data_.size();
}

int CpuLoadModel::columnCount(const QModelIndex& parent) const {
  return COLUMN_MAX;
}


QVariant CpuLoadModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  // role check
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return header_[section];
  }

  return MonitorInterModel::headerData(section, orientation, role);
}



QVariant CpuLoadModel::data(const QModelIndex& index, int role) const {
  // out bounds
  if (index.column() < 0 || index.column() >= COLUMN_MAX) {
    return QVariant();
  }
  // role && in bounds   monitor_data_  2dimensional array
  if (role == Qt::DisplayRole) {
    if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX)
      return monitor_data_[index.row()][index.column()];
  }
  return QVariant();
}

void CpuLoadModel::UpdateMonitorInfo(
    const monitor::proto::MonitorInfo& monitor_info) {
  // reset
  beginResetModel();
  monitor_data_.clear();

  monitor_data_.push_back(insert_one_cpu_load(monitor_info.cpu_load()));

  // QModelIndex leftTop = createIndex(0, 0);
  // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
  // emit dataChanged(leftTop, rightBottom, {});


  // end
  endResetModel();

  return;
} 


// cpu_load data type change to QT data type
std::vector<QVariant> CpuLoadModel::insert_one_cpu_load(
    const monitor::proto::CpuLoad& cpu_load) {

  std::vector<QVariant> cpu_load_list;

  for (int i = CpuLoad::CPU_AVG_1; i < COLUMN_MAX; i++) {
    switch (i) {
      case CpuLoad::CPU_AVG_1:
        cpu_load_list.push_back(QVariant(cpu_load.load_avg_1()));
        break;
      case CpuLoad::CPU_AVG_3:
        cpu_load_list.push_back(QVariant(cpu_load.load_avg_3()));
        break;
      case CpuLoad::CPU_AVG_15:
        cpu_load_list.push_back(QVariant(cpu_load.load_avg_15()));
        break;
      default:
        break;
    }
  }
  return cpu_load_list;
}
}  // namespace monitor
