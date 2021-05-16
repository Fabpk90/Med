//
// Created by fab on 15/05/2021.
//

#include "Framebuffer.h"
#include <iostream>
#include <stb/stb_image_write.h>

#include <chrono>
#include <ctime>
#include <string>


Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &idFbo);
    glDeleteTextures(1, &idColorTex);
    glDeleteTextures(1, &idDepthTex);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, idFbo);
}

void Framebuffer::writeToDisk()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s = "screenshots/";

    time_t t;

    s += std::to_string(time(&t));
    s += ".bmp";

    std::cout << "Saving " << s << std::endl;

    char *data =  new char[width * height * 3]; // 3 components (R, G, B)

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_flip_vertically_on_write(true);
    stbi_write_bmp(s.c_str(), width, height, 3, data);

    delete[] data;
}

Framebuffer::Framebuffer(int width, int height, bool hasDepth, bool hasColor, bool updateOnResize)
        : width(width), height(height), hasDepth(hasDepth), hasColor(hasColor)
{
    glGenFramebuffers(1, &idFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, idFbo);

    if(hasColor)
    {
        glGenTextures(1, &idColorTex);
        glBindTexture(GL_TEXTURE_2D, idColorTex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idColorTex, 0);
    }

    if(hasDepth)
    {
        glGenTextures(1, &idDepthTex);
        glBindTexture(GL_TEXTURE_2D, idDepthTex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                     nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTex, 0);
    }

    if( (hasColor || hasDepth) && glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Ay caramba, framebuffers are not supported by your cg" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::enableWrite(bool b)
{
}

void Framebuffer::enableRead(bool b)
{

}

void Framebuffer::unBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::getColorTexture()
{
    return idColorTex;
}

unsigned int Framebuffer::getDepthTexture()
{
    return idDepthTex;
}

void Framebuffer::setDepthTexture(unsigned int id)
{
    //if(idDepthTex != -1) handle referencing

    idDepthTex = id;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTex, 0);
}

void Framebuffer::setColorTexture(unsigned int id)
{
    //TODO: handle referencing here as well and bound fbo

    hasColor = true;

    idColorTex = id;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idColorTex, 0);
}

Framebuffer::Framebuffer(int width, int height, int colorTexId, int depthTexId) : width(width), height(height), idColorTex(colorTexId), idDepthTex(depthTexId)
{
    glGenFramebuffers(1, &idFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, idFbo);

    if(colorTexId != -1)
    {
        idColorTex = colorTexId;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idColorTex, 0);
    }

    if(depthTexId != -1)
    {
        idDepthTex = depthTexId;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTex, 0);
    }
}

void Framebuffer::OnResize(int width, int height)
{
    this->width = width;
    this->height = height;

    if(hasColor)
    {
        glBindTexture(GL_TEXTURE_2D, idColorTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }

    if(hasDepth)
    {
        glBindTexture(GL_TEXTURE_2D, idDepthTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                     nullptr);
    }
}