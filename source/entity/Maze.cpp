//
// Created by stefano on 31/08/16.
//

#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Maze{

    private:

    int rows;
    int cols;
    bool ** mazeMatrix;
    vector<Alarm*> alarms;
    int active_alarms;
    int timeOfPlay;

    bool lose;
    bool win;


    public:

        Maze(){

            Logger::info("Start to parse the matrix");

            ifstream file;
            file.open(Constants::WORLD_CONFIGURATION);
            string value;
            file >> timeOfPlay;
            file >> rows;
            file >> cols;
            rows = rows+2; // borders
            cols = cols+2; // borders

            win = false;
            lose = false;

            mazeMatrix = new bool*[rows];

            for(int i = 0; i < rows; ++i) {
                mazeMatrix[i] = new bool[cols];
            }

            /* Default values inizialization: the maze is always closed: border = 2 */
            int i=0;
            int j=0;
            for(i=0; i<rows; i++){
                for(j=0; j<cols; j++){
                    if(i==0 || i==rows-1 || j==0 || j==cols-1){
                        mazeMatrix[i][j] = 1;
                    }else{
                        mazeMatrix[i][j] = 0;
                    }
                }
            }
            string line;

            for(i=1; i<rows-1; i++){
                for(j=1; j<cols-1; j++){
                    file >> mazeMatrix[i][j];
                }
            }


            Logger::info("Finish to parse the matrix");
            file.close();

            this->alarms = Alarm::loadAlarms();
            this->active_alarms = this->alarms.size();
        }


        int getRows(){
            return rows;
        }

        int getCols(){
            return cols;
        }


        bool** getMazeMatrix(){
            return mazeMatrix;
        }


        int getActiveAlarms(){

            return this->active_alarms;
        }

        void decreaseActiveAlarms(){

           if(this->active_alarms > 0){

                this->active_alarms -=1;

           }

        }

        vector<Alarm*> getAlarm(){

            return this->alarms;
        }

        bool isWall(int z, int x){
            return mazeMatrix[z][x];
        }


        int getTimeOfPlay(){

            return this->timeOfPlay;
        }

        void decreaseTimeOfPlay(){

            if(this->timeOfPlay > 0){
                this->timeOfPlay -=1;
            }

        }

        char * generateTitleBar(){

            string * title = new string;
            *title = string("Run Escape   Active Alarms: ")+maze::to_string(this->active_alarms)+string("/")+maze::to_string(alarms.size());
            *title += string("   Time to go: ")+maze::to_string(timeOfPlay)+string("s");
            return (char*)title->c_str();

        }


        bool isWin(){
            return this->win;
        }

        bool isLose(){
            return this->lose;
        }


        void setLose(bool lose){
            this->lose = lose;
        }

        void setWin(bool win){

            this->win = win;
        }


    };