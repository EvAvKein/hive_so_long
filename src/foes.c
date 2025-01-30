#include "../include/so_long.h"

bool create_foe(t_game *game, t_pos pos)
{
  t_foe	*foe;
  t_foe *prev_foe;
 
  foe = malloc(sizeof(t_foe));
  if (!foe)
    return (!perrno("Foe creation", ENOMEM));
  foe->pending = FOE_PENDING;
  foe->pos = pos;
  foe->standing_on_collectible = false;
  foe->standing_on_exit = false;
  foe->img_i = -1;
  foe->next = NULL;
  if (game->foes)
  {
    prev_foe = game->foes;
    while (prev_foe->next)
      prev_foe = prev_foe->next;
    prev_foe->next = foe;
  }
  else
    game->foes = foe;
  return (1);
}

void destroy_foe(t_game *game, t_offset *player_move)
{
  t_foe *foe;
	
  edit_attack_counters(game, --game->progress.attacks);
  foe = adjacent_foe(game, player_move);
  if (!foe)
    return ; 
  game->images.foe->instances[foe->img_i].enabled = false;
  if (foe->standing_on_collectible)
    game->map->layout[foe->pos.y][foe->pos.x] = COLLECTIBLE_CHAR;
  else if (foe->standing_on_exit)
    game->map->layout[foe->pos.y][foe->pos.x] = EXIT_CHAR;
  else
    game->map->layout[foe->pos.y][foe->pos.x] = EMPTY_CHAR;
}

static void move_foe(t_game *game, t_foe *foe,
  char direction1, char direction2)
{
  t_entity	ahead;

  ahead = adjacent_entity(game->map->layout, foe->pos, direction1);
  if ((ahead.chr == WALL_CHAR) || (ahead.chr == FOE_CHAR))
  {
    ahead = adjacent_entity(game->map->layout, foe->pos, direction2);
    if ((ahead.chr == WALL_CHAR) || (ahead.chr == FOE_CHAR))
      return ;
  }
  if (ahead.chr == PLAYER_CHAR)
    defeat(game);
	if (foe->standing_on_exit && foe->standing_on_exit--)
		game->map->layout[foe->pos.y][foe->pos.x] = EXIT_CHAR;
	else if (foe->standing_on_collectible && foe->standing_on_collectible--)
		game->map->layout[foe->pos.y][foe->pos.x] = COLLECTIBLE_CHAR;
  else
		game->map->layout[foe->pos.y][foe->pos.x] = EMPTY_CHAR;
  if (ahead.chr == COLLECTIBLE_CHAR)
    foe->standing_on_collectible = true;
  if (ahead.chr == EXIT_CHAR)
    foe->standing_on_exit = true;
  update_foe_pos(foe, game->images.foe, ahead.pos);
  game->map->layout[ahead.pos.y][ahead.pos.x] = FOE_CHAR;
  foe->pos = ahead.pos;
}

static void play_foe(t_game *game, t_foe *foe, t_pos player, t_offset offset)
{
  t_offset distance; 
  if (foe->pending && foe->pending--)
    return ;
  if (foe->img_i < 0)
  {
    if (game->map->layout[foe->pos.y][foe->pos.x] != EMPTY_CHAR)
      return ;
    foe->img_i = mlx_image_to_window(game->mlx, game->images.foe,
      foe->pos.x * BPP + offset.x, foe->pos.y * BPP + offset.y);
    if (foe->img_i < 0)
      return ((void)!perr("MLX foe drawing error\n"));
    game->map->layout[foe->pos.y][foe->pos.x] = FOE_CHAR;
    return ;
  }
  if (!game->images.foe->instances[foe->img_i].enabled)
    return ;
  distance = (t_offset){
    .x = ((int)player.x - foe->pos.x), .y = ((int)player.y - foe->pos.y)};
  if (distance.y && (abs(distance.y) < abs(distance.x))) 
    move_foe(game, foe, direction_by_offset((t_offset){.x = 0, .y = distance.y}
    ), direction_by_offset((t_offset){.x = distance.x, .y = 0}));
  else
    move_foe(game, foe, direction_by_offset((t_offset){.x = distance.x, .y = 0}
    ), direction_by_offset((t_offset){.x = 0, .y = distance.y}));
}

bool  play_foes(t_game *game)
{
  t_pos player_pos;
  t_foe *foe;
  t_offset offset;

  foe = game->foes;
  offset = (t_offset){.x = game->images.wall->instances->x,
  .y = game->images.wall->instances->y};
  init_player_pos(game, &player_pos);
  while (foe)
  {
    play_foe(game, foe, player_pos, offset);
    foe = foe->next;
  }
  return (1);
}
