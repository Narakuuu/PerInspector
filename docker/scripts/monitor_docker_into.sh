#!/usr/bin/env bash

# start GUI
xhost +local:root 1>/dev/null 2>&1
docker exec \
    -u root \
    -it linux_monitor \
    /bin/bash

# close GUI
xhost -local:root 1>/dev/null 2>&1