#if defined _hook_included
  #endinput
#endif

#define _hook_included

stock hook_init () {
	RegisterHookChain(RG_CBasePlayer_Spawn, "rgPlayerSpawn", true);
	RegisterHookChain(RG_CBasePlayer_MakeBomber, "rgPlayerMakeBomber", false);
}

public rgPlayerSpawn(id) {
	if(g_bVotingProcess) {
		SetBlackScreenFade(1);
	}
	
	if (!g_bKnifeRound)
		return;

	rg_remove_all_items(id);
	rg_give_item(id, "weapon_knife");
}

public rgPlayerMakeBomber(const this) {  // Варн
	if (g_bKnifeRound) {
		SetHookChainReturn(ATYPE_BOOL, false);
		return;
	}
	if (!game_is_started()) {
		SetHookChainReturn(ATYPE_BOOL, false);
		return;
	}
}
