//
// Created by stefano on 03/09/16.
//
class Utils{

public:


    /**
     * This method needs to normalize the Camera
     * @param position
     * @return
     */
    static GLfloat centerCamera(GLfloat position){

        return position -=0.5;
    }


    /**
     * This method check if you're going over an alarm
     * @param maze
     * @param to_z
     * @param to_x
     * @return
     */
    static bool isGoingThroughtAlarm(Maze* maze, float to_z, float to_x){


        vector<Alarm*> alarms = maze->getAlarm();

        vector<Alarm*>::const_iterator ite;

        bool collision = false;

        for(ite=alarms.begin(); ite!=alarms.end() && !collision; ite++){


            float x = (*ite)->getX();
            float z = (*ite)->getZ();

            if((to_x == x )  && (to_z == z ) ){
                Logger::info(string("CRASH ALARM x: ")+maze::to_string(x)+string( " and z: ")+maze::to_string(z));
                collision = true;
            }


        }
        return collision;
    }

    /**
     * This method check if you're going over the wall.
     *
     * @param maze
     * @param to_z
     * @param to_x
     * @return
     */
    static bool isGoingThroughtWall(Maze* maze, float to_z, float to_x){


        bool collision = maze->isWall(to_z,to_x);

        if(collision){
            Logger::info("CRASH");
            Logger::info(string("Axes: z:")+maze::to_string(to_z)+string(" x: ")+maze::to_string(to_x));

        }

        return collision;


    }



};