//
// Created by stefano on 31/08/16.
//

#include <iostream>
#include <string>
using namespace std;

class Logger{

    public:

        /**
         * @var bool
         */
        static bool DEBUG;

        /**
         * This method print an INFO message
         * @param text
         */
        static void info(const char* text){

            if(Logger::DEBUG) {
                std::cout << "[INFO]: " << text << endl;
            }
        }

        /**
         * This method print an INFO message
         * @param text
         */
        static void info(std::string text){
            if(Logger::DEBUG) {
                std::cout << "[INFO]: " << text << endl;
            }
        }

        /**
         * This method print an ERROR message
         * @param text
         */
        static void error(const char* text){

            if(Logger::DEBUG) {
                std::cout << "[ERROR]: " << text << endl;
            }
        }

        /**
        * This method print an ERROR message
        * @param text
        */
        static void error(std::string text){
            if(Logger::DEBUG) {
                std::cout << "[ERROR]: " << text << endl;
            }
        }

        /**
        * This method print an DEBUG message
        * @param text
        */
        static void debug(const char* text){

            if(Logger::DEBUG) {
                std::cout << "[DEBUG]: " << text << endl;
            }
        }

        /**
        * This method print an DEBUG message
        * @param text
        */
        static void debug(bool text){
            if(Logger::DEBUG) {
                std::cout << "[DEBUG]: " << text << endl;
            }
        }
};

bool Logger::DEBUG = false;