# Stereo Delay Plugin with Juce

Graham Seamans - gseamans@pdx.edu

### Overview

This is a stereo delay plugin. It has two channels with individual delay buffers and uses IIR LPF's to make a clean warm sound. As it's a Juce plugin it should be able to compine and run in basically any environment, but I have only been able to test it as a standalone plugin on OSX and in Logic Pro.

### Running the Project

### Testing

For testing I've been using the plugin as an AudioUnit in Logic Pro. It has been working without any issues for me there.

### Thoughts

I would say that pretty much everything worked. I am a little dissapointed with how the filter movement is really chunky sounding, but it's a convencience feature as I don't remember ever wanting to automate this parameter while making music. I'm actually super satisfied with the result, as it's a very nice sounding stereo delay which was my goal.

The more time I spent on this the smaller it's become, which is a good sign, but now the majority of the code for the project is for managing the GUI.

I'm really excited about this project as it's something that I'm actually planning to use (I really like the sound of the IIR filters), and I may add some features to it as well in the future, such as a mild distorion on the wet signal or maybe a chorus. I will need to restructure some of the project to do this, so I've decided to leave the project as it is for now.
