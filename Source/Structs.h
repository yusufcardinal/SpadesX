//Copyright DarkNeutrino 2021
#ifndef STRUCTS_H
#define STRUCTS_H

#include <bits/types/struct_timeval.h>
#include <enet/enet.h>
#include <libvxl/libvxl.h>
#include <time.h>

#include "Enums.h"
#include "Queue.h"
#include "Types.h"
#include "Util/Line.h"
#include "enet/protocol.h"

typedef struct {
    uint8 sent;
    float fuse;
    uint8 exploded;
    Vector3f position;
    Vector3f velocity;
    unsigned long long timeSinceSent;
    unsigned long long timeNow;
} Grenade;

typedef struct { // Seriously what the F. Thank voxlap motion for this mess.
    Vector3f position;
    Vector3f eyePos;
    Vector3f velocity;
    Vector3f strafeOrientation;
    Vector3f heightOrientation;
    Vector3f forwardOrientation;
} Movement;

typedef struct { //Yet again thanks voxlap.
    Vector3f forward;
    Vector3f strafe;
    Vector3f height;
} Orientation;

typedef struct {
    // compressed map
    Queue* compressedMap;
    uint32 compressedSize;
    vec3i resultLine[50];
    long unsigned int mapSize;
    struct libvxl_map map;
} Map;

typedef struct
{
    uint8     score[2];
    uint8     scoreLimit;
    IntelFlag intelFlags;
    Vector3f  intel[2];
    Vector3f  base[2];
    uint8     playerIntelTeamA; // player ID if intel flags & 1 != 0
    uint8     playerIntelTeamB; // player ID if intel flags & 2 != 0
    uint8     intelHeld[2];
} ModeCTF;

typedef struct {
    uint8     countOfUsers;
    //
    uint8 numPlayers;
    uint8 maxPlayers;
    //
    Color3i  colorFog;
    Color3i  colorTeamA;
    Color3i  colorTeamB;
    char     nameTeamA[11];
    char     nameTeamB[11];
    GameMode mode;
    // mode
    ModeCTF ctf;
    // respawn area
    Quad2D spawns[2];
    uint32    inputFlags;
} Protocol;

typedef struct {
	Queue*    queues;
    State     state;
    Weapon    weapon;
    Team      team;
    Tool      item;
    uint32    kills;
    Color3i   color;
    char      name[17];
    ENetPeer* peer;
    uint8     respawnTime;
    uint32    startOfRespawnWait;
    Color4i   toolColor;
    int       HP;
    uint8     grenades;
    uint8     blocks;
    uint8     weaponReserve;
    short     weaponClip;
    vec3i     resultLine[50];
    uint8     ip[4];
    uint8     alive;
    uint8	  input;
    uint8	  allowKilling;
    uint8     allowTeamKilling;
    unsigned long long timeSinceLastWU;
    uint16    ups;
    uint8     muted;
    uint8     canBuild;
    Grenade   grenade[3];
    uint8     toldToMaster;
    uint8     hasIntel;

    uint8     movForward;
    uint8     movBackwards;
    uint8     movLeft;
    uint8     movRight;
    uint8     jumping;
    uint8     crouching;
    uint8     sneaking;
    uint8     sprinting;
    uint8     primary_fire;
    uint8     secondary_fire;
    time_t    sinceLastBaseEnter;
    time_t    sinceLastBaseEnterRestock;
    Vector3f  locAtClick;

    //Bellow this point is stuff used for calculating movement.
    Movement movement;
    uint8 airborne;
    uint8 wade;
    float lastclimb;
} Player;

typedef struct {
	// Master
    ENetHost* client;
    ENetPeer* peer;
    ENetEvent event;
    uint8     enableMasterConnection;
    time_t    timeSinceLastSend;
} Master;

typedef struct {
	ENetHost* host;
	Player player[32];
	Protocol protocol;
	Master master;
    Map map;
    uint8 globalAK;
    uint8 globalAB;
} Server;

#endif
