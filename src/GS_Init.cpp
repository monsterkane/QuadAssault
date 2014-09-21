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

#include "GameState.h"
#include "UI_Button.h"
#include "UI_Window.h"
#include "GUI_Functions.h"

bool GameState::Init(Game* game)
{
    this->igra=game;
	gotovo=false;

    gameState=this;
	lightSet=false;
	mobTriggerSet=0;
	light_red=1.0; light_green=10; light_blue=1.0; light_intensity=8.0; light_radius=128.0;

	textureManager=new ManagerTextura();
    textureManager->UcitajTexturu("../data/cursor.tga");
    textureManager->UcitajTexturu("../data/backgroundUniverse.tga");

	soundManager=new ManagerZvuka();		

    shaders.push_back(new Shader("../data/LightVS.txt", "../data/LightFS.txt"));
    shaders.push_back(new Shader("../data/RenderSceneVS.txt", "../data/RenderSceneFS.txt"));

	fonts.push_back(sf::Font());
    fonts.back().loadFromFile("../data/DialogueFont.TTF");

	uiManager=new UI_Menager();
    uiManager->Init(textureManager,game);

	uiManager->DodajProzor(new UI_Prozor());	
	
	UI_Prozor* p=uiManager->DajProzore().back();
	p->Init(uiManager,Vec2(32,32), Vec2(320, 240), "Alati");
	
	p->DodajElement(new UI_Gumb());	
	UI_Gumb* g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uiManager->DajProzore().back(),Vec2(16,32),Vec2(32,32),SetupLightGUI,textureManager->DajTexturu("../data/button_light.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uiManager->DajProzore().back(),Vec2(64,32),Vec2(32,32),SetupTriggerGUI,textureManager->DajTexturu("../data/button_light.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uiManager->DajProzore().back(),Vec2(16,72),Vec2(32,32),GenerateEmptyLevelGUI,textureManager->DajTexturu("../data/button_gen.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uiManager->DajProzore().back(),Vec2(64,72),Vec2(32,32),SaveLevelGUI,textureManager->DajTexturu("../data/button_save.tga")->id);

	DEVMODE=false;

    SetupFBO();

    LoadMap();

	transition=T_FADEIN;
	transition_color=0.0f;
	transition_speed=1;
    levelCompleted=false;

	gameOverTimer=3;

	return true;
}

bool GameState::SetupFBO()
{
    sf::Vector2u window_size = igra->GetRW()->getSize();
	glGenFramebuffers(1,&fbo);	

	glGenTextures(1,&lightmap);
	glBindTexture(GL_TEXTURE_2D,lightmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        window_size.x,
        window_size.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1,&normalmap);
	glBindTexture(GL_TEXTURE_2D,normalmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        window_size.x,
        window_size.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1,&geometry);
	glBindTexture(GL_TEXTURE_2D,geometry);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        window_size.x,
        window_size.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
		
	return true;
}
void GameState::DeleteFBO()
{
	glDeleteFramebuffers(1,&fbo);
	glDeleteTextures(1,&lightmap);
	glDeleteTextures(1,&normalmap);
	glDeleteTextures(1,&geometry);
}



