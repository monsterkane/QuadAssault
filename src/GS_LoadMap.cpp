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

void GlavnoStanje::UcitajMapu()
{
	maps=new unsigned char*[MX];
	for(int i=0; i<MX; i++)
	{
		maps[i]=new unsigned char[MY];
	}
	blokovi=new Block*[MX];
	for(int i=0; i<MX; i++)
	{
		blokovi[i]=new Block[MY];
	}

	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{		
			maps[i][j]=0;
			if(i==0 || j==0 || i==MX-1 || j==MY-1)
				maps[i][j]=1;
	}	

	kamera=new Objekt();
	kamera->PromijeniPoz(Vec2(0,0));	

	igrac=new Igrac();	

	ambijentnoSvjetlo=Vec3(0.1f, 0.1f, 0.1f);

	Vec2 igracPoz=Vec2(0,0);

    ifstream file_(nivo_datoteka_g.c_str(),ios::in);
	string linija_;
	while(getline(file_,linija_))
	{
		istringstream lstring(linija_,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{
			if(vrijednost=="block")
			{
				getline(lstring,vrijednost,' ');
				int x=atoi(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int y=atoi(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int tip=atoi(vrijednost.c_str());
				if(x/BLOCK_SIZE<MX && y/BLOCK_SIZE<MY)
					maps[x/BLOCK_SIZE][y/BLOCK_SIZE]=tip;
			}
			if(vrijednost=="light")
			{
				svjetla.push_back(new Svjetlo());
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
				svjetla.back()->Init(Vec2(x,y),radius,this);
				svjetla.back()->Postavke(Vec3(r,g,b),intenzitet);
				svjetla.back()->staticno=true;
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
			if(vrijednost=="player")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				igracPoz=Vec2(x,y);
			}	
			if(vrijednost=="weapon")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int id=atoi(vrijednost.c_str());
				stvari.push_back(new OruzjePickup());
				OruzjePickup* o=(OruzjePickup*)stvari.back();
				o->Init(Vec2(x,y),this,id);
			}
			if(vrijednost=="key")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int id=atoi(vrijednost.c_str());
				stvari.push_back(new KljucPickup());
				KljucPickup* k=(KljucPickup*)stvari.back();
				k->Init(Vec2(x,y),this,id);
			}
			if(vrijednost=="preload_sound")
			{
				getline(lstring,vrijednost,' ');
                mz->UcitajZvuk((char*)("../data/"+vrijednost).c_str());
			}
			if(vrijednost=="muzika")
			{
				getline(lstring,vrijednost,' ');				
                muzika.openFromFile((char*)("../data/"+vrijednost).c_str());
                muzika.setVolume(25);
                muzika.setLoop(true);
                muzika.play();
			}
			if(vrijednost=="mob")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				Mob* m=SpawnajMobPremaImenu(vrijednost);
				mobovi.push_back(m);
				mobovi.back()->Init(Vec2(x,y),this,maps);
			}
			if(vrijednost=="mobtrigger")
			{
				triggeri.push_back(new Trigger());
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
				Mob* m=SpawnajMobPremaImenu(vrijednost);								
				triggeri.back()->InitMob(Vec2(x,y),Vec2(x2,y2),Vec2(mx,my),m,this);
			}
			if(vrijednost=="endtrigger")
			{
				triggeri.push_back(new Trigger());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());											
				triggeri.back()->InitKraj(Vec2(x,y),Vec2(x2,y2),this);
			}
			if(vrijednost=="messagetrigger")
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
				triggeri.push_back(new Trigger());
				Poruka* p=new Poruka();
				p->Init(posiljatelj,text,trajanje,zvuk_file,this);
				triggeri.back()->InitPoruka(Vec2(x,y), Vec2(x2,y2), p, this);
			}
		}
	}
	file.close();
	igrac->Init(igracPoz,this,maps);
	InitBlokove();
}
Mob* GlavnoStanje::SpawnajMobPremaImenu(string ime)
{
	if(ime=="lasermob1")				
		return new LaserMob1();	
	if(ime=="plasmamob1")				
		return new PlazmaMob1();	
	if(ime=="minigunmob1")		
		return new MinigunMob1();
}
void GlavnoStanje::InitBlokove()
{
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{
		/*if(maps[i][j]==0)
            blokovi[i][j].Init(Vec2(i*BLOCK_SIZE, j*BLOCK_SIZE),maps[i][j],mt->DajTexturu("../data/Pozadina1.tga")->id, this);
		if(maps[i][j]==1)
            blokovi[i][j].Init(Vec2(i*BLOCK_SIZE, j*BLOCK_SIZE),maps[i][j],mt->DajTexturu("../data/Block.tga")->id, this);
		if(maps[i][j]==2)*/
			blokovi[i][j].Init(Vec2(i*BLOCK_SIZE, j*BLOCK_SIZE),maps[i][j], this);			
	}	
}
void GlavnoStanje::ObrisiMapu()
{
	for(int i=0; i<MX; i++)
		delete[] maps[i];
	delete[] maps;
	for(int i=0; i<MX; i++)
		delete[] blokovi[i];
	delete[] blokovi;
}
void GlavnoStanje::GenerirajPrazanLevel()
{
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{		
			maps[i][j]=0;
			if(i==0 || j==0 || i==MX-1 || j==MY-1)
				maps[i][j]=1;
	}	
	InitBlokove();
	for(int i=0; i<svjetla.size(); i++)
	{
		if(svjetla[i]->staticno==true)
		{
			delete svjetla[i];
			svjetla.erase(svjetla.begin()+i);
		}
	}
}
