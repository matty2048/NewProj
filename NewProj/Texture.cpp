#include "Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
std::map<const char*, Texture*> Texture::texes;
Texture::Texture(unsigned int size_x, unsigned int size_y):size_x(size_x),size_y(size_y)
{
	glGenTextures(1, TexID);
    glBindTexture(GL_TEXTURE_2D, *TexID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

Texture::Texture(const char* path) //loads texture from path
{
    if (texes.find(path) != texes.end())
    {
        Texture* t = texes[path];
        this->data = t->data;
        this->size_x = t->GetSize_x();
        this->size_y = t->GetSize_y();
        this->TexID = t->TexID;
        finished = true;
    }
    else {
        int x;
        int y;

        int numberofChannels;
        this->data = stbi_load(path, &x, &y, &numberofChannels, 0);
        this->size_x = x;
        this->size_y = y;
        Texture* a = this;
        texes.emplace(path, a);
    }
}

void Texture::ChangeSize(unsigned int new_x, unsigned int new_y)
{
    
    this->size_x = new_x;
    this->size_y = new_y;
    
    glBindTexture(GL_TEXTURE_2D, *TexID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, new_x, new_y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadTex()
{
    if (finished) return;
    glGenTextures(1, this->TexID);
    glBindTexture(GL_TEXTURE_2D, *TexID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->size_x,this->size_y , 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    finished = true;
}


