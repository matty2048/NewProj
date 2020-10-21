#include "Texture.h"

Texture::Texture(unsigned int size_x, unsigned int size_y):size_x(size_x),size_y(size_y)
{
	glGenTextures(1, &TexID);
    glBindTexture(GL_TEXTURE_2D, TexID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::changesize(unsigned int new_x, unsigned int new_y)
{
    this->size_x = new_x;
    this->size_y = new_y;
    glBindTexture(GL_TEXTURE_2D, TexID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, new_x, new_y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
}


