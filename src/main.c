/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 08:29:22 by sreinhol          #+#    #+#             */
/*   Updated: 2023/07/22 17:13:33 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	ft_getcols(t_data *data, t_check *check)
{
	char	c;
	int		i;

	i = 0;
	while (check->str[i] != '\0')
	{
		c = check->str[i];
		if (c != '1' && c != '0'
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W'
			&& c != '\n' && c != '\0' && c != ' ')
			error_free("Bad map formatting.", check->str);
		i++;
	}
	if (!(ft_strchr(check->str, '1')) && (!(ft_strchr(check->str, '0'))))
		error_free("Bad map formatting.", check->str);
	if (i > data->map.line_length)
		data->map.line_length = i;
	if (ft_strcmp(check->str, "\n"))
		data->map.map_row++;
	check->map_started = true;
	return (1);
}

static bool	check_map_info(t_data *data)
{
	if (data->map.no != NULL && data->map.so != NULL
		&& data->map.we != NULL && data->map.ea != NULL
		&& data->map.floor_color != NULL && data->map.ceiling_color != NULL)
	{
		return (false);
	}
	else
		return (true);
}

int	get_input(t_data *data, char *input)
{
	t_check	check;

	init_map_and_check(data, &check, input); //  data ve check verileri varsayılan değerlerle başlatılır ve harita dosyası kontrol edilir.
	while (check.str) // satırlar tek tek dönüyor
	{
		while ((check_map_info(data))) // NO,WE,SO... verilerin null olup olmadığını kontrol ediyor eğer bunlar dolu ise hata döner
			get_identifiers(data, &check);
		while (!ft_strcmp(check.str, "\n") && check.map_started == false)
			gnl(&check.str, check.fd, false, &check);
		ft_getcols(data, &check); // harita içinde tanımla harfler dışında bir şey varsa hata basar (10 dışında sayılar harfler gbi.)
		if (check.identifiers != 6)
			error_free3("Invalid input.", data);
		gnl(&check.str, check.fd, true, &check);
	}
	free(check.str);
	close(check.fd);
	fill_map(data, input, &check);
	check_map(data, &check);
	return (SUCCESS);
}

/*void *check_sound(void *d)
{
	(void)d;
	system("afplay ./sound/askinolayim.mp3");
	return NULL;
}
*/


int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv) == FAILED)	// genel argüman ve map kontrolleri
		return (FAILED);
	init_data(&data);	// data yapısnın içindeki değerleri temizlemek sıfırlamak için kullandık.
	if (get_input(&data, argv[1]) == FAILED)	// harita kontrollerini yaptı ve verileri değişkenlere atadık.
		return (FAILED);
	data.mlx_ptr = mlx_init();//Bu kod, data yapısının mlx_ptr üyesine bu işaretçiyi atayarak, ilgili veri yapısının grafik bağdaştırıcısıyla etkileşim kurabilmesini sağlar. Bu sayede, grafik işlemleri ve pencere yönetimi için mlx_ptr üyesi kullanılabilir.
	init_player_map(&data); // oyuncunun başlangıç ayarlarını belirler (görüş açısı vs.)
	data.win_ptr = mlx_new_window(data.mlx_ptr, S_WIDTH, S_HEIGHT, "cub3d");
	data.img[0].img = mlx_new_image(data.mlx_ptr, S_WIDTH, S_HEIGHT); 
	data.img[0].addr = (int *)mlx_get_data_addr(data.img[0].img, // değişkenleri mlx struckına kaydediyor ki mlx ulaşmak istediğinde hepsine erişebilsin
			&data.img[0].bpp, &data.img[0].sl, &data.img[0].endian); // mlx_get_data_addr fonksiyonu, MiniLibX kütüphanesindeki bir fonksiyondur. Bu fonksiyon, oluşturulan bir görüntünün veri adresini, bit derinliğini (bit per piksel), satır boyutunu ve bayt sıralamasını almak için kullanılır.
	//mlx_mouse_hide();
	
	
	//if(!ft_strcmp(argv[1],"maps/gs.cub"))
    //	pthread_create(&data.t, NULL, &check_sound, NULL);
	
	mlx_hook(data.win_ptr, X_KEY_PRESS, (1L << 0), &key_dir_on, &data);
	mlx_loop_hook(data.mlx_ptr, &main_loop, &data);
	mlx_hook(data.win_ptr, 03, 0, &key_dir_off, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
