
#include <iostream>
#include <iomanip>
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

#include <FreeImage.h>

#define MAINPROGRAM

#include "variables.h"
#include "readfile.h"
#include "Scene.h"

using namespace std;

typedef uint8_t BYTE;

int black = 0;

/**
 * [saveScreenshot description]
 * @param fname  [description]
 * @param width  [description]
 * @param height [description]
 * @param pixels [description]
 */
void saveScreenshot(string fname, int width, int height, BYTE * pixels) {
    FIBITMAP * img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
    FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
    std::cout << endl << "Saved screenshot: " << fname << endl;
    delete[] pixels;
}

/**
 * Pad the number to two digits
 * @param  number [description]
 * @return        [description]
 */
string padZero(int number) {
    return (number < 10 ? "0" : "") + to_string(number);
}

/**
 *
 * @param curr  [description]
 * @param total [description]
 * @param color [description]
 */
void printProgress(int curr, int total, vec3 color) {
    const int PROGRESS_LENGTH = 75;
    if (curr == 0) {
        for (int i = 0; i < PROGRESS_LENGTH; i++) {
            cout << '-';
        }
    }
    else {
        for (int i = 0; i < PROGRESS_LENGTH + 5; i++) {
            cout << '\b';
        }
        
        int currLength = (float) curr / (float) total * (float) PROGRESS_LENGTH;
        cout << '[';
        for (int i = 0; i < PROGRESS_LENGTH; i++) {
            if (i < currLength) {
                cout << '=';
            }
            else if (i == currLength) {
                cout << '>';
            }
            else {
                cout << ' ';
            }
        }
        cout << ']';
        
        int percentage = (float) curr / (float) total * 100;
        cout << padZero(percentage) << '%';
    }
}

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char* argv[]) {
    
    // Check the command line argument
    if (argc != 2) {
        std::cerr << "Usage: render [scenefile]\n" << std::endl;
        exit(-1);
    }
    
    // Initialize the freeimage module
    FreeImage_Initialise();
    
    // Create and Construct the Scene
    Scene scene;
    readfile(argv[1], &scene);
    scene.onRenderProgress(&printProgress);
    
    if (animateCamera) {
        int stepAmount = 72;
        int step = 360 / stepAmount;
        for (int i = 0; i <= stepAmount; i++) {
            saveScreenshot(outputfile + padZero(i) + ".png", scene.getWidth(), scene.getHeight(), scene.render());
            scene.rotateCamera(step, vec3(0, 1, 0));
        }
    }
    else {
        saveScreenshot(outputfile, scene.getWidth(), scene.getHeight(), scene.render());
    }
    
    // DeInitialize the freeimage module
    FreeImage_DeInitialise();
    
    // Exit the program
    return 0;
}
