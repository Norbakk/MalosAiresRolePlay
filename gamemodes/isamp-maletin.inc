#if defined _isamp_maletin_included
	#endinput
#endif
#define _isamp_maletin_included

//=============================SISTEMA DE MALETINES=============================

//================================CONSTANTES====================================

#define MAX_DINERO_MALETIN 500000

//================================COMANDOS======================================

CMD:maletin(playerid, params[])
{
	new command[40], amount, hand, briefCaseMoney, string[128];

	hand = SearchHandsForItem(playerid, ITEM_ID_MALETINDINERO);
	if(hand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes un malet�n para dinero en alguna de tus manos.");

 	briefCaseMoney = GetHandParam(playerid, hand);
	if(sscanf(params, "s[40]i", command, amount))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /maletin [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} retirar [dinero] - guardar [dinero]");
        SendFMessage(playerid, COLOR_WHITE, "El malet�n contiene $%d pesos.", briefCaseMoney);

	} else if(strcmp(command, "retirar", true) == 0) {
		
	    if(amount <= 0 || amount > briefCaseMoney)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Cantidad inv�lida.");
		        
	    GivePlayerCash(playerid, amount);
		SetHandItemAndParam(playerid, hand, ITEM_ID_MALETINDINERO, briefCaseMoney - amount);
		PlayerActionMessage(playerid, 15.0, "abre su malet�n y retira algo de su interior.");
		ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
  		format(string, sizeof(string), "Retir� $%d de un malet�n", amount);
    	log(playerid, LOG_MONEY, string);
			
	} else if(strcmp(command, "guardar", true) == 0) {
		
	    if(amount <= 0 || amount > GetPlayerCash(playerid))
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Cantidad inv�lida.");
		if(amount + briefCaseMoney > MAX_DINERO_MALETIN)
			return SendClientMessage(playerid, COLOR_YELLOW2, "�Tanto dinero no entra en el malet�n!");

	    GivePlayerCash(playerid, -amount);
		SetHandItemAndParam(playerid, hand, ITEM_ID_MALETINDINERO, briefCaseMoney + amount);
		PlayerActionMessage(playerid, 15.0, "abre su malet�n y guarda algo en su interior.");
		ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
  		format(string, sizeof(string), "Guard� $%d en un malet�n", amount);
    	log(playerid, LOG_MONEY, string);
	}
	return 1;
}
