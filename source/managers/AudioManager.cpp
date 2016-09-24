//
// Created by stefano on 07/09/16.
//

class AudioManager{

private:
        vector<ALuint*>* buffers;
        vector<ALuint*>* sources;
        ALCdevice* device;
        ALCcontext* context;
        ALuint worldSource;
        ALuint wordlBuffer;
public:

    /**
     * Construcor of Audio Manager
     * @return
     */
    AudioManager(){

        buffers = new vector<ALuint*>;
        sources = new vector<ALuint*>;
        device = alcOpenDevice(NULL);
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
        alListener3f(AL_POSITION, 1, 1,1);
        alListener3f(AL_VELOCITY, 0, 0, 0);
        ALfloat aVector[6] = { 0, 0, -1, 0, 1, 0};
        alListenerfv(AL_ORIENTATION, aVector);

    }


    /**
     * Distructor of AudioManager
     */
    ~AudioManager(){

        for(int i =0; i<buffers->size(); i++){
            alDeleteSources(1, sources->at(i));
            alDeleteBuffers(1, buffers->at(i));
        }
        alDeleteSources(1, &worldSource);
        alDeleteBuffers(1, &wordlBuffer);
        alcDestroyContext(context);
        alcCloseDevice(device);
        alutExit();
    }

    /**
     * This method sto the audio source
     * @param i
     */
    void stopAudioSource(int i){

        alSourceStop(*sources->at(i));
    }

    /**
     * This method load a source in the Alarm position
     * The method also apply the Exponential audio decrease so to far you are, from the alarm to less will be the sound
     * @param x
     * @param z
     * @param y
     */
    void loadAlarmSource(ALfloat x, ALfloat z, ALfloat y){



        Logger::info(string("Audio in")+maze::to_string(x)+string(" ")+maze::to_string(z)+string(" ")+maze::to_string(y));
        ALuint* auxBuffer = new ALuint(alutCreateBufferFromFile(Constants::AUDIO_ALARM));
        buffers->push_back(auxBuffer);
        int i = sources->size();
        ALuint *auxSource = new ALuint();
        alGenSources (1, auxSource);
        alSourcei (*auxSource, AL_BUFFER, *auxBuffer);
        alSourcei(*auxSource, AL_LOOPING, AL_TRUE);

        alDistanceModel(AL_EXPONENT_DISTANCE); // exponential curve of sound attenuation
        alSource3f(*auxSource, AL_POSITION, x, y, z);
        alSource3f(*auxSource, AL_DIRECTION, 0, 1, 0);
        alSourcei(*auxSource, AL_LOOPING, AL_TRUE);
        alSourcef(*auxSource, AL_REFERENCE_DISTANCE, 3);
        alSourcef(*auxSource, AL_ROLLOFF_FACTOR, 3);
        alSourcef(*auxSource, AL_MIN_GAIN, 0.0);
        alSourcef(*auxSource, AL_MAX_GAIN, 1.0);
        alSourcePlay (*auxSource);

        //to make it play

        alSourcePlay(*auxSource);
        sources->push_back(auxSource);


    }

    /**
     * This method is necessary to allow the audio decreasion, because it set the real position of the player
     * @param x
     * @param z
     * @param angle
     */
    void updateListenerPosition(ALfloat x, ALfloat z, ALfloat angle){
        alListener3f(AL_POSITION, x, 1, z);

    }

    /**
     * This method is used to load the Environment audio source
     * @param x
     * @param z
     * @param y
     */
    void loadWorldSource(ALfloat x, ALfloat z, ALfloat y){


        this->wordlBuffer = alutCreateBufferFromFile(Constants::AUDIO_WORLD);

        alGenSources(1, &this->worldSource);
        alSourcef(this->worldSource, AL_PITCH,1);
        alSourcef(this->worldSource, AL_GAIN, 1);
        alSource3f(this->worldSource, AL_POSITION, x, y, z);
        alSource3f(this->worldSource, AL_VELOCITY, 0, 0, 0);
        alSourcei(this->worldSource, AL_LOOPING, AL_TRUE);

        //attach a source to a buffer
        alSourcei(this->worldSource, AL_BUFFER, this->wordlBuffer);

        //to make it play
        alSourcePlay(this->worldSource);
    }

};