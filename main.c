#include <stdio.h>
#include "mlx/mlx.h"

int main(void)
{
    void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 800, "Hello world!");
	mlx_loop(mlx);

}
