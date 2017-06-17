#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class DrawAPI
{
    
public:
    void virtual draw(float x, float y) = 0;
};

class DrawCircleConsole : public DrawAPI 
{
public:
    void draw(float x, float y) 
    {
        //~ Position doesn't change!
        std::cout << R"(
                           xx
                         xxxxxx
                       xxxxxxxxxx
                      xxxxxxxxxxxx
                      xxxxxxxxxxxx
                       xxxxxxxxxx
                         xxxxxx          
                           xx
        )" << std::endl;
    }
};

class DrawLosangeConsole : public DrawAPI 
{
public:
    void draw(float x, float y) 
    {
        //~ Position doesn't change!
        std::cout << R"(
                *
               ***
              *****
             *******
              *****
               ***
                *
        )" << std::endl;
    }
};



class DrawAPIOpenGL : public DrawAPI
{
protected:
    GLuint vao, vbo, shade;
    DrawAPIOpenGL(GLuint shade) : shade(shade) {}
public:
    void virtual draw(float x, float y) = 0;
};

class DrawLinedTriangleOpenGL : public DrawAPIOpenGL
{
public:
    DrawLinedTriangleOpenGL(GLuint shade) : DrawAPIOpenGL(shade) 
    {
        GLfloat vertices[] = {        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
        };

        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void draw(float x, float y) 
    {
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(shade, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(this->vao);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(0);   
    }
};

class DrawLinedRectangleOpenGL : public DrawAPIOpenGL 
{
public:
    DrawLinedRectangleOpenGL(GLuint shade) : DrawAPIOpenGL(shade) 
    {
        GLfloat vertices[] = {        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void draw(float x, float y) 
    {
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(shade, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(this->vao);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(0);   
    }
};

class DrawRectangleOpenGL : public DrawAPIOpenGL 
{
    
public:
    DrawRectangleOpenGL(GLuint shade) : DrawAPIOpenGL(shade)
    {
        GLfloat vertices[] = {        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };
        
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
    }
    void draw(float x, float y) 
    {        
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(shade, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);        
    }
};

class DrawTriangleOpenGL : public DrawAPIOpenGL 
{
public:
    DrawTriangleOpenGL(GLuint shade) : DrawAPIOpenGL(shade) 
    {
          GLfloat vertices[] = {        
            0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
        };

        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void draw(float x, float y) 
    {
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(shade, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);   
    }
};

#endif

