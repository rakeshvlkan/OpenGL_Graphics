

Instanced Rendering:

This is application show the rendering performance difference between  No Instancing, Shader Instancing and Hardware Instancing methods. 

1. No Instancing:
    > Each instance of the object is drawn individually.
	> Two calls to glUniform3fv to set the attributes for the current instance
	> One call to glDrawElements to render the current instance
	
2. Shader Instancing:
   
   > Two calls to glUniform3fv to set the attributes for the current batch of instances
   >One call to glDrawElements to render the current batch of instance
	In order to support drawing 100 instances of the object the sample creates a vertex buffer object that contains the vertices of 100 copies of the object. 
	The data for each vertex is extended to additionally contain an instance id. This id is then used to load per instance attributes from an 
	array of uniform shaders variables to adjust position, rotation and color of each instance.	Further on, in addition to the vertex buffer object, 
	a buffer is created that contains the indices for the 100 copies of the original index buffer.
	
3. Hardware Instancing:
   > Objects are drawn using just one call to glDrawElementsInstanced() 
	To setup this draw call additional per instance vertex attributes are setup by two calls to each glEnableVertexAttribArray, 
	glVertexAttribPointer and glVertexAttribDivisor. This setup does bring in per instance data as additional per vertex attributes to the vertex shader.
  
Currently "No Instancing" and "Hardware Instancing" methdos are implemented but "Shader Instancing" is not implemented due to some issues in sending 100 instances on each draw call.
Currently I am fixing this issue and update soon.

Also here I have created framework so that if anyone wants to create an application using OpenGL(glfw and glew), they can use this framework and start creating application. 
I have a plan to add support for "glut" and vulkan libraryin this framework. I will update the code once it is ready. 

Dependencies: 
Assimp
freetype  : Used for text rendering
GLEW
GLFW
STB Image
glm

Execution Steps:
Windows:
Open OpenGL_Graphics.sln in any one of the mode and execute. 

Note: Please copy all dependency dlls to build folder