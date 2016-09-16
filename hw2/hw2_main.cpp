//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

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

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];
unsigned tri_strip_size=105;
unsigned tri_size=216;
/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    // use the vertex array object vaoID[0] for this model representation
    
    


    
    //TODO:
    float* vertices = new float[tri_strip_size];  // Vertices for our square
    float *colors = new float[tri_strip_size]; // Colors for our vertices
    for(int i=0;i<tri_strip_size;i++){
	if(i%3==0)
	    colors[i]=1.0;
	else
	    colors[i]=0.0;
    }
    //point 0
    vertices[0] = 0; vertices[1] = 1; vertices[2] = 0;
    //point 1
    vertices[3] = 0; vertices[4] = 3; vertices[5] = 0;
    //point 2
    vertices[6] = 1; vertices[7] = 1; vertices[8] = 0;
    //point 3
    vertices[9] = 1; vertices[10] = 3; vertices[11] = 0;
    //point 4
    vertices[12] = 1; vertices[13] = 1; vertices[14] = 1;
    //point 5
    vertices[15] = 1; vertices[16] = 3; vertices[17] = 1;
    //point 6
    vertices[18] = 0; vertices[19] = 1; vertices[20] = 1;
    //point 7
    vertices[21] = 0; vertices[22] = 3; vertices[23] = 1;
    //point 0
    vertices[24] = 0; vertices[25] = 1; vertices[26] = 0;
    //point 1
    vertices[27] = 0; vertices[28] = 3; vertices[29] = 0;
    //point 7
    vertices[30] = 0; vertices[31] = 3; vertices[32] = 1;
    //point 3
    vertices[33] = 1; vertices[34] = 3; vertices[35] = 0;
    //point 5
    vertices[36] = 1; vertices[37] = 3; vertices[38] = 1;
    //point 2
    vertices[39] = 1; vertices[40] = 1; vertices[41] = 0;
    //point 4
    vertices[42] = 1; vertices[43] = 1; vertices[44] = 1;
    //point 0
    vertices[45] = 0; vertices[46] = 1; vertices[47] = 0;
    //point 8
    vertices[48] = 3; vertices[49] = 1; vertices[50] = 0;
    //point 9
    vertices[51] = 3; vertices[52] = 1; vertices[53] = 1;
    //point 0
    vertices[54] = 0; vertices[55] = 1; vertices[56] = 0;
    //point 10
    vertices[57] = 1; vertices[58] = 1; vertices[59] = 2;
    //point 11
    vertices[60] = 0; vertices[61] = 1; vertices[62] = 2;
    //point 0
    vertices[63] = 0; vertices[64] = 1; vertices[65] = 0;
    //point 13
    vertices[66] = 0; vertices[67] = 0; vertices[68] = 2;
    //point 12
    vertices[69] = 0; vertices[70] = 0; vertices[71] = 0;
    //point 14
    vertices[72] = 1; vertices[73] = 0; vertices[74] = 2;
    //point 15
    vertices[75] = 3; vertices[76] = 0; vertices[77] = 1;
    //point 12
    vertices[78] = 0; vertices[79] = 0; vertices[80] = 0;
    //point 16
    vertices[81] = 3; vertices[82] = 0; vertices[83] = 0;
    //point 8
    vertices[84] = 3; vertices[85] = 1; vertices[86] = 0;
    //point 15
    vertices[87] = 3; vertices[88] = 0; vertices[89] = 1;
    //point 9
    vertices[90] = 3; vertices[91] = 1; vertices[92] = 1;
    //point 14
    vertices[93] = 1; vertices[94] = 0; vertices[95] = 2;
    //point 10
    vertices[96] = 1; vertices[97] = 1; vertices[98] = 2;
    //point 13
    vertices[99] = 0; vertices[100] = 0; vertices[101] = 2;
    //point 11
    vertices[102] = 0; vertices[103] = 1; vertices[104] = 2;
    // //point 6
    // vertices[45] = 0; vertices[46] = 1; vertices[47] = 1;
    // colors[45] = 1.0; colors[46] = 0.0; colors[47] = 0.0;
    // //point 7
    // vertices[45] = 0; vertices[46] = 3; vertices[47] = 1;
    // colors[45] = 1.0; colors[46] = 0.0; colors[47] = 0.0;
    
    
    glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(4, vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, tri_strip_size * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
  
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, tri_strip_size * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    delete [] colors;
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createTriangleModel(void)
{
    // use the vertex array object vaoID[1] for this model representation
  
    //TODO:
    float* vertices = new float[tri_size];  // Vertices for our square
    float *colors = new float[tri_size]; // Colors for our vertices
    for(int i=0;i<tri_size;i++){
	if(i%3==2)
	    colors[i]=1.0;
	else
	    colors[i]=0.0;
    }
    //point 0
    vertices[0] = 0; vertices[1] = 1; vertices[2] = 0;
    //point 1
    vertices[3] = 0; vertices[4] = 3; vertices[5] = 0;
    //point 3
    vertices[6] = 1; vertices[7] = 3; vertices[8] = 0;
    //point 0
    vertices[9] = 0; vertices[10] = 1; vertices[11] = 0;
    //point 3
    vertices[12] = 1; vertices[13] = 3; vertices[14] = 0;
    //point 2
    vertices[15] = 1; vertices[16] = 1; vertices[17] = 0;
    //point 3
    vertices[18] = 1; vertices[19] = 3; vertices[20] = 0;
    //point 2
    vertices[21] = 1; vertices[22] = 1; vertices[23] = 0;
    //point 4
    vertices[24] = 1; vertices[25] = 1; vertices[26] = 1;
    //point 3
    vertices[27] = 1; vertices[28] = 3; vertices[29] = 0;
    //point 4
    vertices[30] = 1; vertices[31] = 1; vertices[32] = 1;
    //point 5
    vertices[33] = 1; vertices[34] = 3; vertices[35] = 1;
    //point 4
    vertices[36] = 1; vertices[37] = 1; vertices[38] = 1;
    //point 5
    vertices[39] = 1; vertices[40] = 3; vertices[41] = 1;
    //point 6
    vertices[42] = 0; vertices[43] = 1; vertices[44] = 1;
    //point 5
    vertices[45] = 1; vertices[46] = 3; vertices[47] = 1;
    //point 6
    vertices[48] = 0; vertices[49] = 1; vertices[50] = 1;
    //point 7
    vertices[51] = 0; vertices[52] = 3; vertices[53] = 1;
    //point 7
    vertices[54] = 0; vertices[55] = 3; vertices[56] = 1;
    //point 6
    vertices[57] = 0; vertices[58] = 1; vertices[59] = 1;
    //point 1
    vertices[60] = 0; vertices[61] = 3; vertices[62] = 0;
    //point 1
    vertices[63] = 0; vertices[64] = 3; vertices[65] = 0;
    //point 6
    vertices[66] = 0; vertices[67] = 1; vertices[68] = 1;
    //point 0
    vertices[69] = 0; vertices[70] = 1; vertices[71] = 0;
    //point 7
    vertices[72] = 0; vertices[73] = 3; vertices[74] = 1;
    //point 5
    vertices[75] = 1; vertices[76] = 3; vertices[77] = 1;
    //point 3
    vertices[78] = 1; vertices[79] = 3; vertices[80] = 0;
    //point 3
    vertices[81] = 1; vertices[82] = 3; vertices[83] = 0;
    //point 7
    vertices[84] = 0; vertices[85] = 3; vertices[86] = 1;
    //point 1
    vertices[87] = 0; vertices[88] = 3; vertices[89] = 0;
    //point 0
    vertices[90] = 0; vertices[91] = 1; vertices[92] = 0;
    //point 10
    vertices[93] = 1; vertices[94] = 1; vertices[95] = 2;
    //point 11
    vertices[96] = 0; vertices[97] = 1; vertices[98] = 2;
    //point 0
    vertices[99] = 0; vertices[100] = 1; vertices[101] = 0;
    //point 10
    vertices[102] = 1; vertices[103] = 1; vertices[104] = 2;
    //point 9
    vertices[105] = 3; vertices[106] = 1; vertices[107] = 1;
    //point 0
    vertices[108] = 0; vertices[109] = 1; vertices[110] = 0;
    //point 9
    vertices[111] = 3; vertices[112] = 1; vertices[113] = 1;
    //point 8
    vertices[114] = 3; vertices[115] = 1; vertices[116] = 0;
    //point 0
    vertices[99] = 0; vertices[100] = 1; vertices[101] = 0;
    //point 10
    vertices[102] = 1; vertices[103] = 1; vertices[104] = 2;
    //point 9
    vertices[105] = 3; vertices[106] = 1; vertices[107] = 1;
    //point 0
    vertices[108] = 0; vertices[109] = 1; vertices[110] = 0;
    //point 9
    vertices[111] = 3; vertices[112] = 1; vertices[113] = 1;
    //point 8
    vertices[114] = 3; vertices[115] = 1; vertices[116] = 0;
    //point 9
    vertices[117] = 3; vertices[118] = 1; vertices[119] = 1;
    //point 8
    vertices[120] = 3; vertices[121] = 1; vertices[122] = 0;
    //point 16
    vertices[123] = 3; vertices[124] = 0; vertices[125] = 0;
    //point 16
    vertices[126] = 3; vertices[127] = 0; vertices[128] = 0;
    //point 9
    vertices[129] = 3; vertices[130] = 1; vertices[131] = 1;
    //point 15
    vertices[132] = 3; vertices[133] = 0; vertices[134] = 1;
    //point 15
    vertices[135] = 3; vertices[136] = 0; vertices[137] = 1;
    //point 16
    vertices[138] = 3; vertices[139] = 0; vertices[140] = 0;
    //point 12
    vertices[141] = 0; vertices[142] = 0; vertices[143] = 0;
    //point 12
    vertices[144] = 0; vertices[145] = 0; vertices[146] = 0;
    //point 15
    vertices[147] = 3; vertices[148] = 0; vertices[149] = 1;
    //point 14
    vertices[150] = 1; vertices[151] = 0; vertices[152] = 2;
    //point 14
    vertices[153] = 1; vertices[154] = 0; vertices[155] = 2;
    //point 12
    vertices[156] = 0; vertices[157] = 0; vertices[158] = 0;
    //point 13
    vertices[159] = 0; vertices[160] = 0; vertices[161] = 2;
    //point 12
    vertices[162] = 0; vertices[163] = 0; vertices[164] = 0;
    //point 13
    vertices[165] = 0; vertices[166] = 0; vertices[167] = 2;
    //point 11
    vertices[168] = 0; vertices[169] = 1; vertices[170] = 2;
    //point 11
    vertices[171] = 0; vertices[172] = 1; vertices[173] = 2;
    //point 12
    vertices[174] = 0; vertices[175] = 0; vertices[176] = 0;
    //point 0
    vertices[177] = 0; vertices[178] = 1; vertices[179] = 0;
    //point 13
    vertices[180] = 0; vertices[181] = 0; vertices[182] = 2;
    //point 11
    vertices[183] = 0; vertices[184] = 1; vertices[185] = 2;
    //point 10
    vertices[186] = 1; vertices[187] = 1; vertices[188] = 2;
    //point 10
    vertices[189] = 1; vertices[190] = 1; vertices[191] = 2;
    //point 13
    vertices[192] = 0; vertices[193] = 0; vertices[194] = 2;
    //point 14
    vertices[195] = 1; vertices[196] = 0; vertices[197] = 2;
    //point 14
    vertices[198] = 1; vertices[199] = 0; vertices[200] = 2;
    //point 10
    vertices[201] = 1; vertices[202] = 1; vertices[203] = 2;
    //point 9
    vertices[204] = 3; vertices[205] = 1; vertices[206] = 1;
    //point 9
    vertices[207] = 3; vertices[208] = 1; vertices[209] = 1;
    //point 14
    vertices[210] = 1; vertices[211] = 0; vertices[212] = 2;
    //point 15
    vertices[213] = 3; vertices[214] = 0; vertices[215] = 1;      
    // colors[45] = 1.0; colors[46] = 0.0; colors[47] = 0.0;
    // //point 7
    // vertices[45] = 0; vertices[46] = 3; vertices[47] = 1;
    // colors[45] = 1.0; colors[46] = 0.0; colors[47] = 0.0;
    
    
    glGenVertexArrays(2, &vaoID[1]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it
    
    
    //glGenBuffers(4, vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, tri_size * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
  
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[3]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, tri_size * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    delete [] colors;
    
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);
        
	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0 ,  tri_strip_size/3);


    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[1]);
        

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY POLYGONS YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0 ,tri_size/3);

    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
    renderTriangleStripModel();

    createTriangleModel();
    renderTriangleModel();
    
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
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
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
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        

		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
		// This line renders your Ppolygon model
        renderTriangleModel();
        
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
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

