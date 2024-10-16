/**
*                                            Noclip Fly Include - v0.0.1
* Include created by Collw 
* Based on code from Southclaws
* The original code has been modified and enhanced, and has been refactored into an include file to simplify system integration.
*
* Improvements include:
* - Code optimization for better performance
* - Added flexibility and customizability for various use cases
* - Simplified structure for easier maintenance and integration
*
* This include aims to streamline the process of adding the system to your project.
*
*/





#if defined NoclipFly
    #endinput
#endif
#define NoclipFly

#include <a_samp>

//Modo do player
#define CAMERA_MODE_NONE    	0
#define CAMERA_MODE_FLY     	1
// Teclas de definição
#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8
#define MOVE_SPEED              100.0
#define ACCEL_RATE              0.03


enum noclipenum
{
	cameramode,
	flyobject,
	mode,
	lrold,
	udold,
	lastmove,
	Float:accelmul
}
new noclipdata[MAX_PLAYERS][noclipenum];

public NoclipInit()
{
	 	for(new x; x<MAX_PLAYERS; x++)
	{
		if(noclipdata[x][cameramode] == CAMERA_MODE_FLY) CancelFlyMode(x);
	}
	return 1;
}
public NoclipUpdate(playerid)
{

    	if(noclipdata[playerid][cameramode] == CAMERA_MODE_FLY)
	{
		new keys,ud,lr;
		GetPlayerKeys(playerid,keys,ud,lr);

		if(noclipdata[playerid][mode] && (GetTickCount() - noclipdata[playerid][lastmove] > 100))
		{
		    // If the last move was > 100ms ago, process moving the object the players camera is attached to
		    MoveCamera(playerid);
		}

		// Se o último movimento foi há mais de 100ms, processe o movimento do objeto ao qual a câmera do jogador está anexada
		if(noclipdata[playerid][udold] != ud || noclipdata[playerid][lrold] != lr)
		{
			if((noclipdata[playerid][udold] != 0 || noclipdata[playerid][lrold] != 0) && ud == 0 && lr == 0)
			{ // Todas as teclas foram liberadas, pare o objeto ao qual a câmera está anexada e redefina o multiplicador de aceleração.
				StopPlayerObject(playerid, noclipdata[playerid][flyobject]);
				noclipdata[playerid][mode]      = 0;
				noclipdata[playerid][accelmul]  = 0.0;
			}
			else
			{
            // Indica que uma nova tecla foi pressionada.

			   // Obtém a direção que o jogador deseja se mover, conforme indicado pelas teclas.
				noclipdata[playerid][mode] = GetMoveDirectionFromKeys(ud, lr);


                // Processa o movimento do objeto ao qual a câmera do jogador está anexada.
				MoveCamera(playerid);
			}
		}
		noclipdata[playerid][udold] = ud; noclipdata[playerid][lrold] = lr; // Store current keys pressed for comparison next update
		return 0;
	}

    return 1; // Retorne 1 para indicar que a atualização foi bem-sucedida
}
public NoclipConnect(playerid)
{
	noclipdata[playerid][cameramode] 	= CAMERA_MODE_NONE;
	noclipdata[playerid][lrold]	   	 	= 0;
	noclipdata[playerid][udold]   		= 0;
	noclipdata[playerid][mode]   		= 0;
	noclipdata[playerid][lastmove]   	= 0;
	noclipdata[playerid][accelmul]   	= 0.0;
	return 1;
}
stock FlyMode(playerid)
{
    // Cria um objeto invisível para a câmera do jogador ser anexada
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);

    // Cria o objeto e armazena no array 'noclipdata'
    noclipdata[playerid][flyobject] = CreatePlayerObject(playerid, 19300, X, Y, Z, 0.0, 0.0, 0.0);

    // Coloca o jogador no modo de espectador para que os objetos sejam transmitidos com base na localização da câmera
    TogglePlayerSpectating(playerid, true);

    // Anexa a câmera do jogador ao objeto criado
    AttachCameraToPlayerObject(playerid, noclipdata[playerid][flyobject]);

    // Marca que o jogador está no modo Fly
    SetPVarInt(playerid, "FlyMode", 1);
    noclipdata[playerid][cameramode] = CAMERA_MODE_FLY;

    return 1;
}

stock CancelFlyMode(playerid)
{
    // Obter a posição atual da câmera ANTES de destruir o objeto
    new Float:camX, Float:camY, Float:camZ;
    GetPlayerCameraPos(playerid, camX, camY, camZ);

    // Cancelar o Fly Mode e restaurar o jogador ao controle normal
    DeletePVar(playerid, "FlyMode");
    CancelEdit(playerid);
    TogglePlayerSpectating(playerid, false);

    // Colocar o jogador na posição onde a câmera está
    SetPlayerPos(playerid, camX, camY, camZ);

    // Destruir o objeto associado ao Fly Mode
    DestroyPlayerObject(playerid, noclipdata[playerid][flyobject]);
    noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;

    return 1;
}

stock GetMoveDirectionFromKeys(ud, lr)
{
	new direction = 0;

    if(lr < 0)
	{
		if(ud < 0) 		direction = MOVE_FORWARD_LEFT; 	// Tecla para Cima & Esquerda pressionada
		else if(ud > 0) direction = MOVE_BACK_LEFT; 	// Tecla para Baixo & Esquerda pressionada
		else            direction = MOVE_LEFT;          // Tecla para Esquerda pressionada
	}
	else if(lr > 0) 	// Tecla para Direita pressionada
	{
		if(ud < 0)      direction = MOVE_FORWARD_RIGHT;  // Tecla para Cima & Direita pressionada
		else if(ud > 0) direction = MOVE_BACK_RIGHT;     // Tecla para Baixo & Direita pressionada
		else			direction = MOVE_RIGHT;          // Tecla para Direita pressionada
	}
	else if(ud < 0) 	direction = MOVE_FORWARD; 	// Tecla para Cima pressionada
	else if(ud > 0) 	direction = MOVE_BACK;		// Tecla para Baixo pressionada

	return direction;
}

stock GetNextCameraPosition(move_mode, Float:CP[3], Float:FV[3], &Float:X, &Float:Y, &Float:Z)
{
    // Calcula a próxima posição da câmera com base em sua posição atual e na direção em que está olhando
    #define OFFSET_X (FV[0]*6000.0)
	#define OFFSET_Y (FV[1]*6000.0)
	#define OFFSET_Z (FV[2]*6000.0)

	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			X = CP[0]+OFFSET_X;
			Y = CP[1]+OFFSET_Y;
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_BACK:
		{
			X = CP[0]-OFFSET_X;
			Y = CP[1]-OFFSET_Y;
			Z = CP[2]-OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			X = CP[0]-OFFSET_Y;
			Y = CP[1]+OFFSET_X;
			Z = CP[2];
		}
		case MOVE_RIGHT:
		{
			X = CP[0]+OFFSET_Y;
			Y = CP[1]-OFFSET_X;
			Z = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			X = CP[0]+(-OFFSET_X - OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y + OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			X = CP[0]+(-OFFSET_X + OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y - OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			X = CP[0]+(OFFSET_X  - OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  + OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			X = CP[0]+(OFFSET_X  + OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  - OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
	}
}

stock MoveCamera(playerid)
{
	new Float:FV[3], Float:CP[3];
	GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);          // Posição da câmera no espaço
    GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);  // Para onde a câmera está olhando

	// Aumenta o multiplicador de aceleração quanto mais tempo a tecla é mantida pressionada
	if(noclipdata[playerid][accelmul] <= 1) noclipdata[playerid][accelmul] += ACCEL_RATE;

	// Determina a velocidade de movimento da câmera com base no multiplicador de aceleração
	new Float:speed = MOVE_SPEED * noclipdata[playerid][accelmul];

	// Calcula a próxima posição da câmera com base em sua posição atual e na direção em que está olhando
	new Float:X, Float:Y, Float:Z;
	GetNextCameraPosition(noclipdata[playerid][mode], CP, FV, X, Y, Z);
	MovePlayerObject(playerid, noclipdata[playerid][flyobject], X, Y, Z, speed);

	// Armazena a última vez que a câmera foi movida como agora
	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}

