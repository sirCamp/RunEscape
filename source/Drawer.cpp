//
// Created by stefano on 02/09/16.
//

class Drawer{
private:
    bool firstTime;
public:

    Drawer(): firstTime(true){}

    /**
     * This method draw the Floor of maze
     * @param x
     * @param z
     */
    void drawFloor(int x, int z){
        glBegin(GL_QUADS);

        glNormal3f(0, -1, 0);
        glTexCoord2f(z, z);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, z);
        glVertex3f(0, 0, z);
        glTexCoord2f(0, 0);
        glVertex3f(x, 0, z);
        glTexCoord2f(z, 0);
        glVertex3f(x, 0, 0);
        glEnd();
    }

    /**
     * This method draw the Sky of maze
     * @param x
     * @param z
     */
    void drawSky(int x, int z){
        glBegin(GL_QUADS);

        glNormal3f(0, -1, 0);
        glTexCoord2f(z, 0);
        glVertex3f(x, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(x, 1, z);
        glTexCoord2f(0, z);
        glVertex3f(0, 1, z);
        glTexCoord2f(z, z);
        glVertex3f(0, 1, 0);
        glEnd();
    }

    /**
     * This method draw the Walls of maze
     * @param x
     * @param y
     * @param z
     * @param R
     */
    void drawCube(int x, int y, int z, GLfloat R = 1)
    {


        glBegin(GL_QUADS);

        glNormal3f(0, 0, 1);
        glTexCoord2f(1, 1);
        glVertex3f(x + R, y + R, z + R);
        glTexCoord2f(0, 1);
        glVertex3f(x, y + R, z + R);
        glTexCoord2f(0, 0);
        glVertex3f(x, y, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y, z + R);

        glNormal3f(0, 0, -1);
        glTexCoord2f(1, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y, z);
        glTexCoord2f(1, 0);
        glVertex3f(x, y, z);

        glNormal3f(1, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z + R);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y, z);

        glNormal3f(-1, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x, y + R, z + R);
        glTexCoord2f(0, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x, y, z);
        glTexCoord2f(1, 0);
        glVertex3f(x, y, z + R);

        //faccia sopra
        glNormal3f(0, 1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x, y + R, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y + R, z + R);

        //faccia sotto
        glNormal3f(0, -1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y + R, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x, y + R, z + R);




        glEnd();
    }

    void drawMaze(Maze* mazeScheme){
        float coordX = 0;
        float coordZ = 0;
        bool** matrix = mazeScheme->getMazeMatrix();
        for(int i=0; i<mazeScheme->getRows(); i++){
            for(int j=0; j<mazeScheme->getCols() ; j++){
                bool cubeToBeDrawn = matrix[i][j];
                if(cubeToBeDrawn ){

                    drawCube((coordX+j), 0, (coordZ+i),1);
                }

            }

        }
    }

    /**
     * This method draw the alarms and set the sound
     * @param mazeScheme
     * @param audioManager
     */
    void drawAlarm(Maze* mazeScheme, AudioManager* audioManager){

        vector<Alarm*>::const_iterator ite;
        vector<Alarm*> alarms  = mazeScheme->getAlarm();


        for(ite=alarms.begin(); ite!=alarms.end(); ite++){

            float x = (*ite)->getX();
            float z = (*ite)->getZ() + Constants::ALARM_Z_FACTOR;
            float R = Constants::ALARM_R_FACTOR;
            float y = 0;

           if(this->isFirstTime()) {
                audioManager->loadAlarmSource(x, z, y+R);
            }

            glPushAttrib(GL_CURRENT_BIT);

            glBegin(GL_QUADS);

            glColor3f((*ite)->isActive(),!(*ite)->isActive(),0);

            glNormal3f(0, 0, 1);
            glTexCoord2f(1, 1);
            glVertex3f(x + R, y + R, z + R);
            glTexCoord2f(0, 1);
            glVertex3f(x, y + R, z + R);
            glTexCoord2f(0, 0);
            glVertex3f(x, y, z + R);
            glTexCoord2f(1, 0);
            glVertex3f(x + R, y, z + R);

            glNormal3f(0, 0, -1);
            glTexCoord2f(1, 1);
            glVertex3f(x, y + R, z);
            glTexCoord2f(0, 1);
            glVertex3f(x + R, y + R, z);
            glTexCoord2f(0, 0);
            glVertex3f(x + R, y, z);
            glTexCoord2f(1, 0);
            glVertex3f(x, y, z);

            glNormal3f(1, 0, 0);
            glTexCoord2f(1, 1);
            glVertex3f(x + R, y + R, z);
            glTexCoord2f(0, 1);
            glVertex3f(x + R, y + R, z + R);
            glTexCoord2f(0, 0);
            glVertex3f(x + R, y, z + R);
            glTexCoord2f(1, 0);
            glVertex3f(x + R, y, z);

            glNormal3f(-1, 0, 0);
            glTexCoord2f(1, 1);
            glVertex3f(x, y + R, z + R);
            glTexCoord2f(0, 1);
            glVertex3f(x, y + R, z);
            glTexCoord2f(0, 0);
            glVertex3f(x, y, z);
            glTexCoord2f(1, 0);
            glVertex3f(x, y, z + R);

            //faccia sopra
            glNormal3f(0, 1, 0);
            glTexCoord2f(1, 1);
            glVertex3f(x + R, y + R, z);
            glTexCoord2f(0, 1);
            glVertex3f(x, y + R, z);
            glTexCoord2f(0, 0);
            glVertex3f(x, y + R, z + R);
            glTexCoord2f(1, 0);
            glVertex3f(x + R, y + R, z + R);

            //faccia sotto
            glNormal3f(0, -1, 0);
            glTexCoord2f(1, 1);
            glVertex3f(x, y + R, z);
            glTexCoord2f(0, 1);
            glVertex3f(x + R, y + R, z);
            glTexCoord2f(0, 0);
            glVertex3f(x + R, y + R, z + R);
            glTexCoord2f(1, 0);
            glVertex3f(x, y + R, z + R);

            glEnd();
            glPopAttrib();

            //Logger::info(string("disegno allarme in :")+maze::to_string(x)+string(" ")+maze::to_string(z));

        }

    }

    /**
     * This Method draw the Biutmap of Win or Lose
     * @param maze
     */
    void drawWinOrLoseView(Maze* maze){



        glDisable(GL_LIGHTING);
        glClearColor(0, 0, 0, 0);

        glColor3d(1, 1, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 1.0, 0.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(0, 0, 1, 0);
        glTranslatef(0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        string text = Constants::EXIT_TEXT;
        glRasterPos2d(0.05, 0.95);
        for (string::const_iterator ii = text.begin(); ii != text.end(); ++ii){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
        }

        string text_message = "";
        string text_title = "";
        float x,y;

        if(maze->isWin()){

            text_message  = Constants::WIN_TEXT;
            text_title = Constants::WIN_TITLE;
            x = 0.4;
            y = 0.5;

        }
        else if(maze->isLose()){

            text_message  = Constants::LOSE_TEXT;
            text_message = text_message.replace(text_message.find("#"), 1,maze::to_string(maze->getActiveAlarms()));
            text_title = Constants::LOSE_TITLE;
            x = 0.2;
            y = 0.5;
        }


        glRasterPos2d(x, y);
        for (string::const_iterator ii = text_message.begin(); ii != text_message.end(); ++ii)
        {
              glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
        }

        glutSetWindowTitle(text_title.c_str());

        glutSwapBuffers();

    }


    /**
     * Setter for firstTime
     * @param firstTime
     */
    void setFirstTime(bool firstTime){

        this->firstTime = firstTime;
    }

    /**
     * Getter for firstTime
     * @return bool
     */
    bool isFirstTime(){

        return this->firstTime;
    }


}; 