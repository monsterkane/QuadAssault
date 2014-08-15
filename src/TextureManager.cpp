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

#include "TextureManager.h"
#include "Dependencies.h"

Textura::Textura()
{
}
Textura::~Textura()
{
}
Textura::Textura(char* file, GLuint id)
{
	this->file=file;
	this->id=id;
}		
	

ManagerTextura::ManagerTextura()
{
}
ManagerTextura::~ManagerTextura()
{
	for(int i=0; i<texture.size(); i++)
	glDeleteTextures(1,&texture[i].id);
	texture.clear();
}

vector<Textura>* ManagerTextura::DajTexture()
{
	return &texture;
}

Textura* ManagerTextura::DajTexturu(int i)
{
	return &texture[i];
}
Textura* ManagerTextura::DajTexturu(char* name)
{	
	for(int i=0; i<texture.size(); i++)
		if(texture[i].file==name)
		{
			return &texture[i];
		}
	UcitajTexturu(name);
	return &texture.back();
}

void ManagerTextura::BrisiTexturu(int i)
{
	texture.erase(texture.begin()+i);
	glDeleteTextures(1,&texture[i].id);
}
void ManagerTextura::BrisiTexturu(char* name)
{
	for(int i=0; i<texture.size(); i++)
		if(texture[i].file==name)
		{
			texture.erase(texture.begin()+i);
			glDeleteTextures(1,&texture[i].id);
			break;
		}
}

bool ManagerTextura::UcitajTexturu(char* name)
{	
	GLuint id;
	sf::Image image;	
    if(image.loadFromFile(name))
	{			
		glGenTextures(1,&id);
		glBindTexture(GL_TEXTURE_2D,id);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());			
        glTexImage2D( GL_TEXTURE_2D, 0, 4, image.getSize().x, image.getSize().y, 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);				
			
		texture.push_back(Textura(name,id));
		cout << "Textura ucitana : " << name << endl;
		return true;
	}
	else
	{
        cerr << "ERROR: Greska kod ucitavanja textura.";
		return false;
	}
}

void ManagerTextura::Brisi()
{
	for(int i=0; i<texture.size(); i++)
	glDeleteTextures(1,&texture[i].id);
	texture.clear();
}
