/*
 *   Copyright (C) 2011, 2012 Marko Stanić
 *   Copyright (C) 2014 QuadAssault contributors    
 *
 *   This file is part of QuadAssault.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with This program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Shader.h"

Shader::Shader(){};

Shader::Shader(char* vertex_program_file, char* fragment_program_file)
{
	vertex_program=glCreateShader(GL_VERTEX_SHADER);
	fragment_program=glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs=readFile(vertex_program_file);
	const char* fs=readFile(fragment_program_file);

	glShaderSource(vertex_program,1,&vs,0);
	glShaderSource(fragment_program,1,&fs,0);

	glCompileShader(vertex_program);	
	glCompileShader(fragment_program);

    GLint success;
    glGetShaderiv(fragment_program, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(fragment_program, sizeof(InfoLog), NULL, InfoLog);
        cerr << "ERROR: " << InfoLog;
    }

    ID=glCreateProgram();
	glAttachShader(ID,vertex_program);
    glAttachShader(ID,fragment_program);
	glLinkProgram(ID);

	Log(ID);	
}

void Shader::Bind()
{
	glUseProgram(ID);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

Shader::~Shader()
{
	glDetachShader(ID,vertex_program);
	glDetachShader(ID,fragment_program);

	glDeleteShader(vertex_program);
	glDeleteShader(fragment_program);
	glDeleteProgram(ID);
}

const char* Shader::readFile(char* file)
{
	FILE* f=fopen(file,"rt");
	fseek(f,0,SEEK_END);
	int broj=ftell(f);
	rewind(f);

	char* output=(char*)malloc(sizeof(char)*(broj+1));
	broj=fread(output,sizeof(char),broj,f);
	output[broj]='\0';
	fclose(f);

	return output;
}

void Shader::Log(GLuint obj)
{
	int infologLength = 0;
	int maxLength;
 
	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
 
	char *infoLog=(char*)malloc(sizeof(char)*maxLength);
 
	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
 
	if (infologLength > 0)
        cerr << infoLog << endl;//printf("%s\n",infoLog);
}
