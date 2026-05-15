/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 08:59:21 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/15 18:47:10 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
#define DDA_H

#include "../render/render.h"
#include "../types.h"

t_tex dda(t_point p, float dir, t_test* data);

#endif
