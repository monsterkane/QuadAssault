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

#include "Game.h"

bool Game::Init(char* configFile)
{
    // This falls under the config ***
    width=800;
    height=600;
    //width=1680;
    //height=1050;
    char* name="QuadAssault";
    int style=sf::Style::Close;
    //stil=sf::Style::Fullscreen;
	//***************************
	cout << "----Quad Assault----" << endl;
	cout << "*******************" << endl;		

    cout << "Setting up window..." << endl;
    rw.create(sf::VideoMode((int)width,(int)height,32), name, style);
    //rw.setFramerateLimit(60);
    rw.setMouseCursorVisible(false);
		
    done=false;
	srand(time(NULL));
		
    cout << "Setting up OpenGL ..." << endl;
    glViewport(0,0,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    glOrtho(0,width,height,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );	
	
    GLenum error=glewInit();

    if(error!=GLEW_OK)
	{
        cerr << "ERROR: Impossible to initialize Glew. Your graphics card probably does not support Shader Model 2.0.\n";
		return false;
	}

    cout << "The game is ready." << endl;
	return true;
}
void Game::SetState(Stanje* state, bool destroy)
{	
    if(destroy==true)
	{
        states[states.size()-1]->Izlaz();
        delete states[states.size()-1];
        states.erase(states.begin()+states.size()-1);
        cout << "Old state deleted." << endl;
	}
    states.push_back(state);
    cout << "Setting up new state..." << endl;
    states.back()->Init(this);
    states.back()->PrviUpdate=true;
	
    cout << "The game is ready." << endl;
}
void Game::Loop()
{
    while(done==false)
	{
        static sf::Clock clock;
        float deltaT=clock.restart().asSeconds();
		
        states.back()->Input();
        states.back()->Update(deltaT);
				
        states.back()->Render();
        rw.display();

        if(states.back()->Gotovo())
		{
            states.back()->Izlaz();
            delete states.back();
            states.pop_back();
		}
        if(states.size()==0)
            done=true;
	}
}
void Game::Deinit()
{
    for(int i=0; i<states.size(); i++)
	{
        states[i]->Izlaz();
        delete states[i];
	}
    states.clear();
    rw.close();
}

sf::RenderWindow* Game::GetRW()
{
	return &rw;
}

int Game::Rand(int i1, int i2)
{
	return rand()%i2+i1;
}
