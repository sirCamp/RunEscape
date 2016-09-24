//
// Created by stefano on 02/09/16.
//

#include <fstream>

class TextureManager{

private:

    unsigned char* data; // Actual RGB data
    int textureNumber;

    /**
     *  This method allow to bind the loaded Texture to the variable
     * @param texture
     * @param x
     * @param y
     * @param format
     * @return
     */
    bool textureBinder(unsigned char* texture, int x = 256, int y = 256, int format = GL_RGB){

        textureNumber++;

        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1.0f);
        glEnable(GL_CULL_FACE);
        glBindTexture(GL_TEXTURE_2D, textureNumber);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, format, GL_UNSIGNED_BYTE, texture);

        return true;
    }



    /**
     * This method is used to load a BMP texture
     * @param fileName
     * @param width
     * @param height
     * @param format
     * @return
     */
    GLint bmpLoader(const char* fileName, unsigned int width = 256, unsigned int height = 256, int format = GL_RGB){

        unsigned char header[54]; // Each BMP file begins by a 54-bytes header
        unsigned int dataPos;     // Position in the file where the actual data begins
        unsigned int imageSize;   // = width*height*3

        FILE * file = fopen(fileName,"rb");

        if (!file){
            Logger::error("Image could not be opened");
            return 0;
        }

        if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
            Logger::error("BPM file is not correct");
            return false;
        }

        if ( header[0]!='B' || header[1]!='M' ){
            Logger::error("Not a correct BMP file");
            return 0;
        }

        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize==0 || width == 512)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos==0)      dataPos=54; // The BMP header is done that way

        // Create a buffer
        data = new unsigned char [imageSize];

        // Read the actual data from the file into the buffer
        fread(data,1,imageSize,file);

        //Everything is in memory now, the file can be closed
        fclose(file);

        //it binds a texture
        textureBinder(data, width, height, format);

        return 0;
    }


    /**
     * This method is use to load a RAW texture
     * @param fileName
     * @param width
     * @param height
     * @return
     */
    GLint rawLoader(const char* fileName, unsigned int width = 256, unsigned int height = 256){

        FILE* fHan = fopen(fileName, "rb");

        unsigned int imageSize = width*height*3;
        data = new unsigned char [imageSize];

        if(fHan == NULL){
            Logger::error("Image could not be opened");
        }

        fread(data, width * height, 3, fHan);
        fclose(fHan);

        //it binds a texture
        textureBinder(data, width, height);

        return 0;
    }

public:


    /**
     * The Constructor
     * @return
     */
    TextureManager(): textureNumber(0){}



    /**
     * This method is used to choose the right way to load the texture
     * @param fileName
     * @param width
     * @param height
     * @param format
     * @param type
     */
    void loadTexture(const char* fileName, unsigned int width = 256, unsigned int height = 256, int format = GL_RGB, int type = Constants::LOAD_BMP_TEXTURE){


        switch (type){

            case Constants::LOAD_RAW_TEXTURE:

                this->rawLoader(fileName,width,height);
                break;

            case Constants::LOAD_BMP_TEXTURE:
                this->bmpLoader(fileName,width,height,format);
                break;
        }

    }
};