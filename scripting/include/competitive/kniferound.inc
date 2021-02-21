new bool:g_bKnifeRound;
new bool:g_bVotingProcess;
new g_Votes[2];

stock KnifeRound() {
	g_bKnifeRound = true;
	g_bVotingProcess = false;
	exec_Knife();
	chat_print(0, "%L", LANG_SERVER, "PUG_KNIFE_START");
	
	return PLUGIN_CONTINUE;
}

public vote_win(team) {
	static iPlayers[MAX_PLAYERS], count;
	switch(team) {
		case 0: {
			get_players(iPlayers, count, "eh", "CT");
		}
		case 1: {
			get_players(iPlayers, count, "eh", "TERRORIST");
		}
	}
	for(new i; i < count; i++) {
		ShowMenu(iPlayers[i]);
	}
	set_task(8.0, "finishvote");
}

public ShowMenu(id) {
	g_bVotingProcess = true;
	SetBlackScreenFade(1);
	if(g_bVotingProcess) {
		show_menu(id, 3, "\wПоменятся командами?^n^n\w[\r1\w] \yПерейти^n\w[\r2\w] \rОстаться", -1, "ShowMenuHan");
	}
	
	return PLUGIN_CONTINUE;
}

public handleShowMenu(id, key) {
	if(!g_bVotingProcess) return;

	switch(key) {
		case 0: {
			g_Votes[0]++;
		}
		case 1: {
			g_Votes[1]++;
		}
	} 
	
	return;
}

public finishvote() {
	server_cmd("sv_restartround 1");
	
	if (g_Votes[0] > g_Votes[1]) {
		chat_print(0, "%L", LANG_SERVER, "PUG_KNIFE_SWAP");
		teams_switch()
	} else {
		chat_print(0, "%L", LANG_SERVER, "PUG_KNIFE_STAY");
	}

	SetBlackScreenFade(0)
	
	g_Votes[0] = 0;
	g_Votes[1] = 0;
	g_bVotingProcess = false;
	
	liveOnThree();
	
	return PLUGIN_HANDLED;
}

public taskRR (T[]) {
	server_cmd("sv_restart %s",T);
}

stock SetBlackScreenFade(fade) {
	new time, hold, flags;
	static iMsgScreenFade; 
	if(!iMsgScreenFade) 
		iMsgScreenFade = get_user_msgid("ScreenFade");
	
	switch (fade) {
		case 1: { time = 1; hold = 1; flags = 4; }
		default: { time = 4096; hold = 1024; flags = 2; }
	}

	message_begin(MSG_BROADCAST, iMsgScreenFade);
	write_short(time);
	write_short(hold);
	write_short(flags);
	write_byte(0);
	write_byte(0);
	write_byte(0);
	write_byte(255);
	message_end();
}
