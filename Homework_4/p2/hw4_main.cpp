//
//  main.cpp
//  Texture template for Homework 4
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//



/*---------------------------------------------------------------------------------
Note,

- The code gives you some hints what to do. I added some comments
- The shader code is stored in two files. HW4_shader.vs/.fs
  You must edit this shader programs in order to get the shader code to work with textures. 

In addition:
- The class (file) ShaderFileUtils provides functions to load shader code from a file. 
- The class (file) ImgLoader provides a function to load a bitmap .bmp image from a file. 

-----------------------------------------------------------------------------------*/

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "ShaderFileUtils.h"
#include "ImgLoader.h"



// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;


/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;



// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];



// int loadAndCreateTexture(string path_and_file)
// {


// }
/*!
 Verifies wheterh a file [name] exits
 @param name - the path and the name of the file.
 */
bool SearchTexture (const std::string& name, string& new_name)
{
	new_name = "";

	bool exits = false;

    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
		new_name = name;
        exits = true;
		return exits;
    } else {
        f.close();
        exits = false;
    }



	int idx = name.find_first_of("/");
    string newstring = name.substr(idx+1, name.length() - 3);


	ifstream f2(newstring.c_str());
    if (f2.good()) {
        f2.close();
        exits = true;
    } else {
        f2.close();
        exits = false;
    }


	if(exits)
	{
		new_name = newstring;
	}


	return exits;
}

/**
This function checks your shader code
@param shader - the id of the shader
@param shader_type - type = GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
*/
bool CheckShaderLocal(GLuint shader, GLenum shader_type)
{
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint info_len = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

		if (info_len)
		{
			char* buf = (char*)malloc(info_len);
			if (buf) {
				glGetShaderInfoLog(shader, info_len, NULL, buf);
				cout << "Could not compile shader shader_type " << shader_type << ":\n" << buf << endl;
				free(buf);
			}
			glDeleteShader(shader);
			shader = 0;
		}
		return false;
	}
	return true;

}




/*!
This function creates a single square
 */
void createSquare(void)
{
	// float* vertices = new float[18];  // Vertices for our square
	// float *colors = new float[18]; // Colors for our vertices

	// vertices[0] = -0.5; vertices[1] = -0.5; vertices[2] = 0.5; // Bottom left corner
	// colors[0] = 1.0; colors[1] = 1.0; colors[2] = 1.0; // Bottom left corner

	// vertices[3] = -0.5; vertices[4] = 0.5; vertices[5] = 0.5; // Top left corner
	// colors[3] = 1.0; colors[4] = 0.0; colors[5] = 0.0; // Top left corner

	// vertices[6] = 0.5; vertices[7] = 0.5; vertices[8] = 0.5; // Top Right corner
	// colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; // Top Right corner

	// vertices[9] = 0.5; vertices[10] = -0.5; vertices[11] = 0.5; // Bottom right corner
	// colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner

	// vertices[12] = -0.5; vertices[13] = -0.5; vertices[14] = 0.5; // Bottom left corner
	// colors[12] = 1.0; colors[13] = 1.0; colors[14] = 1.0; // Bottom left corner

	// vertices[15] = 0.5; vertices[16] = 0.5; vertices[17] = 0.5; // Top Right corner
	// colors[15] = 0.0; colors[16] = 1.0; colors[17] = 0.0; // Top Right corner


	/*---------------------------------------------------------------------------------
	  TODO:
	  - Add texture coordinates to the vertices above
	  - Assign the texture coordinates to a vertex buffer objects as discussed in class.
	    Note, they ned to be inside the same vbo in which the vertices are defined. 
	-----------------------------------------------------------------------------------*/
	float* vertices = new float[30];  // Vertices for our square
	float *colors = new float[18]; // Colors for our vertices

	vertices[0] = -0.5; vertices[1] = -0.5; vertices[2] = 0.5; vertices[3]=0.0; vertices[4]=0.0; // Bottom left corner
	colors[0] = 1.0; colors[1] = 1.0; colors[2] = 1.0; // Bottom left corner

	vertices[5] = -0.5; vertices[6] = 0.5; vertices[7] = 0.5; vertices[8]=0.0; vertices[9]=1.0; // Top left corner
	colors[3] = 1.0; colors[4] = 0.0; colors[5] = 0.0; // Top left corner

	vertices[10] = 0.5; vertices[11] = 0.5; vertices[12] = 0.5; vertices[13]=1.0; vertices[14]=1.0;// Top Right corner
	colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; // Top Right corner

	vertices[15] = 0.5; vertices[16] = -0.5; vertices[17] = 0.5; vertices[18]=1.0; vertices[19]=0.0;// Bottom right corner
	colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner

	vertices[20] = -0.5; vertices[21] = -0.5; vertices[22] = 0.5; vertices[23]=0.0; vertices[24]=0.0;// Bottom left corner
	colors[12] = 1.0; colors[13] = 1.0; colors[14] = 1.0; // Bottom left corner

	vertices[25] = 0.5; vertices[26] = 0.5; vertices[27] = 0.5; vertices[28]=1.0; vertices[29]=1.0;// Top Right corner
	colors[15] = 0.0; colors[16] = 1.0; colors[17] = 0.0; // Top Right corner


	glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it


	glGenBuffers(2, vboID); // Generate our Vertex Buffer Object

							// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL); // Set up our vertex attributes pointer
		glEnableVertexAttribArray(0); // Disable our Vertex Array Object


// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat),(const GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


								  //Color
	//glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	//glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	//glEnableVertexAttribArray(2); // Enable the second vertex attribute array

	glBindVertexArray(0); // Disable our Vertex Buffer Object


	delete[] vertices; // Delete our vertices from memory


	/*---------------------------------------------------------------------------------
	TODO:
	- Load the texture
	- Create a texture object
	- Set the correct texture unit active
	- Set all texture parameters as requried
	- Load the texture to your graphics card
	- Create a texture uniform variable
	-----------------------------------------------------------------------------------*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	int channels;
	unsigned int width, height;
	//unsigned char* gradient = ImgLoader::Load("./color_gradient.bmp", width, height,channels);
	unsigned char* gradient = ImgLoader::Load("./color_gradient.bmp", width, height, channels);
	
    
    //**********************************************************************************************
    // Texture generation
    
    // Generate a texture, this function allocates the memory and
    // associates the texture with a variable.
	GLuint texture0;
    glGenTextures(1, &texture0 );
    int tex_idx0 = glGetUniformLocation(program, "tex_gradient" );
    glActiveTexture(GL_TEXTURE0);

    
    // Set a texture as active texture.
    glBindTexture( GL_TEXTURE_2D, texture0 );
    glUniform1i(tex_idx0, 0);
    
    // Change the parameters of your texture units.
    //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    
    
    // Create a texture and load it to your graphics hardware. This texture is automatically associated
    // with texture 0 and the textuer variable "texture" / the active texture.
	//cout << channels << "\n";
    if(channels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, gradient);
    else if(channels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, gradient);
    
    //**********************************************************************************************
    // Create a midmap texture pyramid and load it to the graphics hardware.
    // Note, the MIN and MAG filter must be set to one of the available midmap filters.
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, gradient);
    
    // Delete your loaded data
    //free( gradient);
    
    // Return the texture.
    //return _texture;
	width = 0; height = 0; channels = 0;
	//unsigned char* landscape = ImgLoader::Load("../data/textures/texture_isu.bmp", width, height, channels);
	unsigned char* landscape = ImgLoader::Load("./landscape.bmp", width, height, channels);
	GLuint texture1;
	glGenTextures(1, &texture1);
	int tex_idx1 = glGetUniformLocation(program, "tex_landscape");
	glActiveTexture(GL_TEXTURE1);


	// Set a texture as active texture.
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(tex_idx1, 1);

	// Change the parameters of your texture units.
	//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Create a texture and load it to your graphics hardware. This texture is automatically associated
	// with texture 0 and the textuer variable "texture" / the active texture.
	//cout << channels << "\n";
	if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, landscape);
	else if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, landscape);

	//**********************************************************************************************
	// Create a midmap texture pyramid and load it to the graphics hardware.
	// Note, the MIN and MAG filter must be set to one of the available midmap filters.
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, landscape);

	//unsigned char* landscape = ImgLoader::Load("../data/textures/texture_isu.bmp", width, height, channels);
	unsigned char* animal = ImgLoader::Load("./animal.bmp", width, height, channels);
	GLuint texture2;
	glGenTextures(1, &texture2);
	int tex_idx2 = glGetUniformLocation(program, "tex_animal");
	glActiveTexture(GL_TEXTURE2);


	// Set a texture as active texture.
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(tex_idx2, 2);

	// Change the parameters of your texture units.
	//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Create a texture and load it to your graphics hardware. This texture is automatically associated
	// with texture 0 and the textuer variable "texture" / the active texture.
	//cout << channels << "\n";
	if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, animal);
	else if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, animal);

	// Delete your loaded data
	free(animal);

}







/*!
 This code renders the plane
 */
void renderSquare(void)
{

	glUseProgram(program);

	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object

	glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square

	glBindVertexArray(0); // Unbind our Vertex Array Object

	glUseProgram(0);

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
	createSquare();
    
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
	static const string vertex_code = ShaderFileUtils::LoadFromFile("./hw4_shader.vs");
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = ShaderFileUtils::LoadFromFile("./hw4_shader.fs");
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
	bool ret = CheckShaderLocal(fs, GL_VERTEX_SHADER);
	if (!ret) { cout << "Problems compiling GL_VERTEX_SHADER" << endl; }
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
	ret = CheckShaderLocal(vs, GL_VERTEX_SHADER);
	if (!ret) { cout << "Problems compiling GL_VERTEX_SHADER" << endl; }
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    



    glBindAttribLocation(program, 0, "in_Position");
    //glBindAttribLocation(program, 1, "in_Color");
    glBindAttribLocation(program, 1, "in_tex_coord");
    glBindAttribLocation(program, 2, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model 
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
       
		// This line renders your Ppolygon model
		renderSquare();
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}
