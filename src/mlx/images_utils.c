#include "../../include/so_long.h"

mlx_instance_t *image_instance_by_pos(mlx_image_t *img, t_offset offset, t_pos pos)
{
  size_t  instance_count;
  size_t  i;

  instance_count = img->count;
  i = 0;
  while (i < instance_count)
  {
    if (img->instances[i].x / BPP == offset.x + (int)pos.x
        && img->instances[i].y / BPP == offset.y + (int)pos.y)
      return (&img->instances[i]);
    i++;
  }
  perr("BUG: image_instance_by_pos not found\n");
  return (NULL);
}

static bool	offset_image_instances(mlx_image_t *img, int relative_x, int relative_y)
{
  size_t  instance_count;
  size_t  i;

  instance_count = img->count;
  i = 0;
  while (i < instance_count)
  {
    img->instances[i].x += relative_x * BPP;
    img->instances[i].y += relative_y * BPP;
    i++;
  }
  return (1);
}

bool offset_images_within_bounds(t_game *game, char direction)
{
  t_offset		offset;
  mlx_image_t		*walls;
  mlx_instance_t *player;

  walls = game->images.wall;
  player = game->images.player->instances;
  offset.y = 0
    - (direction == DOWN_CHAR && player->y > game->screen.height / 2
      && walls->instances[walls->count - 1].y >= game->screen.height)
    + (direction == UP_CHAR && player->y < game->screen.height / 2
      && walls->instances->y < 0);
  offset.x = 0
    - (direction == RIGHT_CHAR && player->x > game->screen.width / 2
      && walls->instances[walls->count - 1].x >= game->screen.width)
    + (direction == LEFT_CHAR && player->x < game->screen.width / 2
      && walls->instances->x < 0); 
  if (!offset.x && !offset.y)
    return (false);
  offset_image_instances(game->images.background, offset.x, offset.y);
  offset_image_instances(game->images.exit, offset.x, offset.y);
  offset_image_instances(game->images.wall, offset.x, offset.y);
  offset_image_instances(game->images.player, offset.x, offset.y);
  offset_image_instances(game->images.collectible, offset.x, offset.y);
  offset_image_instances(game->images.foe, offset.x, offset.y);
  return (1);
}

t_offset calc_offset(t_game *game)
{
	t_offset			offset;
	t_pos		player;

	offset = (t_offset){.x = 0, .y = 0};
	if ((size_t)game->screen.width > game->map->width * BPP)
		offset.x = (game->screen.width / BPP / 2) - (game->map->width / 2);	
	if ((size_t)game->screen.height > game->map->lines * BPP)
		offset.y = (game->screen.height / BPP / 2) - (game->map->lines / 2);
	if (offset.x && offset.y)
		return (offset);
	if (game->images.player->instances)
		update_pos(&player, (size_t)game->images.player->instances->x / BPP,
			(size_t)game->images.player->instances->y / BPP);
	else
		init_player_pos(game, &player);
	if (!offset.x)
		offset.x = clamp((0 - game->map->width + (game->screen.width / BPP)),
				(0 - player.x + (game->screen.width / BPP / 2)), 0);
	if (!offset.y)
		offset.y = clamp((0 - game->map->lines + (game->screen.height / BPP)),
				(0 - player.y + (game->screen.height / BPP / 2)), 0);
	return (offset);
}

void update_foe_pos(t_foe *foe, mlx_image_t *foe_img, t_pos dest)
{
  t_offset distance;

  distance = (t_offset){.x = (int)dest.x - foe->pos.x, .y = (int)dest.y - foe->pos.y};
  if (!distance.x && !distance.y)
    return ;
  if (distance.y)
  {
    foe_img->instances[foe->img_i].y += (int32_t)(distance.y * BPP);
    foe->pos.x = dest.x;
  }
  else
  {
    foe_img->instances[foe->img_i].x += (int32_t)(distance.x * BPP); 
    foe->pos.y = dest.y;
  }
}