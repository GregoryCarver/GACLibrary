# S.T.A.R.(STEM Teaching Assistant Realm) Readme
1. First way to compile:
    - Create visual studio project
    - Put dependencies folder in source location of project
    - Put source and header folders in source
    - May have to right click and add to project
    - Open Project properties, under Linker/general/Additional Library Directories add: \$(SolutionDir)Dependencies\GLFW\lib-vc2019;$(SolutionDir)Dependencies\GLEW\lib\Release\WIN32;
    - Under Linker/input/Additional Dependencies add: glfw3.lib;glew32s.lib;opengl32.lib
    - Under C/C++/general/Additional Include Directories add: \$(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include;%(AdditionalIncludeDirectories)
    - Under C/C++/Preprocessor add: GLEW_STATIC

2. Second way to compile:
    - Pull from github
    - Make sure to put dependencies folder in source folder still
