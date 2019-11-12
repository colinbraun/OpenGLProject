# OpenGLProject
An OpenGL project for the purpose of learning

To build/run in a non Microsoft Visual Studio 2019 environment (I.E. eclipse, previous versions of MSVS, etc.) it is necessary to get a glfw.lib file to replace the one that comes with this project (though using something other than visual studio would require resolving other issues, like linking and includes). Source or binaries for the glfw.lib file can be found at https://www.glfw.org/download.html (once again, only if necessary).

Note: It is probably best to download the source package and create the lib file with CMake if the binaries do not work.

For MS Visual Studio 2019:
Open the solution in Microsoft Visual Studio 2019 (earlier version may or may not work).
Determine what version of OpenGL your hardware supports (google how to do this if necessary). 
Set the correct major and minor version hints in OpenGLProject.cpp, and set the correct value in fragmentShader.fs and vertexShader.vs (the first lines) I will try to make this process automatic as I develop so it doesn't need to be manually changed.

Then build the solution and run, and hopefully it will work.
