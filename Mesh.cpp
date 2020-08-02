#include "Mesh.h"
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

#ifndef SPLIT_H
#define SPLIT_H
//helpful for parsing the file, thanks to my intro cs course for this function
void split(std::string temp, std::string words[], char del, int maxWords)
{
	std::stringstream tempStream(temp);
	int i = 0;
	std::string tempFromTemp;
	while(std::getline(tempStream, tempFromTemp, del))
	{
		if (i == maxWords)
			return;
		words[i] = tempFromTemp;
		i++;
	}
}

#endif

//supposed to read in obj files exporrted from blender
//with the following settings:
/*
triangulate faces
*/
namespace gum
{
Mesh::Mesh(const std::string& objfile)
{
    //actual file reading
	std::ifstream inFile(objfile);
	//if the file can't be opened we just turn it into a cube lol
	if(!inFile.is_open())
	{
		std::cerr << "ERROR: cannot open mesh file: '" << objfile << "'; turning it into a cube..." << std::endl;
        inFile.open("res/cube.obj");
	}

    std::vector<GLfloat> tempVertices;
    std::vector<GLfloat> tempNormals;

    std::string temp;
    while(std::getline(inFile, temp))
    {
        //add another delimeter to the end of the line
        temp += ' ';
        //skip comments in the file
        if (temp[0] == '#')
            continue;

        //if it is about to describe a vertex;
        else if(temp[0] == 'v')
        {
            //if its a texture coord
            if (temp[1] == 't')
            {
                std::string words[3];
                split(temp, words, ' ', 4);
                /*
                tempUVcoords.push_back(std::stof(words[1]));
                tempUVcoords.push_back(std::stof(words[2]));
                */
            }
            //if it's a vertex normal
            else if (temp[1] == 'n')
            {
                std::string words[4];
                split(temp, words, ' ', 4);

                tempNormals.push_back(std::stof(words[1]));
                tempNormals.push_back(std::stof(words[2]));
                tempNormals.push_back(std::stof(words[3]));
            }
            //if its a vertex
            else
            {
                std::string words[4];
                split(temp, words, ' ', 4);

                tempVertices.push_back(std::stof(words[1]));
                tempVertices.push_back(std::stof(words[2]));
                tempVertices.push_back(std::stof(words[3]));
            }
        }

        //if it's a face
        else if(temp[0] == 'f')
        {
            std::string words[4];
            split(temp, words, ' ', 4);

            //face describes vertIndex/vertUv/normIndex in .obj file
            for(int i = 1; i < 4; i++)
            {
                std::string vertData[3];
                split(words[i], vertData, '/', 3);

                int vertIndex = std::stoi(vertData[0]);
                int normIndex = std::stoi(vertData[2]);

                Vec3 vertex(
                        tempVertices.at((vertIndex-1) * 3 + 0),
                        tempVertices.at((vertIndex-1) * 3 + 1),
                        tempVertices.at((vertIndex-1) * 3 + 2)
                );
                vertices.push_back(vertex);

                Vec3 normal(
                    tempNormals.at((normIndex -1 ) * 3 + 0),
                    tempNormals.at((normIndex -1 ) * 3 + 1),
                    tempNormals.at((normIndex -1 ) * 3 + 2)
                );
                normals.push_back(normal);
            }
        }

        //other stuff we don't care about from the file, -redundant but explicit
        else
        {
            continue;
        }
    
	}
    inFile.close();

    //vertex vao/vbo
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size() * 3, vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

    //normals
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size() * 3, normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
}

void Mesh::render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view) {
    glBindVertexArray(vertexArray);

    Mat4 mvp = proj_view * this->world_transform();

    glUseProgram(shaderProgram);

    GLint mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.data());

    GLint modelLocation = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, this->world_transform().data());

    GLint viewLocation = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, camera.getView().data());

    GLint modelViewLocation = glGetUniformLocation(shaderProgram, "modelview");
    Mat4 mv = camera.getView() * this->world_transform();
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, mv.data());

    GLint cameraPosLocation = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(cameraPosLocation, 1, camera.world_transform()[3].data());

    glEnableVertexAttribArray(vertexArray);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(vertexArray);
}

}
