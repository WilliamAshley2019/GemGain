# GemGain
This is a simple gain knob

GemGain - A GPLv3 Gain Plugin for JUCE and VST3
An open-source digital audio gain plugin for precise level control.
GemGain is a lightweight, high-performance digital audio gain plugin developed using the powerful JUCE framework and the Steinberg VST3 SDK. Designed for transparent and precise volume manipulation, this plugin is ideal for a wide range of audio applications, from mixing and mastering to basic level adjustments. Released under the GNU General Public License v3.0, GemGain serves as a clear, well-documented example for developers interested in open-source audio development.

Features
Precise Gain Control: Adjust the output level with a smooth and responsive gain slider.

Input/Output Meters: Visual feedback on signal levels with peak-hold functionality.

Low CPU Usage: Designed for efficiency, making it suitable for use on multiple tracks in a project.

Cross-Platform Compatibility: Builds natively on Windows, macOS, and Linux.

Resizable GUI: A modern, scalable user interface to fit any screen resolution.

Audio Engineering Explained
A digital audio gain plugin performs a simple but fundamental function: it multiplies every incoming audio sample by a constant value. This value, known as the gain factor, is determined by the user's gain control setting.

The gain control on the user interface is typically represented in decibels (dB), which is a logarithmic unit. This is because the human ear perceives loudness on a logarithmic scale. To convert the linear gain factor to the decibel value shown on the slider, the following formula is used:

Gain (dB)=20⋅log 
10
​
 (gain factor)
Conversely, to apply the gain to the audio samples, the plugin converts the user's dB setting back to a linear gain factor:

Gain factor=10 
Gain (dB)/20
 
This process is considered "transparent" because it does not introduce any non-linear distortion, unlike plugins such as compressors or saturators. Its sole purpose is to increase or decrease the amplitude of the audio signal uniformly.

Licensing and Copyright
This project, GemGain, is licensed under the GNU General Public License v3.0. A full copy of the license can be found in the LICENSE file in this repository.

Third-Party SDKs
This software relies on two crucial third-party libraries, each with its own licensing requirements that are compatible with this GPLv3 release:

JUCE Framework:
This project uses JUCE under a permissive license that allows for linking with GPL-licensed software. For your own commercial closed-source projects, you would need to acquire a different JUCE license. For more information, please refer to the official JUCE Licensing Page.

Steinberg VST3 SDK:
The VST3 SDK license is permissive and explicitly permits its use in open-source software, including projects released under the GPL. By cloning this repository, you agree to comply with the terms of the VST3 SDK license. The full text of the license is included in the SDK itself.

Please ensure you adhere to the licensing terms of both JUCE and the VST3 SDK when using or distributing this software.

Requirements
JUCE

Steinberg VST3 SDK

A C++ compiler that supports C++17 or later.

CMake (recommended) or a supported IDE (e.g., Xcode, Visual Studio).

Building the Plugin
Clone this repository:
git clone https://github.com/WilliamAshley2019/SimpleGain.git

Follow the JUCE instructions to set up your project with the VST3 SDK.

Open the project file in your preferred IDE and build the plugin.

Contributing
We welcome contributions! Feel free to fork the repository, make changes, and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

© 2025 William Ashley
