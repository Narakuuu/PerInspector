# PerInspector
基于使用C++实现的分布式Linux性能分析监控系统，通过gPRC框架构建client与sever：cilent生成库供monitor模块和display模块调用并对启用server的服务器进行性能分析和监控，
为模拟出真实性能问题使用stress工具进行压测

## 特点
* 分布式的性能监控系统，支持CPU状态、系统负载、软中断、内存信息以及网络接口状态的监控；
* 使用dockerfile指定相应的cmake，grpc，proto等源码和依赖，构建整个项目环境，易于在多台服务器上部署环境，并编写容器操作的脚本指令，易于启动操作项目所依赖的环境。
* 使用工厂方法实现monitor模块，监控相应的CPU状态、系统负载、软中断、内存信息、网络接口状态，易于为之后扩展更多系统监控；
* 通过grpc框架，构建出相应的server， client，并考虑为了降低耦合性，项目每个模块相互独立，可拆解，只通过调用grpc服务来进行远程连接；
* 使用protobuf序列化协议，构建项目的数据结构并创建IDL文件;
* 为了模拟出真实的性能问题，使用stress工具进行模拟压测，分析相应时刻服务器的cpu状况和中断状况。

## 环境要求
* 虚拟机Ubuntu镜像不要低于18.04
* 选择net模式，推荐硬盘大小设置为30-40G
* 建议在Ubuntu git clone 代码，不推荐在windows上下载再进行拷贝，windows会改变代码中可执行文件的权限和格式

## 项目的启动过程
* git 环境配置
* Ubutun git 拉取项目代码
* 安装docker
* 通过项目中的docker文件，构建项目镜像
```bash
docker build --network host -f base.dockerfile .
```
* 启动并进入docker容器（进入项目docker/scripts目录）
```bash
./monitor_docker_run.sh
./monitor_docker_into.sh
```
* 编译代码
```bash
 cd cmake
 cmake ..
 make -j6
```
* 项目运行

**服务器端:**
```bash
cd rpc/manager/server
./server

新建终端
cd ~/work/private-node/docker/scripts
./monitor_docker_into.sh
cd work/cmake/test_monitor/src
./monitor
```
**客户端:**
```bash
cd ~/work/private-node/docker/scripts
./monitor_docker_into.sh
cd work/cmake/display_monitor
./display 
```

## 项目展示
_因为个人计算机性能有限，多开虚拟机有明显卡顿录屏效果不好，这里以监控本地服务器为例，_
> * __监控效果展示:

![image](https://github.com/Narakuuu/IMG/blob/main/inspector_show.gif)

![image](https://github.com/Narakuuu/IMG/blob/main/result.gif)

## 致谢
[@gRPC_QuickStart](https://grpc.io/docs/languages/cpp/quickstart/)：gRPC快速上手

*一些帮助很大的博客帖子*

[@黄树超](https://www.cnblogs.com/schips/p/10183111.html)：Linux中关于ldconfig的博客

[@美团技术团队](https://tech.meituan.com/2015/02/26/serialization-vs-deserialization.html)：关于序列化和反序列的文章

[@sparkdev](https://www.cnblogs.com/sparkdev/p/10354947.html)：Linux stress命令基本用法

*以及Abseil、cmake、protobuf、gRPC相关的官方build文档*

[@Abseil](https://github.com/abseil/abseil-cpp/blob/master/CMake/README.md)：Abseil CMake Build Instructions

[@protobuf](https://github.com/protocolbuffers/protobuf/blob/main/cmake/README.md)：protobuf CMake Configuration

[@gRPC](https://github.com/grpc/grpc/blob/master/BUILDING.md#build-from-source)：gRPC build from source






