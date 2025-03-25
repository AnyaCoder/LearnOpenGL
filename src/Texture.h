#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture {
public:
    unsigned int ID;
    Texture(const char* path);
    void bind() const;
    
private:
    int width, height, nrChannels;
};

#endif
