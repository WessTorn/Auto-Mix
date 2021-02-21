stock pugmenu_start (id) {
	new menu = menu_create("Меню:", "pugmenu_handler");

	menu_additem(menu, "Сменить команду");
	menu_additem(menu, "Пауза");
	menu_additem(menu, "Кикнуть игрока");
	menu_additem(menu, "\yАдмин меню");

	menu_display(id, menu);
}

stock bool:player_can_vote (id) {
	if (is_restarting()) {
		return false;
	}
	if (!client_is_player(id)) {
		chat_print(id, "%L", LANG_SERVER, "PUG_VOTING_SPEC");
		return false;
	}

	return true;
}

public pugmenu_handler (id, menu, item) {
	if (item == MENU_EXIT)
		return PLUGIN_HANDLED;

	switch (item) {
		case 0:
			client_cmd(id, "jointeam");
		case 1:
			if (player_can_vote(id)) {
				if (game_is_live())
					votepause_start(id);
				else
					chat_print(id, "%L", LANG_SERVER, "PUG_GAME_NOTSTARTED");
			}
		case 2:
			if (player_can_vote(id))
				votekick_select_player_menu(id);
		case 3:
			client_cmd(id, "amxmodmenu");
	}

	return PLUGIN_HANDLED;
}

stock menu_iteminfo (menu, item, info[], size)  {
	new dummy;
	menu_item_getinfo(menu, item, dummy, info, size, _, _, dummy);
}

stock pugmenu_mute (id) {
	new menu = menu_create_players(id, "pugmenu_hmute");
	menu_display(id, menu);
}

public pugmenu_hmute (id, menu, item) {
	if (item == MENU_EXIT)
		return PLUGIN_HANDLED;

	new authid[32];
	menu_iteminfo(menu, item, authid, charsmax(authid));

	new target = find_player("c", authid);

	if (target)
		client_mute(id, target);
		
	return PLUGIN_HANDLED;
}

stock pugmenu_unmute (id) {
	new menu = menu_create_players(id, "pugmenu_hunmute");
	menu_display(id, menu);
}

public pugmenu_hunmute (id, menu, item) {
	if (item == MENU_EXIT)
		return PLUGIN_HANDLED;

	new authid[32];
	menu_iteminfo(menu, item, authid, charsmax(authid));

	new target = find_player("c", authid);

	if (target)
		client_unmute(id, target);
		
	return PLUGIN_HANDLED;
}
