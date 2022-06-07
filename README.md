# rmf_human_detector_oakd

![](docs/human_detection.png)

A ROS 2 node that detects humans via on-chip-inference on `OAK-D` cameras and publishes the detections over `/rmf_obstacles` as `rmf_obstacle_msgs::Obstacles` message.

## Requirements
* [OAK-D camera](https://docs.luxonis.com/projects/hardware/en/latest/)- Tested on OAK-D Lite and OAK-D
* [depthai-core](https://github.com/luxonis/depthai-core)
* [ROS 2](https://docs.ros.org/en/galactic/Installation/Ubuntu-Install-Debians.html)- Tested on `galactic`
* [Open-RMF](https://github.com/open-rmf/rmf)


## Setup
Follow the [instructions] to build `depthai` as a **shared library** and install it to a location that is a standard library path on your system. See [Troubleshooting](#troubleshooting) in case of issues.

Then clone this package into your `Open-RMF` workspace

```bash
git clone https://github.com/open-rmf/rmf_human_detector_oakd.git
```

Then run `rosdep` from the root of the workspace folder to install any missing dependencies
```bash
rosdep update
rosdep install --from-paths src --ignore-src --ros-distro galactic --skip-keys "depthai" -y
```

Then build the new package after sourcing the ROS 2 distribution
```bash
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release --packages-up-to rmf_human_detector_oakd
```

## Run
The node can be run either as a component within a ROS 2 container or as a standalone node. Remember to source the build workspace prior.

The component plugin is `rmf_human_detector_oakd::HumanDetector` and can be loaded into a `ComponentManager` via `ros2 component load <COMPONENT_MANAGER> rmf_human_detector_oakd::HumanDetector`.

To launch as a standalone node,
```bash
ros2 launch rmf_human_detector_oakd human_detection.launch.xml blob_path:=<PATH_TO_MOBILENET-SSD_BLOB>
```

### Parameters
THe node has several configurable parameters documented in the [launch file](launch/human_detector.launch.xml).
The most important of which is `blob_path` as it holds the absolute path to the NN model for inference. See `depthai` documentation for more information on how the various pre-trained models can be obtained.
It is recommended to use the [blobconverter](https://github.com/luxonis/blobconverter/) tool to obtain the `mobilenet-ssd_openvino_2021.4_6shave.blob` blob for inference.


To visualize the detection frames, set `debug:=True`. Note: Frames will only be visualized when a human is actively detected.


```bash
ros2 launch rmf_human_detector_oakd human_detector.launch.xml blob_path:=/home/USER/.cache/blobconverter/mobilenet-ssd_openvino_2021.4_6shave.blob debug:=True
```

## Troubleshooting
If `depthai` is not built and installed properly, a number of build and runtime errors may arise. If you're facing issues, try building it following these instructions
```bash
cd ~/
git clone https://github.com/luxonis/depthai-core.git
cd depthai-core
git submodule update --init --recursive
cmake -S. -Bbuild -D'BUILD_SHARED_LIBS=ON'
cmake --build build --target install
```

Next symlink the built shared libraries to `/usr/lib/`
```bash
cd /usr/lib/
sudo ln -s ~/Downloads/depthai-core/build/install/lib/libdepthai-core.so .
sudo ln -s ~/Downloads/depthai-core/build/install/lib/libdepthai-opencv.so .
```

Then build this package by setting the `depthai_DIR` flag.
```bash
colcon build --packages-up-to rmf_human_detector_oakd --cmake-args -DCMAKE_BUILD_TYPE=Release -Ddepthai_DIR=/home/USER/depthai-core/build/install/lib/cmake/depthai

```
