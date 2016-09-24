//
// Created by stefano on 05/09/16.
//
#include <fstream>
class Alarm{

private:

    int X;
    int Z;
    bool active;

public:

    Alarm(int X = 0, int Z = 0): active(true){

        this->X = X;
        this->Z = Z;
    }

    static vector<Alarm*> loadAlarms(){

        Logger::info("Start to parse the alarms");
        long unsigned int alarms = 0;

        ifstream file;
        file.open(Constants::ALARM_CONFIGURATION);
        string value;
        file >> alarms;

        /**
         * Create and istantiate the alarms vector
         */
        vector<Alarm*> allAlarms (alarms);
        allAlarms.clear();



        Logger::info(string("Ci sono ")+maze::to_string(alarms)+string(" allarmi da inserire, vettore istanziato con dimensione ")+maze::to_string(allAlarms.size()));

        for(int i=0; i<alarms; i++){

            int x, z;
            file >> x;
            file >> z;


            allAlarms.push_back(new Alarm(x+1, z+1));

        }

        file.close();

        Logger::info("Finish to parse the alarms");
        return allAlarms;

    }


    int getX(){
        return this->X;
    }

    int getZ(){
        return this->Z;
    }

    int isActive(){
        return (int) this->active;
    }

    void setActive( bool active){
        this->active = active;
    }






};