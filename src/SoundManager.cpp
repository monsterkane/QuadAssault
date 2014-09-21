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

#include "SoundManager.h"

vector<Zvuk>* ManagerZvuka::DajZvukove()
{
	return &zvukovi;
}		
Zvuk* ManagerZvuka::DajZvuk(char* ime)
{
	for(int i=0; i<zvukovi.size(); i++)
		if(zvukovi[i].file==ime)
		{
			return &zvukovi[i];
		}
	UcitajZvuk(ime);
	return &zvukovi.back();
}
bool ManagerZvuka::UcitajZvuk(char* ime)
{
	sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile(ime))
	{
        cerr << "ERROR: Errors loading sound files.";
		return false;
	}
	Zvuk z;
	z.file=ime;
	z.buffer=Buffer;	
	zvukovi.push_back(z);
	cout << "Sound loaded : " << ime << endl;
	return true;
}
void ManagerZvuka::Brisi()
{
	zvukovi.clear();
}
ManagerZvuka::ManagerZvuka()
{
}
ManagerZvuka::~ManagerZvuka()
{
	zvukovi.clear();
}
