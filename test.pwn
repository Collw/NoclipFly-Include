// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

#include <a_samp>
#include <noclipfly>
#include <zcmd>


main()
{
	print("\n----------------------------------");
	print(" Blank Gamemode by your name here");
	print("----------------------------------\n");
}



public OnGameModeInit()
{
	// Don't use these lines if it's a filterscript
	SetGameModeText("Collw NoclipFly");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	
	NoclipInit();// Fun��o respons�vel por verificar e desativar o modo de voo ("Fly Mode") para todos os jogadores que estejam atualmente usando o noclip/fly.
	
	return 1;
}

public OnGameModeExit()
{
	return 1;
}
//comando:
CMD:fly(playerid)// comando para ativar e desativar o modo de voo
{


	if(GetPVarType(playerid, "FlyMode")) CancelFlyMode(playerid);
	else FlyMode(playerid);
	return 1;
}
public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
    NoclipConnect(playerid);//� respons�vel por inicializar os dados relacionados ao modo "Noclip" (Fly Mode) para um jogador espec�fico assim que ele se conecta ao servidor.-
	return 1;
}
public OnPlayerUpdate(playerid)
{

   NoclipUpdate(playerid); //Fun��o respons�vel por gerenciar o movimento do jogador quando ele est� no modo "Fly" (Noclip Mode), atualizando a posi��o da c�mera e o objeto ao qual a c�mera do jogador est� anexada.
   return 1;
}


public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/mycommand", cmdtext, true, 10) == 0)
	{
		// Do something here
		return 1;
	}
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}


