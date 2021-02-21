#if defined _chooseteam_included
  #endinput
#endif

#define _chooseteam_included

static const KEYSMENU = MENU_KEY_1|MENU_KEY_2|MENU_KEY_5|MENU_KEY_6;

stock chooseteam_init () {
	register_clcmd("chooseteam", "chooseteam");
	register_clcmd("jointeam", "jointeam");
	register_menucmd(register_menuid("Team_Select", 1), KEYSMENU, "teamselect"); 
	register_menucmd(-2, KEYSMENU, "teamselect"); 

	register_message(get_user_msgid("HostagePos"), "msgHostagePos");
	register_message(get_user_msgid("ShowMenu"), "msgShowMenu");
	register_message(get_user_msgid("VGUIMenu"), "msgVguiMenu");
	register_message(get_user_msgid("HideWeapon"), "msgHideWeapon");
}

// Blocked  command

public chooseteam (id) {
	set_pdata_int(id, 125, get_pdata_int(id, 125, 5) & ~(1<<8), 5);
	return PLUGIN_CONTINUE;
}

public jointeam (id) {
	new selected;
	
	selected = read_argv_int(1);

	return chooseteam_check(id, selected)
}

public teamselect (id, selected) {
	return chooseteam_check(id, (selected+1))
}

public chooseteam_check (id, selected) {
	new TeamName:team;

	switch (selected) {
		case 1:
			team = TEAM_TERRORIST;
		case 2:
			team = TEAM_CT;
		case 5:
			team = TEAM_UNASSIGNED;
		case 6:
			team = TEAM_SPECTATOR;
	}

	return check_team(id, team)
}

public msgHostagePos(msgid, dest, id) {
	return PLUGIN_HANDLED;
}

public msgShowMenu(msgid, dest, id) {
	if (!shouldAutoJoin(id))
		return (PLUGIN_CONTINUE);

	static team_select[] = "#Team_Select";
	static menu_text_code[sizeof team_select];
	get_msg_arg_string(4, menu_text_code, sizeof menu_text_code - 1);
	if (!equal(menu_text_code, team_select))
		return (PLUGIN_CONTINUE);

	setForceTeamJoinTask(id, msgid);

	return (PLUGIN_HANDLED);
}

public msgVguiMenu(msgid, dest, id) {
	if (get_msg_arg_int(1) != 2 || !shouldAutoJoin(id))
		return (PLUGIN_CONTINUE);

	setForceTeamJoinTask(id, msgid);

	return (PLUGIN_HANDLED);
}

public msgHideWeapon(msgid, dest, id) {
	const money = (1 << 5);
	set_msg_arg_int(1, ARG_BYTE, get_msg_arg_int(1) | money);
}

bool:shouldAutoJoin(id) {
	return (!get_user_team(id) && !task_exists(id));
}

setForceTeamJoinTask(id, menu_msgid) {
	static param_menu_msgid[2];
	param_menu_msgid[0] = menu_msgid;
	set_task(0.1, "taskForceTeamJoin", id, param_menu_msgid, sizeof param_menu_msgid);
}

public taskForceTeamJoin(menu_msgid[], id) {
	if (get_user_team(id))
		return;

	forceTeamJoin(id, menu_msgid[0], "5", "5");
}


stock forceTeamJoin(id, menu_msgid, team[] = "5", class[] = "0") {
	static jointeam[] = "jointeam";
	if (class[0] == '0') {
		engclient_cmd(id, jointeam, team);
		return;
	}

	static msg_block, joinclass[] = "joinclass";
	msg_block = get_msg_block(menu_msgid);
	set_msg_block(menu_msgid, BLOCK_SET);
	engclient_cmd(id, jointeam, team);
	engclient_cmd(id, joinclass, class);
	set_msg_block(menu_msgid, msg_block);
	set_task(0.1, "taskSetPlayerTeam", id);
}

public taskSetPlayerTeam(id) {
	if (!is_user_connected(id))
		return;

	if (g_bCaptain) {
		transferToSpec(id);
		return;
	}
}

stock transferToSpec(id) {
	setTeam(id, TEAM_SPECTATOR);
	set_entvar(id, var_solid, SOLID_NOT);
	set_entvar(id, var_movetype, MOVETYPE_FLY);
}

setTeam(id, TeamName:iTeam) {
	set_member(id, m_bTeamChanged, false);

	if (is_user_alive(id))
		user_silentkill(id);

	switch (iTeam) {
		case TEAM_TERRORIST: {
			rg_internal_cmd(id, "jointeam", "1");
			rg_internal_cmd(id, "joinclass", "5");
		}
		case TEAM_CT: {
			rg_internal_cmd(id, "jointeam", "2");
			rg_internal_cmd(id, "joinclass", "5");
		}
		case TEAM_SPECTATOR: {
			rg_internal_cmd(id, "jointeam", "6");
		}
	}
}
