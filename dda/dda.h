/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 08:59:21 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/12 10:37:34 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
#define DDA_H

#include "../render/render.h"
#include "../types.h"

float dda(t_point p, float dir, t_test* data);

#endif
