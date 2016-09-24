//
// Created by stefano on 02/09/16.
//

class Constants{

public:

    static const int LOAD_RAW_TEXTURE = 1;
    static const int LOAD_BMP_TEXTURE = 2;
    static const int LOAD_JGP_TEXTURE = 3;

    static const int ESC_KEY = 27;
    static const int SPACEBAR = 32;

    static const char UP_KEY = 'w';
    static const char DOWN_KEY = 's';
    static const char RIGHT_KEY = 'd';
    static const char LEFT_KEY = 'a';

    static const double PI;

    static const char *TEXTURE_FLOOR_CONFIGURATION;
    static const char *TEXTURE_SKY_CONFIGURATION;
    static const char *TEXTURE_WALL_CONFIGURATION;

    static const float ALARM_R_FACTOR;
    static const float ALARM_Z_FACTOR;

    static const string EXIT_TEXT;
    static const string LOSE_TEXT ;
    static const string WIN_TEXT ;
    static const string LOSE_TITLE;
    static const string WIN_TITLE;

    static const char *AUDIO_ALARM;
    static const char *AUDIO_WORLD;

    static const char *WORLD_CONFIGURATION;
    static const char *ALARM_CONFIGURATION;
};


const float Constants::ALARM_R_FACTOR = 0.5;
const float Constants::ALARM_Z_FACTOR = 0.25;

const string Constants::EXIT_TEXT = "Type \"Esc\" to quit";
const string Constants::LOSE_TEXT = "You Lose! There are # alarms that are not disabled yet";
const string Constants::WIN_TEXT = "You Win!";

const string Constants::LOSE_TITLE = "You Lose!";
const string Constants::WIN_TITLE = "You Win!";

const double Constants::PI = 3.14159265358979323846;

const char *Constants::AUDIO_ALARM = "assets/audio/336899__lalks__siren-02-feeling_2.wav";
const char *Constants::AUDIO_WORLD = "assets/audio/121980__stk13__jungle-ninja.wav";

const char *Constants::WORLD_CONFIGURATION = "configuration.txt";
const char *Constants::ALARM_CONFIGURATION = "alarms.txt";

const char *Constants::TEXTURE_FLOOR_CONFIGURATION = "assets/texture/floor.bmp";
const char *Constants::TEXTURE_SKY_CONFIGURATION = "assets/texture/sky.bmp";
const char *Constants::TEXTURE_WALL_CONFIGURATION = "assets/texture/wall.bmp";