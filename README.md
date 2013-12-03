Nao Autism Games
================

This package contains three basic games designed for children with autism. The first two games, Guess the Emotion and Copy the Robot, go hand in hand and are designed to be played one after the other. These two games are based on emotion recognition and replication, as well as turn-taking. The third game is standalone and allows the child to control the robot remotely.

Many thanks to Aldebaran Robotics for their assistance in providing the behaviors used in the emotion games. Their support has been much appreciated.

Installation
------------

It is assumed that ROS (the Robot Operating System) is already installed on your computer running Ubuntu Linux. If it is not, you can find installation instructions at http://www.ros.org/wiki/ROS/Installation. The following packages are also required:

+ openni_launch
+ openni_tracker
+ Aldebaran NaoQi SDK
+ Pocketsphinx speech recognition engine
+ nao humanoid_stacks
+ libsvm

###Easy Installation###
The simplest way to install is to use the installation script [here](https://dl.dropboxusercontent.com/u/50803462/installscript.sh). Download and double click the script to run it in the terminal, and the games plus all required ROS packages will be installed to the correct directories.

Two pieces of software will need to be installed manually: NaoQi SDK and the OpenNI NiTE middleware.

###Manual Installation###

If you would prefer to install manually, or if the easy installation does not work for any reason, follow these steps to install the games.

####OpenNI####
ROS OpenNI packages can be installed via the command line (on Linux) as follows:
```bash
sudo apt-get install ros-groovy-openni-launch 
sudo apt-get install ros-groovy-openni-tracker
```
The openni_tracker package needs an old version of NiTE to function properly, so go [here](http://www.openni.org/openni-sdk/openni-sdk-history-2/) to download the appropriate NiTE v1.5.2.21 for your operating system. Extract the downloaded archive and use the `install.sh` script to install.


####NaoQi####
The NaoQi SDK can be downloaded from https://community.aldebaran-robotics.com/resources. Bear in mind that you need to register as a developer with Aldebaran in order to access this. Select NAOQI C++ SDK 1.14.5 Linux (32 bits or 64 bits depending on your operating system), then extract it somewhere on your machine (for our examples we have placed it under /opt/naoqi). Next, we need to define some environment variables that we'll use later when running the games and add the NaoQi lib directory to our PYTHONPATH so ROS can access it. To avoid having to repeat lots of typing, add the following to the end of your `~/.bashrc`:
```bash
# Or wherever the NAOqi SDK is installed
export NAOQI_HOME=/opt/naoqi/naoqi-sdk-1.14.5-linux64
export NAOQI_LIBS=$NAOQI_HOME/lib

# Add NAOqi to your python path
export PYTHONPATH=$PYTHONPATH:$NAOQI_LIBS
# Define the library path for running ROS Nao components
export NAOQI_LIBRARY_PATH=$NAOQI_LIBS:$LD_LIBRARY_PATH
```

####Speech Recognition####
Pocketsphinx is used for speech recognition. To install, type the following into the terminal:
```bash 
sudo apt-get install ros-groovy-pocketsphinx
```

The recognizer.py node that this installs is not executable by default, so we need to manually make it executable:
```bash
roscd pocketsphinx/nodes
sudo chmod +x recognizer.py
```

####LibSVM####
LibSVM is used for detecting poses in the Mimic Game. Download it like so:
```bash
sudo apt-get install libsvm3 libsvm-dev libsvm-tools
```

####Nao Autism Games####

Download and compile this repository:
```bash
cd ~
git clone https://github.com/tristanbell/nao-autism.git
cd nao-autism
catkin_make
cmake tools/settings\ editor/CMakeLists.txt
make -C tools/settings\ editor
```
!!!
Also after libsvm has been installed, you will have to move the learner package out of the src folder, run catkin_make (I have to run it twice, for some reason) and then place the learner package back into the projects src folder. For some reason, catkin_make doesn't obey the build_depend tags in the project xml file (although it is probably a misuse of it).

The commands I used to successfully catkin_make where the following.:

mv src/learner .
catkin_make
catkin_make
mv learner/ src/
catkin_make
!!!

Create a new directory for the supporting Nao drivers, then make a new file called rosinstall.txt for installing the drivers:
```bash
mkdir ~/nao
cd ~/nao

echo "- git:
   uri: https://github.com/ahornung/humanoid_msgs
   local-name: humanoid_msgs
- git:
   uri: https://github.com/ahornung/nao_robot
   local-name: nao_robot
- git:
   uri: https://github.com/ahornung/nao_common
   local-name: nao_common" > rosinstall.txt
```
Then run rosinstall to install the relevant packages, making sure to link this workspace with our nao-autism workspace, then compile them:
```bash
rosinstall . ~/nao-autism/devel rosinstall.txt
source setup.bash
rosdep install humanoid_msgs nao_robot nao_common
rosmake humanoid_msgs nao_robot nao_common
```
In order to run our games (or any of the Nao drivers) you must `source ~/nao/setup.bash` first. If you wish to, add `source ~/nao/setup.bash` to the end of your `~/.bashrc` in order to allow you to run the games from any new terminal window.

Running the Emotion Games
-------------------------

ROS programs are normally run through the command line. In order for our program to run, several others must also be running at the same time. The Kinect must also be running in order for the Copy the Robot game to work.

1. First, plug in the Kinect to a USB port.
2. To start the Kinect, open a terminal window and type `roslaunch openni_launch openni.launch`
3. In a new terminal window, type

```bash
    LD_LIBRARY_PATH=$NAOQI_LIBRARY_PATH
    roslaunch ~/nao-autism/launch/run_nao.launch
```
4. Then, in a new terminal window, make sure you are in the nao directory (`cd ~/nao`) then type `source setup.bash`
5. When running for the first time, you will need a configuration file for the game. We have provided one (data.json) as a starting point, but you can make one yourself if you wish. To make one, type `~/nao-autism/tools/settings\ editor/settings_editor` to open the settings editor, then click File > New to generate a basic configuration file. Adjust any of the settings as you see fit, and when you're finished click File > Save As. Save your new configuration file (name it something like "data.json") in the nao-autism folder. Then close the settings editor.
6. Start the emotion recognition games with `roslaunch emotion_game emotion_game.launch`. It will bring up a file chooser, where you must find and select your data.json configuration file. Once opened, the emotion games will begin.

Running the Motion Controller
-----------------------------

The Mimicker program allows a user to control the Nao using a Kinect. To run it (assuming you have already done `source ~/nao/setup.bash`), do the following:

1. With the Kinect plugged in to a USB port, open a terminal window and type `roslaunch openni_launch openni.launch`
2. In another window, do `roslaunch emotion_game kinect_nao.launch`
3. Finally, in a new terminal window type `roslaunch emotion_game kinect_control.launch`

Once it is running, copy the Nao by putting your hands on your head. Once the Kinect recognises someone doing this gesture, it will initialise a virtual 'control box' around this user, giving them control over the robot.

Using the Motion Controller
---------------------------

The kinect motion controller (Mimicker) works in two ways: moving the Nao's arms and making the Nao walk. While stationary, move your arms and the Nao will copy your movements. There are various motions to make it walk:

+ Step forward with either foot to make the Nao walk forward
+ Step backward with either foot to make the Nao walk backward
+ Step to the left with your left foot to make the Nao shuffle to the left
+ Step to the right with your right foot to make the Nao shuffle to the right
+ Turning left or right will make the Nao turn left or right, respectively. This also works while the Nao is walking forwards or backwards
