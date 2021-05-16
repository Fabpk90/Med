//
// Created by fab on 15/05/2021.
//

#ifndef MATERIALEDITOR_VBO_H
#define MATERIALEDITOR_VBO_H

#include <glad/glad.h>

class Vbo
{
public:
    struct Element
    {
        int NbFloats = 0;
        int OffsetFloats = 0;

        Element(int nbFloats)
        {
            NbFloats = nbFloats;
        }

        Element()
        {
            NbFloats = 0;
        }

    };

    Vbo(int nbElements, int nbVertices, bool useEbo = false);

    ~Vbo();

    void setElementDescription(int index, Element desc);

    void setElementData(int dataIndex, int vertexIndex, float f1);

    void setElementData(int dataIndex, int vertexIndex, float f1, float f2);

    void setElementData(int dataIndex, int vertexIndex, float f1, float f2, float f3);

    void setElementData(int dataIndex, int vertexIndex, float f1, float f2, float f3, float f4);

    void createCPUSide();

    void deleteCPUSide();

    void createGPUSide();

    void deleteGPUSide();

    void draw();

    void bind();

private:
    Element *elements;
    int nbElements;
    int nbVertices;

    int totalElementSize;
    int sizeOfOneVertex;

    float *elementsValue;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    bool useEbo;
};

#endif //MATERIALEDITOR_VBO_H
