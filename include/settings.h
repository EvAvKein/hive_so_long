

#ifndef SETTINGS_H
# define SETTINGS_H

# define WINDOW_TITLE		"so_long"
# define WINDOW_SCALE		2

# define BASE_WIDTH			640 // Scales well to a lot of screen sizes!
# define BASE_HEIGHT		360 // Scales well to a lot of screen sizes!
# define INIT_WIDTH			BASE_WIDTH * WINDOW_SCALE
# define INIT_HEIGHT		BASE_HEIGHT * WINDOW_SCALE

# define BPP				40

# define EMPTY_CHAR			'0'
# define WALL_CHAR			'1'
# define COLLECTIBLE_CHAR	'C'
# define EXIT_CHAR			'E'
# define PLAYER_CHAR		'P'

# define UP_CHAR			'U'
# define DOWN_CHAR			'D'
# define LEFT_CHAR			'L'
# define RIGHT_CHAR			'R'

# define NAVIGATED_CHAR		'-'
# ifndef VISUALIZE
#  define VISUALIZE 0
# endif

# define LAYOUT_MALLOC_CHUNK 512

#endif