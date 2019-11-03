/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:17:04 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/03 19:44:14 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	events(t_ray ray, t_sdl sdl)
{
	SDL_Event event;

	while (1)
		while (SDL_PollEvent(&event))
		
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
			{
				//printf("fff\n");
				exit(0);
			}
			else if (SDLK_w == event.key.keysym.sym)
			{
				ray.orig.y -= 0.01;
				ray_tracing_init(&sdl, &ray);
				SDL_RenderPresent(sdl.render);
			}
			else if (SDLK_s == event.key.keysym.sym)
			{
				ray.orig.y += 0.01;
				ray_tracing_init(&sdl, &ray);
				SDL_RenderPresent(sdl.render);
			}
			else if (SDLK_a == event.key.keysym.sym)
			{
				ray.orig.x += 0.01;
				ray_tracing_init(&sdl, &ray);
				SDL_RenderPresent(sdl.render);
			}
			else if (SDLK_d == event.key.keysym.sym)
			{
				ray.orig.x -= 0.01;
				ray_tracing_init(&sdl, &ray);
				SDL_RenderPresent(sdl.render);
			}
}