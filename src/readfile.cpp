/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix
// transformations for a stack (matransform) and to rightmultiply the
// top of a stack.  These functions are given to aid in setting up the
// transformations properly, and to use glm functions in the right way.
// Their use is optional in your program.


// The functions readvals and readfile do basic parsing.  You can of course
// rewrite the parser as you wish, but we think this basic form might be
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE.
// Read the other parts to get a context of what is going on.

/*****************************************************************************/

// Basic includes to get this file to work.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "Transform.h"

using namespace std;

#include "readfile.h"
#include "variables.h"
#include "Scene.h"

void matransform(stack<mat4> &transfstack, GLfloat* values)
{
  mat4 transform = transfstack.top();
  vec4 valvec = vec4(values[0],values[1],values[2],values[3]);
  vec4 newval = transform * valvec;
  for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
  mat4 &T = transfstack.top();
  T = T * M;
}

bool readvals(stringstream &s, const int numvals, float* values)
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i];
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n";
      return false;
    }
  }
  return true;
}

void readfile(const char* filename, Scene * scene) {
    string str, cmd;
    ifstream in;
    in.open(filename);
    if (in.is_open()) {

        stack <mat4> transfstack;
        transfstack.push(mat4(1.0));

        getline (in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines

                stringstream s(str);
                s >> cmd;

                int intvalue;
                std::string stringvalue;
                float values[10];
                bool validinput;

                //_______________________________________________________________
                // handle size command
                //_______________________________________________________________
                if (cmd == "size") {
                    validinput = readvals(s,2,values);
                    if (validinput) {
                        scene->setWidth((int) values[0]);
                        scene->setHeight((int) values[1]);
                        cout << "Scene File Size Settled. Width: " << values[0] << ", Height: " << values[1] << ".\n";
                    }
                }
                //_______________________________________________________________
                // handle animate command
                //_______________________________________________________________
                else if (cmd == "animate") {
                    animateCamera = true;
                }
                //_______________________________________________________________
                // handle maxdepth command
                //_______________________________________________________________
                else if (cmd == "maxdepth") {
                    s >> intvalue;
                    scene->setMaxDepth(intvalue);
                    cout << "Max Depth Settled, Max Depth: " << intvalue << ".\n";
                }
                //_______________________________________________________________
                // handle output command
                //_______________________________________________________________
                else if (cmd == "output") {
                    s >> stringvalue;
                    outputfile = stringvalue;
                    cout << "Output File Name Settled, Name: " << outputfile << ".\n";
                }
                //_______________________________________________________________
                // handle camera command
                //_______________________________________________________________
                else if (cmd == "camera") {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput) {
                        vec3 pos = vec3(values[0], values[1], values[2]);
                        vec3 center = vec3(values[3], values[4], values[5]);
                        vec3 up = vec3(values[6], values[7], values[8]);
                        float fovy = values[9];
                        scene->createCamera(pos, center, up, fovy);
                        cout << "Camera Settled! Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
                    }
                }
                //_______________________________________________________________
                // handle sphere command
                //_______________________________________________________________
                else if (cmd == "sphere") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {
                        scene->addSphere(values[0], values[1], values[2], values[3]);
                    }
                }
                //_______________________________________________________________
                // handle maxverts command
                //_______________________________________________________________
                else if (cmd == "maxverts") {
                    s >> intvalue;
                    maxverts = intvalue;
                }
                //_______________________________________________________________
                // handle maxvertnorms command
                //_______________________________________________________________
                else if (cmd == "maxvertnorms") {
                    s >> intvalue;
                    maxvertnorms = intvalue;
                }
                //_______________________________________________________________
                // handle vertex command
                //_______________________________________________________________
                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        scene->addVertex(values[0], values[1], values[2]);
                    }
                }
                //_______________________________________________________________
                // handle vertexnormal command
                //_______________________________________________________________
                else if (cmd == "vertexnormal") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        scene->addVertex(values[0], values[1], values[2], values[3], values[4],
                        values[5]);
                    }
                }
                //_______________________________________________________________
                // handle tri command
                //_______________________________________________________________
                else if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        scene->addTriangle((int) values[0], (int) values[1], (int) values[2]);
                    }
                }
                //_______________________________________________________________
                // handle trinormal command
                //_______________________________________________________________
                else if (cmd == "trinormal") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        scene->addTriangle((int) values[0], (int) values[1], (int) values[2]);
                    }
                }
                //_______________________________________________________________
                // handle translate
                //_______________________________________________________________
                else if (cmd == "translate") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        mat4 translateM = Transform::translate(values[0], values[1], values[2]);
                        scene->updateTransf(translateM);
                    }
                }
                //_______________________________________________________________
                // handle rotate
                //_______________________________________________________________
                else if (cmd == "rotate") {
                    validinput = readvals(s,4,values);
                    if (validinput) {
                        vec3 axis = normalize(vec3(values[0], values[1], values[2]));
                        mat4 rotateM = mat4(Transform::rotate(values[3], axis));
                        scene->updateTransf(rotateM);
                    }
                }
                //_______________________________________________________________
                // handle scale
                //_______________________________________________________________
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        mat4 scaleM = Transform::scale(values[0], values[1], values[2]);
                        scene->updateTransf(scaleM);
                    }
                }
                //_______________________________________________________________
                // handle pushTransform
                //_______________________________________________________________
                else if (cmd == "pushTransform") {
                    scene->pushTransf();
                }
                //_______________________________________________________________
                // handle popTransform
                //_______________________________________________________________
                else if (cmd == "popTransform") {
                    scene->popTransf();
                }
                //_______________________________________________________________
                // handle directional
                //_______________________________________________________________
                else if (cmd == "directional") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        scene->addDirectionalLight(values[0], values[1], values[2],
                                                   values[3], values[4], values[5]);
                    }
                }
                //_______________________________________________________________
                // handle point command
                //_______________________________________________________________
                else if (cmd == "point") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        scene->addPointLight(values[0], values[1], values[2],
                                             values[3], values[4], values[5]);
                    }
                }
                //_______________________________________________________________
                // handle attenuation
                // TODO: how to set the default attenuation?
                //_______________________________________________________________
                else if (cmd == "attenuation") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        scene->setAttenuation(values[0], values[1], values[2]);
                    }
                }
                //_______________________________________________________________
                // handle ambient command
                //_______________________________________________________________
                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput) {
                        scene->setAmbient(vec3(values[0], values[1], values[2]));
                    }
                }
                //_______________________________________________________________
                // handle diffuse
                //_______________________________________________________________
                else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput) {
                        scene->setDiffuse(vec3(values[0], values[1], values[2]));
                    }
                }
                //_______________________________________________________________
                // handle specular
                //_______________________________________________________________
                else if (cmd == "specular") {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput) {
                        scene->setSpecular(vec3(values[0], values[1], values[2]));
                    }
                }
                //_______________________________________________________________
                // handle emission
                //_______________________________________________________________
                else if (cmd == "emission") {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput) {
                        scene->setEmission(vec3(values[0], values[1], values[2]));
                    }
                }
                //_______________________________________________________________
                // handle shininess
                //_______________________________________________________________
                else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values); // colors
                    if (validinput) {
                        scene->setShininess(values[0]);
                    }
                }
                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline (in, str);
        }
    }
    else {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}
