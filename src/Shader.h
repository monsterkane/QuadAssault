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

#ifndef SHADER_H
#define SHADER_H
#include "Dependencies.h"

class Shader
{
public:
	Shader();
	Shader(char* vertex_program_file, char* fragment_program_file);
	~Shader();

	void Log(GLuint obj);
		
	const char* readFile(char* file);

	void Bind();
	void UnBind();

	unsigned int ID;

private:		
	unsigned int vertex_program;
	unsigned int fragment_program;
};
#endif
