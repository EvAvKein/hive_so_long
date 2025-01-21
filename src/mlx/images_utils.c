#include "../../include/so_long.h"

mlx_instance_t *image_instance_by_pos(mlx_instance_t *first_wall, mlx_image_t *img, t_pos pos)
{
  t_offset  offset;
  size_t  instance_count;
  size_t  i;

  offset.x = first_wall->x / BPP;
  offset.y = first_wall->y / BPP;
  instance_count = img->count;
  i = 0;
  while (i < instance_count)
  {
    if (img->instances[i].x / BPP == offset.x + (int)pos.x
        && img->instances[i].y / BPP == offset.y + (int)pos.y)
      return (&img->instances[i]);
    i++;
  }
  perr("image_instance_by_pos not found\n");
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
  return (1);
}
