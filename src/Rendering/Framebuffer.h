//
// Created by fab on 15/05/2021.
//

#ifndef MATERIALEDITOR_FRAMEBUFFER_H
#define MATERIALEDITOR_FRAMEBUFFER_H

#include <glad/glad.h>

class Framebuffer
{
protected:
    GLuint idFbo;
    GLuint idColorTex;
    GLuint idDepthTex;

    int width;
    int height;

    bool hasDepth;
    bool hasColor;
public:
    Framebuffer() = delete;
    Framebuffer(int width, int height, bool hasDepth = true, bool hasColor = false, bool updateOnResize = false);
    Framebuffer(int width, int height, int colorTexId, int depthTexId);

    ~Framebuffer();

    void bind();

    void unBind();

    void writeToDisk() ;

    void enableWrite(bool b) ;

    void enableRead(bool b) ;

    unsigned int getColorTexture() ;

    void setColorTexture(unsigned int id) ;

    void setDepthTexture(unsigned int id) ;

    unsigned int getDepthTexture() ;

public:
    void OnResize(int i, int i1) ;

};


#endif //MATERIALEDITOR_FRAMEBUFFER_H
