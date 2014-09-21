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

#ifndef GS_H
#define GS_H
#include "State.h"
#include "Block.h"
#include "Projectile.h"
#include "TextureManager.h"
#include "UI_Menager.h"
#include "Player.h"
#include "Explosion.h"
#include "Mob.h"
#include "LaserMob1.h"
#include "PlasmaMob1.h"
#include "MinigunMob1.h"
#include "Particle.h"
#include "Trigger.h"
#include "Thing.h"
#include "WeaponPickup.h"
#include "SoundManager.h"
#include "Message.h"
#include "MenuState.h"

class GameState : public Stanje
{
private:

	bool DEVMODE;
	
    Svjetlo* light;
    float light_red, light_green, light_blue, light_intensity, light_radius; // light color

    BlockType blockType; // type of block which is set
    bool lightSet;

    unsigned char mobTriggerSet;
    Trigger* trigger;
    Vec2 trigger_begin, trigger_end, trigger_spawn;

    unsigned char** map;
    Block** blocks;

    float gameOverTimer; // when reaches zero, the game goes to the main menu
    bool levelCompleted;

    Igrac* player;

    vector<Projektil*> missiles;
    vector<Explosion*> explosions;
    vector<Svjetlo*> lights;
    vector<Shader*> shaders;
    vector<Mob*> mobs;

    UI_Menager* uiManager;

    ManagerTextura* textureManager;
    ManagerZvuka* soundManager;

    Objekt* camera;
    Vec2 mousePos;

    GLuint fbo;
	
    GLuint lightmap;
    GLuint normalmap;
    GLuint geometry;
    Vec3 ambientLight;
	
    sf::Music music;

    vector<Cestica*> particles;
    vector<Trigger*> triggers;
    vector<Stvar*> things;
    vector<sf::Sound*> sounds;
    vector<sf::Font> fonts;
    vector<Poruka*> messages;

    unsigned char transition; // fade to black
    float transition_color;
    float transition_speed;

public:
    bool Init(Game* game);
	void Input();
	void Update(float deltaT);	
	void UpdateDev(float deltaT);
	void Render();
	void Izlaz();	

    bool SetupFBO();
    void DeleteFBO();

    void LoadMap();
    void InitBlocks();
    void SaveBlocks();
    Mob* SpawnMobByName(string name);

    void UpdateSequences(float deltaT);

    unsigned char** GetMap();
    Block* GetBlock(short x, short y);
    Igrac* GetPlayer();
    vector<Mob*>* GetMobs();
    vector<Projektil*>* GetProjectiles();
    vector<sf::Font>* GetFonts();

    Svjetlo* GetLight(bool stationary);
    Explosion* GetExplosion();
    Projektil* GetProjectile(Projektil* p);
    Cestica* GetParticle(Cestica* c);
    sf::Sound* GetSound(sf::Sound* s, Zvuk* sound);
    Mob* GetMob(Mob* m);
    Poruka* GetMessage(Poruka* m);
    Stvar* GetThing(Stvar* t);
	
    void RenderObjects(unsigned char stationary);

    void RenderGeometry();
    void RenderGeometryNormal();
    void RenderGeometryGlow();

    void RenderNormalOnFBO();
    void RenderGeometryOnFBO();
    void RenderLightOnFBO();
    void RenderScene();

    void CompleteLevel();
    void DeleteMap();

    ManagerTextura* GetTM();
    ManagerZvuka* GetSM();

    /* GUI functions */
    void SetupLight();
    void SetupMobTrigger();
    void GenerateEmptyLevel();
};
#endif
