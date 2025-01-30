  update_pos(&player_pos,
    game->images.player->instances->x / BPP,
    game->images.player->instances->y / BPP);

(also change keyhook handle_player_move to just affect playing foes)
