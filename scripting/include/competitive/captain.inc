#define MinPlayers 4

new g_bCaptain;

new RandomPlayerCT;
new RandomPlayerT;

stock captain() {
	g_bCaptain = true;
	new iPlayers[32],  iPlayer[32], iNum, num;
	get_players(iPlayers, iNum, "h");
	get_players(iPlayer, num, "ch");
	
	if(iNum < MinPlayers) {
		chat_print(0, "%L", LANG_SERVER, "PUG_CAPTAIN_PLAYERS_REQUIRED", (iNum - MinPlayers));
		fnNextVote();
		return PLUGIN_HANDLED;
	}

	for(new i; i < iNum; i++) {
		user_silentkill(iPlayers[i]);
		client_set_team(iPlayers[i], TEAM_SPECTATOR);
	}
	RandomPlayerCT = iPlayer[random(num)];
	RandomPlayerT = iPlayers[random(iNum)];
	
	while(RandomPlayerCT == RandomPlayerT) {
		RandomPlayerT = iPlayers[random(iNum)];
	}

	client_set_team(RandomPlayerCT, TEAM_CT);
	client_set_team(RandomPlayerT, TEAM_TERRORIST);
	
	chat_print(0, "%L", LANG_SERVER, "PUG_CAPTAINS_ARE", getName(RandomPlayerCT), getName(RandomPlayerT));
	
	new First = random(2);
	set_task(1.5, "captain_menu", First ? RandomPlayerCT : RandomPlayerT);
	set_task(0.2, "PlayersList", _, _, _, "b");
	
	server_cmd("sv_restart 1");
	
	return PLUGIN_CONTINUE;
}

public captain_menu(id) {
	new iMenu = menu_create("Выберите игрока:", "captainmenu_handler")
	
	set_task(10.5, "menu_task", id);

	new iPlayers[32], iNum, szPlayer[10], iPlayer;
	get_players(iPlayers, iNum, "eh", "SPECTATOR");

	new szBuffer[256];
	for (new i; i < iNum; i++) {
		iPlayer = iPlayers[i];

		if(client_get_team(iPlayer) != TEAM_SPECTATOR)
			continue;

		num_to_str(iPlayer, szPlayer, charsmax(szPlayer));
		add(szBuffer, charsmax(szBuffer), fmt("%n ", iPlayer));

		menu_additem(iMenu, szBuffer, szPlayer);
		szBuffer = "";
	}

	menu_setprop(iMenu, MPROP_EXIT, MEXIT_NEVER);
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public captainmenu_handler(id, iMenu, item) {
	if(item == MENU_EXIT) {
		return PLUGIN_HANDLED;
	}

	new szData[6], szName[64], iAccess, iCallback;
	menu_item_getinfo(iMenu, item, iAccess, szData, charsmax(szData), szName, charsmax(szName), iCallback);
	menu_destroy(iMenu);

	new iPlayer = str_to_num(szData);

	client_set_team(iPlayer, client_get_team(id));
	chat_print(0, "%L", LANG_SERVER, "PUG_CAPTAIN_CHOOSE", getName(id), getName(iPlayer));
	remove_task(id);

	new iPlayers[MAX_PLAYERS], iNum;
	get_players(iPlayers, iNum);

	new iTotalPlayers;
	for (new i; i < iNum; i++) {
		new tempid = iPlayers[i];

		if (client_get_team(tempid) == TEAM_SPECTATOR) continue;

		iTotalPlayers++;
	}

	if (iTotalPlayers == get_pug_maxplayers()) {
		chat_print(0, "%L", LANG_SERVER, "PUG_TEAMFULL_START");
		resetCaptainData();
		return PLUGIN_HANDLED;
	}
	
	if(is_user_connected(RandomPlayerCT) && is_user_connected(RandomPlayerT)) {
		set_task(1.5,"captain_menu",id == RandomPlayerCT ? RandomPlayerT : RandomPlayerCT)
	} else {
		set_task(5.0,"CheckCaptainJoin",id == RandomPlayerCT ? RandomPlayerCT : RandomPlayerT)
	}
	return PLUGIN_HANDLED;
}

public menu_task(id, iMenu) {
	if (!g_bCaptain) {
		return PLUGIN_HANDLED;
	}
	new iPlayers[32], iNum;
	get_players(iPlayers, iNum, "h");
	
	new randomnum = random(iNum);
	while(client_get_team(iPlayers[randomnum]) != TEAM_SPECTATOR) {
		randomnum = random(iNum);
	}

	if(is_user_connected(id)) {
		menu_destroy(iMenu);
		chat_print(0, "%L", LANG_SERVER, "PUG_CAPTAIN_AUTOCHOOSE", getName(id), getName(iPlayers[randomnum]));
		client_set_team(iPlayers[randomnum],client_get_team(id))
		set_task(1.5, "captain_menu", id == RandomPlayerCT ? RandomPlayerT : RandomPlayerCT);
	} else {
		set_task(5.0, "CheckCaptainJoin", id == RandomPlayerCT ? RandomPlayerT : RandomPlayerCT);
	}

	new bool:has_spec
	for(new i; i < iNum; i++) {
		if(client_get_team(iPlayers[i]) == TEAM_SPECTATOR)
			has_spec = true;
	}

	if(!has_spec) {
		chat_print(0, "%L", LANG_SERVER, "PUG_TEAMFULL_START");
		resetCaptainData();
		return PLUGIN_HANDLED;
	}
	show_menu(id, 0, "^n", 1);
	return PLUGIN_HANDLED;
}

public CheckCaptainJoin(NextCaptainMenu) {
	if(is_user_connected(RandomPlayerCT) && is_user_connected(RandomPlayerT)) {
		set_task(1.5, "captain_menu", NextCaptainMenu)
	} else {
		set_task(5.0, "CheckCaptainJoin", NextCaptainMenu)
	}
}

public PlayersList() {
	new iPlayers[32], iNum;
	get_players(iPlayers, iNum, "h");
	
	new posTR, posCT, posSPEC;
	new HudTextTR[512], HudTextCT[512], HudTextSPEC[512];
	new szNamec[38];
	
	for(new i; i < iNum; i++) {
		if(iPlayers[i] == RandomPlayerCT || iPlayers[i] == RandomPlayerT) {
			formatex(szNamec, charsmax(szNamec), "%s (K)", getName(iPlayers[i]));
		} else {
			szNamec = getName(iPlayers[i]);
		}

		if(client_get_team(iPlayers[i]) == TEAM_TERRORIST) {
			posTR += formatex(HudTextTR[posTR], 511-posTR,"%s^n", szNamec);
		} else if(client_get_team(iPlayers[i]) == TEAM_CT) {
			posCT += formatex(HudTextCT[posCT], 511-posCT, "%s^n", szNamec);
		} else {
			posSPEC += formatex(HudTextSPEC[posSPEC], 511-posSPEC, "%s^n", szNamec);
		}
	}

	for(new i; i < iNum; i++) {
		set_hudmessage(255, 0, 0, 0.70, 0.16, 0, 0.0, 1.1, 0.0, 0.0, 1);
		show_hudmessage(iPlayers[i], "Terrorists:");
		
		set_hudmessage(255, 255, 255, 0.70, 0.19, 0, 0.0, 1.1, 0.0, 0.0, 2);
		show_hudmessage(iPlayers[i], HudTextTR);
		
		set_hudmessage(0, 0, 255, 0.70, 0.51, 0, 0.0, 1.1, 0.0, 0.0, 3);
		show_hudmessage(iPlayers[i], "Counter-Terrorist:");
		
		set_hudmessage(255, 255, 255, 0.70, 0.54, 0, 0.0, 1.1, 0.0, 0.0, 4);
		show_hudmessage(iPlayers[i], HudTextCT);
	}
}

resetCaptainData() {
	remove_task();
	g_bCaptain = false;
	fnNextVote();
}
