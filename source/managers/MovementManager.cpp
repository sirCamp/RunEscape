//
// Created by stefano on 02/09/16.
//
#include <GL/gl.h>

class MovementManager{

    private:
        GLfloat X;
        GLfloat Y;
        GLfloat Z;
        GLfloat A;

    public:

        /**
         * Movement Manager Constructor
         * @param X
         * @param Y
         * @param Z
         * @param A
         * @return
         */
        MovementManager(GLfloat X, GLfloat Y, GLfloat Z, GLfloat A=-90){

            this->X = X;
            this->Y = Y;
            this->Z = Z;
            this->A = A;
        }

        /**
         * This method calculates che movement on the three axeses
         * @param maze
         * @param incr
         */
        void move(Maze* maze, float incr){


            //traslo movimento
            float to_z = (Z + incr*(cos(this->A * Constants::PI / 180.0 )));
            float to_x = (X + incr*(sin(this->A * Constants::PI / 180.0 )));


            Logger::info(string("Move in x:")+maze::to_string(to_x)+string(" and z:")+maze::to_string(to_z));

            if(!Utils::isGoingThroughtWall(maze, to_z,  to_x) && ! Utils::isGoingThroughtAlarm(maze,to_z, to_x)){
                this->X = to_x;
                this->Z = to_z;
            }



        }

        /**
         * This method make the right action for the typed command
         * @param button
         * @param maze
         * @param audioManager
         */
        void action(unsigned char button, Maze * maze, AudioManager *audioManager){



            vector<Alarm*> alarms = maze->getAlarm();
            vector<Alarm*>::const_iterator ite;
            int index = 0;



            if(!maze->isLose() && !maze->isWin()) {


                switch (button) {

                    case Constants::UP_KEY:
                        move(maze, -1);
                        Logger::info("UP_KEY pressed");

                        break;

                    case Constants::DOWN_KEY:
                        move(maze, 1);
                        Logger::info("DOWN_KEY pressed");

                        break;

                    case Constants::LEFT_KEY:

                        this->A += 90;//degrees
                        Logger::info("LEFT_KEY pressed");
                        break;

                    case Constants::RIGHT_KEY:
                        this->A -= 90; //degrees
                        Logger::info("RIGHT_KEY pressed");
                        break;

                    case Constants::SPACEBAR:
                        Logger::info(
                                string("Trying to disactivate an alarm, fom x:") + maze::to_string(X) + string(" to z: ") +
                                maze::to_string(Z));

                        index = -1;
                        for (ite = alarms.begin(); ite != alarms.end(); ite++) {


                            float x = (*ite)->getX();
                            float z = (*ite)->getZ();

                            index++;
                            if (!(*ite)->isActive()) {

                                continue;
                            }


                            bool active = true;


                            if (x - 1 == X && z == Z) {
                                Logger::info(string("ALLARME TROVATO DIFRONTE in: ") + maze::to_string(x) + string(" ") +
                                             maze::to_string(z));
                                active = false;

                            }

                            if (x == X && z - 1 == Z) {
                                Logger::info(string("ALLARME TROVATO DESTRA in: ") + maze::to_string(x) + string(" ") +
                                             maze::to_string(z));
                                active = false;
                            }

                            if (x + 1 == X && z == Z) {
                                Logger::info(string("ALLARME TROVATO DIETRO in: ") + maze::to_string(x) + string(" ") +
                                             maze::to_string(z));
                                active = false;
                            }


                            if (x == X && z + 1 == Z) {
                                Logger::info(string("ALLARME TROVATO SINISTRA in: ") + maze::to_string(x) + string(" ") +
                                             maze::to_string(z));
                                active = false;
                            }


                            if (active == false) {

                                (*ite)->setActive(active);
                                maze->decreaseActiveAlarms();
                                Logger::info(string("disabilito index: ")+maze::to_string(index));
                                audioManager->stopAudioSource(index);

                            }



                        }

                        break;

                    case Constants::ESC_KEY:
                        delete audioManager;
                        Logger::info("Exiting from MazeGame\nbye!!");
                        exit(0);
                        break;
                    }

                    glutPostRedisplay();

                }
                else{

                    if(button == Constants::ESC_KEY) {
                        delete audioManager;
                        Logger::info("Exiting from MazeGame\nbye!!");
                        exit(0);
                    }
                }



        }

        /**
         * Getter for X coordinate
         * @return
         */
        GLfloat getX() const {
            return X;
        }

        /**
         * Setter for X coordinate
         * @param X
         */
        void setX(GLfloat X) {
           this->X = X;
        }

        /**
         * Getter for Y coordinate
         * @return
         */
        GLfloat getY() const {
            return Y;
        }

        /**
         * Setter for Y coordinate
         * @param Y
         */
        void setY(GLfloat Y) {
            this->Y = Y;
        }

        /**
         * Getter for Z coordinate
         * @return
         */
        GLfloat getZ() const {
            return Z;
        }

        /**
         * Setter for Z coordinate
         * @param Z
         */
        void setZ(GLfloat Z) {
            this->Z = Z;
        }

        /**
         * Getter for A angule
         * @return
         */
        GLfloat getA() const {
            return A;
        }

        /**
         * Setter for the A angule
         * @param A
         */
        void setA(GLfloat A) {
            this->A = A;
        }
};