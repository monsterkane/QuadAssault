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

    Vec2 playerPos=Vec2(0,0);

    ifstream file_(nivo_datoteka_g.c_str(),ios::in);
    string line_;
    while(getline(file_,line_))
	{
        istringstream lstring(line_,ios::in);
        string value;
        while(getline(lstring,value,' '))
		{
            if(value=="block")
			{
                getline(lstring,value,' ');
                int x=atoi(value.c_str());
                getline(lstring,value,' ');
                int y=atoi(value.c_str());
                getline(lstring,value,' ');
                int type=atoi(value.c_str());
				if(x/BLOCK_SIZE<MX && y/BLOCK_SIZE<MY)
                    map[x/BLOCK_SIZE][y/BLOCK_SIZE]=type;
			}
            if(value=="light")
			{
				lights.push_back(new Svjetlo());
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                float radius=atof(value.c_str());
                getline(lstring,value,' ');
                float intensity=atof(value.c_str());
                getline(lstring,value,' ');
                float r=atof(value.c_str());
                getline(lstring,value,' ');
                float g=atof(value.c_str());
                getline(lstring,value,' ');
                float b=atof(value.c_str());
				lights.back()->Init(Vec2(x,y),radius,this);
                lights.back()->Postavke(Vec3(r,g,b),intensity);
				lights.back()->staticno=true;
			}
		}
	}
	file_.close();

    ifstream file(nivo_datoteka.c_str(),ios::in);
    string line;
    while(getline(file,line))
	{
        istringstream lstring(line,ios::in);
        string value;
        while(getline(lstring,value,' '))
		{			
            if(value=="player")
			{
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                playerPos=Vec2(x,y);
			}	
            if(value=="weapon")
			{
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                int id=atoi(value.c_str());
				things.push_back(new OruzjePickup());
				OruzjePickup* o=(OruzjePickup*)things.back();
				o->Init(Vec2(x,y),this,id);
			}
            if(value=="key")
			{
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                int id=atoi(value.c_str());
                things.push_back(new KeyPickup());
                KeyPickup* k=(KeyPickup*)things.back();
				k->Init(Vec2(x,y),this,id);
			}
            if(value=="preload_sound")
			{
                getline(lstring,value,' ');
                soundManager->UcitajZvuk((char*)("../data/"+value).c_str());
			}
            if(value=="music")
			{
                getline(lstring,value,' ');
                music.openFromFile((char*)("../data/"+value).c_str());
                music.setVolume(25);
                music.setLoop(true);
                music.play();
			}
            if(value=="mob")
			{
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                Mob* m=SpawnMobByName(value);
				mobs.push_back(m);
				mobs.back()->Init(Vec2(x,y),this,map);
			}
            if(value=="mobtrigger")
			{
				triggers.push_back(new Trigger());
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                float x2=atof(value.c_str());
                getline(lstring,value,' ');
                float y2=atof(value.c_str());
                getline(lstring,value,' ');
                float mx=atof(value.c_str());
                getline(lstring,value,' ');
                float my=atof(value.c_str());
                getline(lstring,value,' ');
                Mob* m=SpawnMobByName(value);
				triggers.back()->InitMob(Vec2(x,y),Vec2(x2,y2),Vec2(mx,my),m,this);
			}
            if(value=="endtrigger")
			{
				triggers.push_back(new Trigger());
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                float x2=atof(value.c_str());
                getline(lstring,value,' ');
                float y2=atof(value.c_str());
				triggers.back()->InitKraj(Vec2(x,y),Vec2(x2,y2),this);
			}
            if(value=="messagetrigger")
			{				
                getline(lstring,value,' ');
                float x=atof(value.c_str());
                getline(lstring,value,' ');
                float y=atof(value.c_str());
                getline(lstring,value,' ');
                float x2=atof(value.c_str());
                getline(lstring,value,' ');
                float y2=atof(value.c_str());
                getline(lstring,value,';');
                string sender=value;
                getline(lstring,value,';');
                string text=value;
                getline(lstring,value,' ');
                float duration=atof(value.c_str());
                getline(lstring,value,' ');
                string sound_file="../data/"+value;
				triggers.push_back(new Trigger());
				Poruka* p=new Poruka();
                p->Init(sender,text,duration,sound_file,this);
				triggers.back()->InitPoruka(Vec2(x,y), Vec2(x2,y2), p, this);
			}
		}
	}
	file.close();
    player->Init(playerPos,this,map);
	InitBlocks();
}
Mob* GameState::SpawnMobByName(string name)
{
	if(name=="lasermob1")				
		return new LaserMob1();	
	if(name=="plasmamob1")				
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
