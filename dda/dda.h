/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 08:59:21 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 18:40:10 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

# include "../types.h"
# include <math.h>

int			is_wall(t_game *data, float px, float py);
t_params	dda(t_point p, float dir, t_game *data);

#endif
