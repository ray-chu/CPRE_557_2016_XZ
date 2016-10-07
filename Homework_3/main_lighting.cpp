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
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "GLSphere.h"
#include "GLAppearance.h"

using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;



int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();

    
    // Init the glew api
    initGlew();
    
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);
    
    
    GLSphere* sphere1 = new Sphere1(0.0, 0.0, 0.0, 5.0, 40, 20);
    GLSphere* sphere2 = new Sphere2(16.0, 0.0, 0.0, 5.0, 40, 20);
    GLSphere* sphere3 = new Sphere3(32.0, 0.0, 0.0, 5.0, 200, 100);
    // create an apperance object.
    GLAppearance* apperance = new GLAppearance("./multi_vertex_lights.vs", "./multi_vertex_lights.fs");

        // The spotlight object
    GLSpotLightSource  light_source1;
    light_source1._lightPos = glm::vec4(48.0,20.0,0.0,1.0);
    light_source1._ambient_intensity = 0.3;
    light_source1._specular_intensity = 4.0;
    light_source1._diffuse_intensity = 3.0;
    light_source1._attenuation_coeff = 0.02;
    light_source1._inner_cone_angle = 10.0; // in degree
    light_source1._outer_cone_angle = 15.0; // in degree
    light_source1._cone_direction = glm::vec3(-0.03, -1.0, -0.05); // this must be aligned with the object and light position.
    
    
    GLDirectLightSource  light_source2;
    light_source2._lightPos = glm::vec4(-10.0,10.0,20.0, 0.0);
    light_source2._ambient_intensity = 0.1;
    light_source2._specular_intensity = 0.2;
    light_source2._diffuse_intensity = 0.0;
    light_source2._attenuation_coeff = 0.0;
   // light_source2._cone_angle = 12.0; // in degree
   // light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.
    
    
    // add the spot light to this apperance object
    apperance->addLightSource(light_source1);
    apperance->addLightSource(light_source2);

    GLMaterial material;
    material._diffuse_material = glm::vec3(0.85, 0.85, 0.10);
    material._ambient_material = glm::vec3(0.85, 0.85, 0.10);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 36.0;
    
    // Add the material to the apperance object
    apperance->setMaterial(material);
    apperance->finalize();
    
    GLSphere3D* sphere4 = new GLSphere3D(48.0, 0.0, 0.0, 5.0, 200, 100);
    
    sphere4->setApperance(*apperance);
    sphere4->init();

    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(20.0f,50.0f,20.0f/*12.0f, 12.0f, 15.5f*/), glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    //sphere->enableNormalVectorRenderer();
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
    
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());
        
        // draw the objects
        cs->draw();
        
        sphere1->draw();
	sphere2->draw();
	sphere3->draw();
	sphere4->draw();
        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}
