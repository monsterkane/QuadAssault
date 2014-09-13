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
#include "KeyPickup.h"
#include "SharedVariables.h"

void GameState::LoadMap()
{
	map=new unsigned char*[MX];
	for(int i=0; i<MX; i++)
	{
		map[i]=new unsigned char[MY];
	}
	blocks=new Block*[MX];
	for(int i=0; i<MX; i++)
	{
		blocks[i]=new Block[MY];
	}

	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{		
			map[i][j]=0;
			if(i==0 || j==0 || i==MX-1 || j==MY-1)
				map[i][j]=1;
	}	

	camera=new Objekt();
	camera->PromijeniPoz(Vec2(0,0));	

	player=new Igrac();	

	ambientLight=Vec3(0.1f, 0.1f, 0.1f);

	Vec2 igracPoz=Vec2(0,0);

    ifstream file_(nivo_datoteka_g.c_str(),ios::in);
	string linija_;
	while(getline(file_,linija_))
	{
		istringstream lstring(linija_,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{
			if(vrijednost=="blok")
			{
				getline(lstring,vrijednost,' ');
				int x=atoi(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int y=atoi(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int tip=atoi(vrijednost.c_str());
				if(x/BLOCK_SIZE<MX && y/BLOCK_SIZE<MY)
					map[x/BLOCK_SIZE][y/BLOCK_SIZE]=tip;
			}
			if(vrijednost=="svjetlo")
			{
				lights.push_back(new Svjetlo());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float radius=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float intenzitet=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float r=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float g=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float b=atof(vrijednost.c_str());
				lights.back()->Init(Vec2(x,y),radius,this);
				lights.back()->Postavke(Vec3(r,g,b),intenzitet);
				lights.back()->staticno=true;
			}
		}
	}
	file_.close();

    ifstream file(nivo_datoteka.c_str(),ios::in);
	string linija;
	while(getline(file,linija))
	{
		istringstream lstring(linija,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{			
			if(vrijednost=="igrac")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				igracPoz=Vec2(x,y);
			}	
			if(vrijednost=="oruzje")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int id=atoi(vrijednost.c_str());
				things.push_back(new OruzjePickup());
				OruzjePickup* o=(OruzjePickup*)things.back();
				o->Init(Vec2(x,y),this,id);
			}
			if(vrijednost=="kljuc")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int id=atoi(vrijednost.c_str());
				things.push_back(new KljucPickup());
				KljucPickup* k=(KljucPickup*)things.back();
				k->Init(Vec2(x,y),this,id);
			}
			if(vrijednost=="preload_zvuk")
			{
				getline(lstring,vrijednost,' ');
                soundManager->UcitajZvuk((char*)("../data/"+vrijednost).c_str());
			}
			if(vrijednost=="muzika")
			{
				getline(lstring,vrijednost,' ');				
                music.openFromFile((char*)("../data/"+vrijednost).c_str());
                music.setVolume(25);
                music.setLoop(true);
                music.play();
			}
			if(vrijednost=="mob")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				Mob* m=SpawnMobByName(vrijednost);
				mobs.push_back(m);
				mobs.back()->Init(Vec2(x,y),this,map);
			}
			if(vrijednost=="mobtrigger")
			{
				triggers.push_back(new Trigger());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float mx=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float my=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				Mob* m=SpawnMobByName(vrijednost);								
				triggers.back()->InitMob(Vec2(x,y),Vec2(x2,y2),Vec2(mx,my),m,this);
			}
			if(vrijednost=="krajtrigger")
			{
				triggers.push_back(new Trigger());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());											
				triggers.back()->InitKraj(Vec2(x,y),Vec2(x2,y2),this);
			}
			if(vrijednost=="porukatrigger")
			{				
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,';');
				string posiljatelj=vrijednost;
				getline(lstring,vrijednost,';');
				string text=vrijednost;
				getline(lstring,vrijednost,' ');
				float trajanje=atof(vrijednost.c_str());	
				getline(lstring,vrijednost,' ');
                string zvuk_file="../data/"+vrijednost;
				triggers.push_back(new Trigger());
				Poruka* p=new Poruka();
				p->Init(posiljatelj,text,trajanje,zvuk_file,this);
				triggers.back()->InitPoruka(Vec2(x,y), Vec2(x2,y2), p, this);
			}
		}
	}
	file.close();
	player->Init(igracPoz,this,map);
	InitBlocks();
}
Mob* GameState::SpawnMobByName(string name)
{
	if(name=="lasermob1")				
		return new LaserMob1();	
	if(name=="plazmamob1")				
		return new PlazmaMob1();	
	if(name=="minigunmob1")		
		return new MinigunMob1();
}
void GameState::InitBlocks()
{
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{
		/*if(mapa[i][j]==0)
            blokovi[i][j].Init(Vec2(i*BLOCK_SIZE, j*BLOCK_SIZE),mapa[i][j],mt->DajTexturu("../data/Pozadina1.tga")->id, this);
		if(mapa[i][j]==1)
            blokovi[i][j].Init(Vec2(i*BLOCK_SIZE, j*BLOCK_SIZE),mapa[i][j],mt->DajTexturu("../data/Block.tga")->id, this);
		if(mapa[i][j]==2)*/
			blocks[i][j].Init(Vec2(i*BLOCK_SIZE, j*BLOCK_SIZE),map[i][j], this);			
	}	
}
void GameState::DeleteMap()
{
	for(int i=0; i<MX; i++)
		delete[] map[i];
	delete[] map;
	for(int i=0; i<MX; i++)
		delete[] blocks[i];
	delete[] blocks;
}
void GameState::GenerateEmptyLevel()
{
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{		
			map[i][j]=0;
			if(i==0 || j==0 || i==MX-1 || j==MY-1)
				map[i][j]=1;
	}	
	InitBlocks();
	for(int i=0; i<lights.size(); i++)
	{
		if(lights[i]->staticno==true)
		{
			delete lights[i];
			lights.erase(lights.begin()+i);
		}
	}
}
