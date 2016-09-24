#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

/* graphics libraries */
#include "GL/glut.h"

/* audio libraries */
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
/********************/
#include "source/utils/Custom.cpp"
#include "source/utils/Logger.cpp"
#include "source/utils/Constants.cpp"
#include "source/entity/Alarm.cpp"
#include "source/entity/Maze.cpp"
#include "source/utils/Utils.cpp"
#include "source/managers/AudioManager.cpp"
#include "source/Drawer.cpp"
#include "source/managers/TextureManager.cpp"
#include "source/managers/MovementManager.cpp"


Drawer* drawer;
Maze* mazeScheme;
MovementManager* movementManager;
AudioManager* audioManager;
TextureManager* textureManager;


void actionPressed(unsigned char button, int, int){


    movementManager->action(button, mazeScheme, audioManager);

}

void reshapeWindow(int w, int h){
        glViewport(0, 0, w, h); // it changes the window size

        // the projection matrix is modified when the window is resized
        glMatrixMode(GL_PROJECTION); // next matrix operations will be applied to the projection one
        glLoadIdentity(); // it substitutes the matrix with the identity matrix
        glFrustum(-0.5, 0.5, -0.5,0.5, 0.3, 1000);

}

void draw()
{


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // presets the buffer to enable it for color writing and to operate to the depth buffer

        GLfloat X = movementManager->getX();
        GLfloat Y = movementManager->getY();
        GLfloat Z = movementManager->getZ();
        GLfloat A = movementManager->getA();

        // Spotlight properties including position.
        audioManager->updateListenerPosition(X, Z, A);

        glMatrixMode(GL_MODELVIEW); // following operations will be applied to the modelview matrix. Operations of translation, scale and other transformations
        glLoadIdentity(); // identity matrix

        glRotatef(-A, 0, 1, 0); // identity -> rotation matrix
        glTranslatef(Utils::centerCamera(-X), -Y, Utils::centerCamera(-Z)); // rotation m. -> translation + rotation matrix

        //useful parameters for ceiling and floor drawing
        int x = mazeScheme->getCols();
        int z = mazeScheme->getRows();

        // material effects and texture enabling
        glMateriali(GL_FRONT, GL_SHININESS, 32);

        glEnable(GL_TEXTURE_2D);

        //floor
        glBindTexture(GL_TEXTURE_2D, 1);
        drawer->drawFloor(x, z);

        //sky
        glBindTexture(GL_TEXTURE_2D, 2);
        drawer->drawSky(x, z);

        //maze
        glBindTexture(GL_TEXTURE_2D, 3);
        drawer->drawMaze(mazeScheme);

        glDisable(GL_TEXTURE_2D);

        glMateriali(GL_FRONT, GL_SHININESS, 128);
        drawer->drawAlarm(mazeScheme, audioManager);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glFrustum(-0.5, 0.5, -0.5,0.5, 0.3, 1000);


        glutSwapBuffers(); // applied to swap the buffer

        drawer->setFirstTime(false);

}



void statusUpdater(int v){

    if(mazeScheme->getActiveAlarms() > 0){

        mazeScheme->decreaseTimeOfPlay();

        if(mazeScheme->getTimeOfPlay() == 0){

            Logger::info("YOU LOSE");
            mazeScheme->setLose(true);
            drawer->drawWinOrLoseView(mazeScheme);
        }
        else{

            char *title = mazeScheme->generateTitleBar();
            Logger::info(title);
            glutSetWindowTitle(title);
            glutTimerFunc(1000, statusUpdater, v);
        }

    }
    else{
        if(mazeScheme->getTimeOfPlay() >= 0){

            Logger::info("YOU WIN");
            mazeScheme->setWin(true);
            drawer->drawWinOrLoseView(mazeScheme);

        }
        else{

            char *title = mazeScheme->generateTitleBar();
            Logger::info(title);
            glutSetWindowTitle(title);
            glutTimerFunc(1000, statusUpdater, v);
        }
    }


}

int main(int argc, char **argv)
{




    if (argc > 1 && string(argv[1]) == "debug") {

       Logger::DEBUG = true;
    }

    float X = 1.0;
    float Y = 0.5;
    float Z = 1.0;
    float A = -90;


    mazeScheme = new Maze();
    drawer = new Drawer();
    movementManager = new MovementManager(X, Y, Z, A);
    audioManager = new AudioManager();
    textureManager = new TextureManager();


    glutInit(&argc, argv); // initialize glut
    alutInit(&argc, argv); // initialize alut
    alGetError();

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); // display mode (ex: with single or double buffer)
    glutInitWindowPosition(200, 200); // window position
    glutInitWindowSize(800, 600); // window size
    char *title = mazeScheme->generateTitleBar();
    glutCreateWindow(title); // it creates a window with the specified name

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //to set the color buffer

    glEnable(GL_DEPTH_TEST); // to allow depth updates
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    textureManager->loadTexture(Constants::TEXTURE_FLOOR_CONFIGURATION,512,512,GL_BGR);
    textureManager->loadTexture(Constants::TEXTURE_SKY_CONFIGURATION,600,600);
    textureManager->loadTexture(Constants::TEXTURE_WALL_CONFIGURATION,3000,2000, GL_BGR);

    audioManager->loadWorldSource(X,Z,Y);

    glutReshapeFunc(reshapeWindow);
    glutDisplayFunc(draw);
    glutKeyboardFunc(actionPressed);
    glutTimerFunc(1000,statusUpdater,100);
    glutMainLoop();

    return 0;
}
