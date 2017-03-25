/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.
// Since all files need access to it, we define EXTERN as either blank or
// extern, depending on if included in the main program or not.

#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif

#include <string>

using namespace std;

//EXTERN int amount; // The amount of rotation for each arrow press
//EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye
//EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up

EXTERN bool animateCamera;

//General
//EXTERN float width;
//EXTERN float height;
EXTERN int depth;
EXTERN std::string outputfile;

//Camera
//EXTERN vec3 pos;
//EXTERN vec3 center;
//EXTERN vec3 up;
//EXTERN float fov;

//Geometry
EXTERN int maxverts;
EXTERN int maxvertnorms;

// Lighting parameter array, similar to that in the fragment shader
//EXTERN vector<float> dirlightpos;
//EXTERN vector<float> dirlightcolor;
//EXTERN vector<float> pointlightpos;
//EXTERN vector<float> pointlightcolor;
EXTERN float attenuation[3];

// Materials (read from file)
// With multiple objects, these are colors for each.
//EXTERN float ambient[4] ;
//EXTERN float diffuse[4] ;
//EXTERN float specular[4] ;
//EXTERN float emission[4] ;
//EXTERN float shininess ;

// For multiple objects, read from a file.
//const int maxobjects = 10 ;
//EXTERN int numobjects ;
//EXTERN struct object {
//  shape type ;
//  GLfloat size ;
//  GLfloat ambient[4] ;
//  GLfloat diffuse[4] ;
//  GLfloat specular[4] ;
//  GLfloat emission[4] ;
//  GLfloat shininess ;
//  mat4 transform ;
//} objects[maxobjects] ;

// Variables to set uniform params for lighting fragment shader
//EXTERN GLuint lightcol ;
//EXTERN GLuint lightpos ;
//EXTERN GLuint numusedcol ;
//EXTERN GLuint enablelighting ;
//EXTERN GLuint ambientcol ;
//EXTERN GLuint diffusecol ;
//EXTERN GLuint specularcol ;
//EXTERN GLuint emissioncol ;
//EXTERN GLuint shininesscol ;
