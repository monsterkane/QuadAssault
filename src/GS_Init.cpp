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

bool GlavnoStanje::Init(Game* igra)
{
	this->igra=igra;
	gotovo=false;

	extStanje=this;
	postavljaSvjetlo=false;
	postavljaMobTrigger=0;
	sr=1.0; sg=10; sb=1.0; si=8.0; srad=128.0;

	mt=new ManagerTextura();
    mt->UcitajTexturu("../data/cursor.tga");
    mt->UcitajTexturu("../data/backgroundUniverse.tga");

	mz=new ManagerZvuka();		

    shaderi.push_back(new Shader("../data/LightVS.txt", "../data/LightFS.txt"));
    shaderi.push_back(new Shader("../data/RenderSceneVS.txt", "../data/RenderSceneFS.txt"));

	fontovi.push_back(sf::Font());
    fontovi.back().loadFromFile("../data/DialogueFont.TTF");

	uim=new UI_Menager();
	uim->Init(mt,igra);

	uim->DodajProzor(new UI_Prozor());	
	
	UI_Prozor* p=uim->DajProzore().back();
	p->Init(uim,Vec2(32,32), Vec2(320, 240), "Alati");
	
	p->DodajElement(new UI_Gumb());	
	UI_Gumb* g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uim->DajProzore().back(),Vec2(16,32),Vec2(32,32),PosSvjetGUI,mt->DajTexturu("../data/button_light.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uim->DajProzore().back(),Vec2(64,32),Vec2(32,32),PosTrigGUI,mt->DajTexturu("../data/button_light.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uim->DajProzore().back(),Vec2(16,72),Vec2(32,32),GenPrazniLevelGUI,mt->DajTexturu("../data/button_gen.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
    g->Init(uim->DajProzore().back(),Vec2(64,72),Vec2(32,32),SpremiLevelGUI,mt->DajTexturu("../data/button_save.tga")->id);

	DEVMODE=false;

	PostaviFBO();	

	UcitajMapu();

	tranzicija=T_FADEIN;
	tBoja=0.0f;
	brzinaFadeanja=1;
	nivoZavrsen=false;

	gameOverTimer=3;

	return true;
}

bool GlavnoStanje::PostaviFBO()
{
    sf::Vector2u window_size = igra->GetRW()->getSize();
	glGenFramebuffers(1,&fbo);	

	glGenTextures(1,&lightmapa);
	glBindTexture(GL_TEXTURE_2D,lightmapa);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        window_size.x,
        window_size.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1,&normalmapa);
	glBindTexture(GL_TEXTURE_2D,normalmapa);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        window_size.x,
        window_size.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1,&geometrija);
	glBindTexture(GL_TEXTURE_2D,geometrija);
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
void GlavnoStanje::IzbrisiFBO()
{
	glDeleteFramebuffers(1,&fbo);
	glDeleteTextures(1,&lightmapa);
	glDeleteTextures(1,&normalmapa);
	glDeleteTextures(1,&geometrija);
}



