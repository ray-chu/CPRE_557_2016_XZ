// Std. Includes
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <string>
#include <iostream>
#include <utility>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

// test timer include
#include <time.h>

// Properties
GLuint screenWidth = 800, screenHeight = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

bool in_frustum(glm::mat4 M, glm::vec3&p);
GLuint loadCubemap(vector<const GLchar*>&faces);
bool CheckCollision(glm::vec3 &one, glm::vec3 &two,glm::vec3 one_size, glm::vec3 two_size);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
glm::vec3 lightPos(0.0f, 50.0f, 10.0f);
glm::vec3 lightPos2(0.0f, 0.0f, 100.0f);
glm::vec3 model_pos(0.0f,-8.0f,0.0f);
GLfloat model_yaw[2]={0.0f,0.0f};
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
bool collision_detect=false;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// The MAIN function, from here we start our application and run our Game loop
int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Space Exploration", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    // Options
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader1("./shaders/spaceship_loading.vs", "./shaders/spaceship_loading.frag");
    Shader shader2("./shaders/spaceship_loading.vs", "./shaders/spaceship_loading.frag");
    Shader shader3("./shaders/model_loading.vs", "./shaders/model_loading.frag");
    Shader skyboxShader("./shaders/skybox.vs", "./shaders/skybox.frag");
    // GLfloat skyboxVertices[] = {
    //     // Positions          
    //     -1.0f,  1.0f, -1.0f,
    //     -1.0f, -1.0f, -1.0f,
    //      1.0f, -1.0f, -1.0f,
    //      1.0f, -1.0f, -1.0f,
    //      1.0f,  1.0f, -1.0f,
    //     -1.0f,  1.0f, -1.0f,
  
    //     -1.0f, -1.0f,  1.0f,
    //     -1.0f, -1.0f, -1.0f,
    //     -1.0f,  1.0f, -1.0f,
    //     -1.0f,  1.0f, -1.0f,
    //     -1.0f,  1.0f,  1.0f,
    //     -1.0f, -1.0f,  1.0f,
  
    //      1.0f, -1.0f, -1.0f,
    //      1.0f, -1.0f,  1.0f,
    //      1.0f,  1.0f,  1.0f,
    //      1.0f,  1.0f,  1.0f,
    //      1.0f,  1.0f, -1.0f,
    //      1.0f, -1.0f, -1.0f,
   
    //     -1.0f, -1.0f,  1.0f,
    //     -1.0f,  1.0f,  1.0f,
    //      1.0f,  1.0f,  1.0f,
    //      1.0f,  1.0f,  1.0f,
    //      1.0f, -1.0f,  1.0f,
    //     -1.0f, -1.0f,  1.0f,
  
    //     -1.0f,  1.0f, -1.0f,
    //      1.0f,  1.0f, -1.0f,
    //      1.0f,  1.0f,  1.0f,
    //      1.0f,  1.0f,  1.0f,
    //     -1.0f,  1.0f,  1.0f,
    //     -1.0f,  1.0f, -1.0f,
  
    //     -1.0f, -1.0f, -1.0f,
    //     -1.0f, -1.0f,  1.0f,
    //      1.0f, -1.0f, -1.0f,
    //      1.0f, -1.0f, -1.0f,
    //     -1.0f, -1.0f,  1.0f,
    //      1.0f, -1.0f,  1.0f
    // };

    GLfloat skyboxVertices[] = {
        // Positions          
        -50.0f,  50.0f, -50.0f,
        -50.0f, -50.0f, -50.0f,
         50.0f, -50.0f, -50.0f,
         50.0f, -50.0f, -50.0f,
         50.0f,  50.0f, -50.0f,
        -50.0f,  50.0f, -50.0f,
  
        -50.0f, -50.0f,  50.0f,
        -50.0f, -50.0f, -50.0f,
        -50.0f,  50.0f, -50.0f,
        -50.0f,  50.0f, -50.0f,
        -50.0f,  50.0f,  50.0f,
        -50.0f, -50.0f,  50.0f,
  
         50.0f, -50.0f, -50.0f,
         50.0f, -50.0f,  50.0f,
         50.0f,  50.0f,  50.0f,
         50.0f,  50.0f,  50.0f,
         50.0f,  50.0f, -50.0f,
         50.0f, -50.0f, -50.0f,
   
        -50.0f, -50.0f,  50.0f,
        -50.0f,  50.0f,  50.0f,
         50.0f,  50.0f,  50.0f,
         50.0f,  50.0f,  50.0f,
         50.0f, -50.0f,  50.0f,
        -50.0f, -50.0f,  50.0f,
  
        -50.0f,  50.0f, -50.0f,
         50.0f,  50.0f, -50.0f,
         50.0f,  50.0f,  50.0f,
         50.0f,  50.0f,  50.0f,
        -50.0f,  50.0f,  50.0f,
        -50.0f,  50.0f, -50.0f,
  
        -50.0f, -50.0f, -50.0f,
        -50.0f, -50.0f,  50.0f,
         50.0f, -50.0f, -50.0f,
         50.0f, -50.0f, -50.0f,
        -50.0f, -50.0f,  50.0f,
         50.0f, -50.0f,  50.0f
    };
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    // Cubemap (Skybox)
    vector<const GLchar*> faces;
    faces.push_back("./skybox/sor_cwd/cwd_up.JPG");
    faces.push_back("./skybox/sor_cwd/cwd_up.JPG");
    faces.push_back("./skybox/sor_cwd/cwd_up.JPG");
    faces.push_back("./skybox/sor_cwd/cwd_up.JPG");
    faces.push_back("./skybox/sor_cwd/cwd_up.JPG");
    faces.push_back("./skybox/sor_cwd/cwd_dn.JPG");
    // faces.push_back("./skybox/right.jpg");
    // faces.push_back("./skybox/left.jpg");
    // faces.push_back("./skybox/top.jpg");
    // faces.push_back("./skybox/bottom.jpg");
    // faces.push_back("./skybox/back.jpg");
    // faces.push_back("./skybox/front.jpg");
    GLuint cubemapTexture = loadCubemap(faces);

    // Load models
    Model spaceship_model("./h2f/f.obj");
    Model rock_model("./asteroid/rock1/rock.obj");
    
    // Draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // //init a timer here
    // const int NUM_SECONDS = 2;
    // double time_counter = 0;

    // clock_t this_time = clock();
    // clock_t last_time = this_time;
    srand(time(NULL));
    vector<pair<glm::vec3,float>> rock_pos;
    for(int i=1;i<=10;i++){
       glm::vec3 tmp;
       tmp.z=model_pos.z+10.0f*i;
       float scale=i/10.0f;
       tmp.x=model_pos.x+scale*(rand()/(float)RAND_MAX*140.0f-70.0f);
       tmp.y=model_pos.y+scale*(rand()/(float)RAND_MAX*120.0f-60.0f);
       scale=(float)(rand()%5)+0.5;
       rock_pos.push_back(make_pair(tmp,scale));
    }
    
    //material properties
    //shader1.Use();
    // glUniform1i(glGetUniformLocation(shader1.Program, "material.diffuse"),  1);
    // glUniform1i(glGetUniformLocation(shader1.Program, "material.specular"), 1);
    glm::vec3 pointLightPositions[]={
       glm::vec3(0.0f,-5.0f,20.0f)
    };  

    // Game loop
    while(!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw skybox first
        glDepthMask(GL_FALSE);// Remember to turn depth writing off
        skyboxShader.Use();
	glm::mat4 skybox_model;
	skybox_model = glm::translate(skybox_model,model_pos);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(skybox_model));
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(skyboxShader.Program, "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);

        shader1.Use();   // <-- Don't forget this one!
	// // update timer here
	// this_time = clock();
        // time_counter += (double)(this_time - last_time);
        // last_time = this_time;
	// // update location
	// if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)){
	//    time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
	//    cout<<camera.Position.x<<","<<camera.Position.y<<","<<camera.Position.z<<"\n";
	// }
        // Draw the loaded model
        glm::mat4 model;
	//glm::vec3 model_pos=camera.Position+camera.Front;
	//glm::vec3 model_center(0.0f,-8.0f,20.0f);
	//glm::vec3 model_center(0.0f,-3.0f,-1.0f);
	//cout<<model_pos.x<<","<<model_pos.y<<","<<model_pos.z<<","<<endl;
	glm::vec3 spaceship_size(1.0f,0.4f,1.0f);
	glm::mat4 model_trans = glm::translate(model,model_pos);
	glm::mat4 model_rotate_z = glm::rotate(model, model_yaw[0],  glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 model_rotate_x = glm::rotate(model, model_yaw[1],  glm::vec3(1.0f,0.0f,0.0f));
	glm::mat4 model_scale = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
	model=model_trans*model_rotate_z*model_rotate_x*model_scale;
        //model = glm::translate(model,-model_center/*glm::vec3(0.1f, -1.0f, 3.3f)*/); // Translate it down a bit so it's at the center of the scene
        glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // Transformation matrices
        glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	//lightPos=model_pos;
//	lightPos2=model_pos+(0.0f, 20.0f, 100.0f);
//	glUniform3fv(glGetUniformLocation(shader1.Program, "lightPos"), 1, glm::value_ptr(lightPos));
//	glUniform3fv(glGetUniformLocation(shader1.Program, "lightPos2"), 1, glm::value_ptr(lightPos2));
	//glUniform1f(glGetUniformLocation(shader1.Program, "material.shininess"), 32.0f);


        // Directional light
        glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.direction"), 0.0f, 0.0f, -1.0f);
        glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.diffuse"), 10.0f, 10.0f,10.0f);
        glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.specular"), 50.0f, 50.0f, 50.0f);
	//lights
	//change light pos if needed
	if(pointLightPositions[0].z<model_pos.z-30.0f){
	   pointLightPositions[0].z=model_pos.z+(rand()/(float)RAND_MAX*60.0f);
	}
        glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].diffuse"), 5.0f, 5.0f, 5.0f);
        glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].specular"), 10.0f, 10.0f, 10.0f);
        glUniform1f(glGetUniformLocation(shader1.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shader1.Program, "pointLights[0].linear"), 0.09);
        glUniform1f(glGetUniformLocation(shader1.Program, "pointLights[0].quadratic"), 0.032);
        spaceship_model.Draw(shader1);

//	shader2.Use();
	glm::vec3 rock_size(1.0f,1.0f,1.0f);
	for(auto&i:rock_pos){
	   glm::mat4 model2;
	   if((camera.Front.z>0.0f) &&!in_frustum(projection*view,i.first)){	             
	   	     i.first.z=model_pos.z+60.0f;
	   	     i.first.x=(rand()/(float)RAND_MAX*140.0f-70.0f);
	   	     i.first.y=(rand()/(float)RAND_MAX*120.0f-60.0f);
	   	     i.second=(float)(rand()%5)+0.5;
	   }
	//model2 = glm::rotate(model2, 135.0f, glm::vec3(0.0, 1.0, 0.0));
	   //float scale=(float)(rand()%5)+1;
	   float scale=i.second;
	   if(CheckCollision(model_pos,i.first,spaceship_size,scale*rock_size))
	      collision_detect=true;
	   //cout<<"Collision Detection"<<endl;
	   model2 = glm::translate(model2,i.first)*glm::scale(model2, glm::vec3(scale, scale, scale));	// It's a bit too big for our scene, so scale it down
	//model2 = glm::translate(model2,glm::vec3(0.0f, 0.0f, 10.0f)); // Translate it down a bit so it's at the center of the scene
	   glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
	   glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	   glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	   //glUniform1f(glGetUniformLocation(shader1.Program, "material.shininess"), 32.0f);

	           // Directional light
	   glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.direction"), 0.0f, 0.0f, -1.0f);
	   glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
	   glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.diffuse"), 5.0f, 5.0f, 5.0f);
	   glUniform3f(glGetUniformLocation(shader1.Program, "dirLight.specular"), 0.8f, 0.8f, 0.8f);
	//lights
	   glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
	   glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].ambient"), 0.5f, 0.5f, 0.5f);
	   glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].diffuse"), 5.0f, 5.0f, 5.0f);
	   glUniform3f(glGetUniformLocation(shader1.Program, "pointLights[0].specular"), 0.5f, 0.5f, 0.5f);
	   glUniform1f(glGetUniformLocation(shader1.Program, "pointLights[0].constant"), 1.0f);
	   glUniform1f(glGetUniformLocation(shader1.Program, "pointLights[0].linear"), 0.09);
	   glUniform1f(glGetUniformLocation(shader1.Program, "pointLights[0].quadratic"), 0.032);
	   rock_model.Draw(shader1);
	}

	// //shader3.Use();
	// glm::mat4 model3;
	// //model2 = glm::rotate(model2, 135.0f, glm::vec3(0.0, 1.0, 0.0));
	// model3 = glm::translate(model3,glm::vec3(5.0f, 0.0f, 10.0f))*glm::scale(model3, glm::vec3(3.0f, 3.0f, 3.0f));	// It's a bit too big for our scene, so scale it down
	// //model2 = glm::translate(model2,glm::vec3(0.0f, 0.0f, 10.0f)); // Translate it down a bit so it's at the center of the scene
        // glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "model"), 1, GL_FALSE, glm::value_ptr(model3));
	// glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	
	
	// rock_model.Draw(shader2);


        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

#pragma region "User input"

// Moves/alters the camera positions based on user input
// void Do_Movement()
// {
//     // Camera controls
//     if(keys[GLFW_KEY_W])
//         camera.ProcessKeyboard(FORWARD, deltaTime);
//     if(keys[GLFW_KEY_S])
//         camera.ProcessKeyboard(BACKWARD, deltaTime);
//     if(keys[GLFW_KEY_A])
//         camera.ProcessKeyboard(LEFT, deltaTime);
//     if(keys[GLFW_KEY_D])
//         camera.ProcessKeyboard(RIGHT, deltaTime);
// }

void Do_Movement()
{
    // Camera controls
   float move_step=5.0f*deltaTime;
   glm::vec3 move_vec(move_step*glm::cos(-model_yaw[1])*glm::sin(-model_yaw[0]),move_step*glm::sin(-model_yaw[1]),move_step*glm::cos(-model_yaw[1])*glm::cos(-model_yaw[0]));
   float yaw_step=20.0f*deltaTime;
    if(keys[GLFW_KEY_F]){
       camera.set_view(true);
    }
    if(keys[GLFW_KEY_B])
       camera.set_view(false);
   if(collision_detect) return;
   // if(keys[GLFW_KEY_J])
   //    model_pos+=move_vec;
   //  if(keys[GLFW_KEY_K])
   //     model_pos-=move_vec;
   if(keys[GLFW_KEY_A])
      model_yaw[0]-=glm::radians(yaw_step);
    //model_pos.x+=move_step;
    if(keys[GLFW_KEY_D])
       model_yaw[0]+=glm::radians(yaw_step);
    if(keys[GLFW_KEY_W])
       model_pos+=move_vec;
    //model_yaw[1]+=glm::radians(yaw_step);
    if(keys[GLFW_KEY_S])
       model_pos-=move_vec;
    if(keys[GLFW_KEY_J])
       model_pos.x+=move_step;
    //model_yaw[1]+=glm::radians(yaw_step);
    if(keys[GLFW_KEY_K])
       model_pos.x-=move_step;
    if(keys[GLFW_KEY_MINUS])
       model_pos.y-=0.2*move_step;
    if(keys[GLFW_KEY_EQUAL])
       model_pos.y+=0.2*move_step;
    //model_yaw[1]-=glm::radians(yaw_step);
    if(keys[GLFW_KEY_C]){
       model_yaw[0]=0.0f;
       model_yaw[1]=0.0f;
    }
    //model_pos.x-=move_step;
    camera.Position=model_pos;
}

bool in_frustum(glm::mat4 M, glm::vec3&p) {
   glm::vec4 Pclip = M * glm::vec4(p, 1.);
   return abs(Pclip.x) < Pclip.w && 
	  abs(Pclip.y) < Pclip.w && 
	  0 < Pclip.z && 
	  Pclip.z < Pclip.w;
}


// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;	
}

GLuint loadCubemap(vector<const GLchar*>& faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width,height;
    unsigned char* image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

bool CheckCollision(glm::vec3 &one, glm::vec3 &two,glm::vec3 one_size, glm::vec3 two_size) // AABB - AABB collision
{
    // Collision x-axis?
   bool collisionX = (one.x + one_size.x/2.0f >= two.x-two_size.x/2.0f) && (two.x + two_size.x/2.0f>= one.x-one_size.x/2.0f);
    // Collision y-axis?
   bool collisionY = (one.y + one_size.y/2.0f >= two.y-two_size.y/2.0f)  && (two.y + two_size.y/2.0f) >= (one.y-one_size.y/2.0f);
    // Collision y-axis?
    bool collisionZ = (one.z + one_size.z/2.0f >= two.z-two_size.z/2.0f)  && (two.z + two_size.z/2.0f) >= (one.z-one_size.z/2.0f);
    // Collision only if on both axes
    return collisionX && collisionY &&collisionZ; 
}

// void mouse_callback(GLFWwindow* window, double xpos, double ypos)
// {
//     if(firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     GLfloat xoffset = xpos - lastX;
//     GLfloat yoffset = lastY - ypos; 
    
//     lastX = xpos;
//     lastY = ypos;

//     camera.ProcessMouseMovement(xoffset, yoffset);
// }


// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//     camera.ProcessMouseScroll(yoffset);
// }

#pragma endregion
