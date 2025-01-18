#include "../../include/so_long.h"

mlx_instance_t * image_instance_by_pos(mlx_image_t *img, t_pos pos)
{
  size_t  instance_count;
  size_t  i;

  instance_count = img->count;
  i = 0;
  while (i < instance_count)
  {
    if (img->instances[i].x / BPP == (int)pos.x
        && img->instances[i].y / BPP == (int)pos.y)
      return (&img->instances[i]);
    i++;
  }
  return (NULL);
}

bool  move_image_by_direction(mlx_image_t *img, char direction)
{
  if (direction == UP_CHAR)
    img->instances[0].y -= BPP;
  else if (direction == DOWN_CHAR)
    img->instances[0].y += BPP;
  else if (direction == LEFT_CHAR)
    img->instances[0].x -= BPP;
  else if (direction == RIGHT_CHAR)
    img->instances[0].x += BPP;
  return (1);
}

static bool	offset_image_instances(mlx_image_t *img, int relative_x, int relative_y)
{
  size_t  instance_count;
  size_t  i;

  instance_count = img->count;
  i = 0;
  while (i < instance_count)
  {
    img->instances[i].x += relative_x;
    img->instances[i].y += relative_y;
    i++;
  }
  return (1);
}

bool offset_images_within_bounds(t_game *game, char direction)
{
  t_offset		offset;
  mlx_image_t		*walls;

  walls = game->images.wall;
  offset = (t_offset){0, 0};
  if (direction == UP_CHAR
      && walls->instances[walls->count - 1].y < (int)(game->map->lines * BPP - BPP))
    offset.y += BPP;
  else if (direction == DOWN_CHAR && walls->instances[0].y < 0)
    offset.y -= BPP;
  else if (direction == LEFT_CHAR
      && walls->instances[walls->count - 1].x < (int)(game->map->width * BPP - BPP))
    offset.x += BPP;
  else if (direction == RIGHT_CHAR && walls->instances[0].x < 0)
    offset.x -= BPP;
  if (offset.x || offset.y)
  {
    offset_image_instances(game->images.background, offset.x, offset.y);
    offset_image_instances(game->images.exit, offset.x, offset.y);
    offset_image_instances(game->images.wall, offset.x, offset.y);
    offset_image_instances(game->images.player, offset.x, offset.y);
    offset_image_instances(game->images.collectible, offset.x, offset.y);
  }
  return (1);
}