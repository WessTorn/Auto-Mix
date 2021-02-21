stock PUG_GetPlayersNum(bool:bBots = false)
 {
	new iPlayers[MAX_PLAYERS],iNum[2];
	
	get_players(iPlayers,iNum[0],bBots ? "he" : "he","TERRORIST");
	get_players(iPlayers,iNum[1],bBots ? "he" : "he","CT");
	
	return iNum[0] + iNum[1];
}
