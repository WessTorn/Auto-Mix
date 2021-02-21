stock TeamName:client_get_team(id) {
	return get_member(id, m_iTeam);
}

stock client_set_team(id, TeamName:team) {
	rg_set_user_team(id, team);
}

stock client_give_money(id, amount) {
	set_member(id, m_iAccount, amount);
}

stock client_get_money(id) {
	return get_member(id, m_iAccount);
}

stock client_set_money(id, amount) {
	rg_add_account(id, amount, AS_SET);
}

stock client_drop_c4(id) {
	rg_drop_item(id, "weapon_c4");
}
