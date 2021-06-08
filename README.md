# Stereo Delay Plugin with Juce

Graham Seamans - gseamans@pdx.edu

### Overview

This is a stereo delay plugin. It has two channels with individual delay buffers and uses IIR LPF's to make a clean warm sound. As it's a Juce plugin it should be able to compile and run in basically any environment, but I have only been able to test it in OSX as a standalone plugin and in Logic Pro, and little bit in Linux on Bitwig Studio.

### Building and Running The Project

* For OSX and Windows It seems that it's necissary to install Juce and open the `Delay_Plugin.jucer` file. After this choose which builder you want to use from the menu on the left hand side, click the icon of XCode or VisualStuido in the top middle of the GUI, build in those enviroments, and you're all good to go.
* For linux I had ProJuicer make a MakeFile, who currently lives in `./LinuxMakeFile/`. If you make this MakeFile it should make a build folder in the current directory which contains a VST3 plugin. I'm not sure if there are any dependencies outside of this repo needed to build. I do have the Juce library dependencies hosted in this directory for building on Linux, and I'm not sure how legal that is, so I plan to remove that from here very soon.

### Demos

There is an example of a dry(ish) and wet guitar in the `demoFiles` directory.

### Testing

For testing I've been using the plugin as an AudioUnit in Logic Pro, and I lightly tested a VST in Bitwig on Linux. It has been working without any issues for me there.

### License

This project is under the GNU General Public License v2.0. Check the `LICENSE` file in the root of this repo for more details.

### Thoughts

I'm stoken on this plugin. I am a little dissapointed with how the filter movement is really glitchy sounding, but it's a convencience feature as I don't remember ever wanting to automate this parameter while making music. I might fix this in the future, but for now I'm satisfied as it's a nice sounding stereo delay which was my goal.

The more time I spent on this the smaller it's become, which is a good sign, but now the majority of the code for the project is for managing the GUI.

I'm really excited about this project as it's something that I'm actually planning to use (I really like the sound of the IIR filters). Additionally, I might add a mild distorion on the wet signal or maybe a chorus though this will require that I restructre things some. 
