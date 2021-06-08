# Stereo Delay Plugin with Juce

Graham Seamans - gseamans@pdx.edu

### Overview

This is a stereo delay plugin. It has two channels with individual delay buffers and uses IIR LPF's to make a clean warm sound. As it's a Juce plugin it should be able to compine and run in basically any environment, but I have only been able to test it as a standalone plugin on OSX and in Logic Pro.

### Building and Running The Project

* For OSX and Windows It seems like it's necissary to install Juce and open the `Delay_Plugin.jucer` file. After this choose which builder you want to use from the menu on the left hand side, click the icon of XCode or VisualStuido in the top middle of the GUI, build in those enviroments, and you're all good to go.
* For linux I had ProJuicer make a MakeFile, who currently lives in `./LinuxMakeFile/`. In that directory you can see the makefile. make this MakeFile and there should be a build folder in the current directory which contains a VST3 plugin. I'm not sure if there are any dependencies outside of this directory needed to build the file, but It worked first try for me. I do have the Juce library up in this directory, and I'm not sure how legal that is, so I plan to remove that from here very soon.


### Testing

For testing I've been using the plugin as an AudioUnit in Logic Pro, and I lightly tested a VST in Bitwig on Linux. It has been working without any issues for me there.

### Thoughts

I would say that pretty much everything worked. I am a little dissapointed with how the filter movement is really chunky sounding, but it's a convencience feature as I don't remember ever wanting to automate this parameter while making music. I'm actually super satisfied with the result, as it's a very nice sounding stereo delay which was my goal.

The more time I spent on this the smaller it's become, which is a good sign, but now the majority of the code for the project is for managing the GUI.

I'm really excited about this project as it's something that I'm actually planning to use (I really like the sound of the IIR filters). The parameters are currently only saved in memory, so I'm going to need to implement a way to store the current setting for saving so that it can be used for real. Additionally, I might add a mild distorion on the wet signal or maybe a chorus. I will need to restructure some of the project to do this, so I've decided to leave the project as it is for now.
