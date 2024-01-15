UENUM(BlueprintType)
enum EBattleState : uint8
{
    BATTLE_STATE_POSITIONING,
    BATTLE_STATE_GET_NEXT_PLAYER,
    BATTLE_STATE_PLAYER_ACTION_SELECT,
    BATTLE_STATE_PLAYER_SELECT_TARGET,
    BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET,
    BATTLE_STATE_WAIT_ACTION
};