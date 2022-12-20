/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdm2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:35:17 by nflan             #+#    #+#             */
/*   Updated: 2022/12/20 18:39:38 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void deleteNodeHelper(NodePtr node, int key) {
	NodePtr todel = TNULL;
	NodePtr x, y;

	y = todel;
	int color = y->color;
	if (todel->left == TNULL)
	{
		x = todel->right;
		rbTransplant(todel, todel->right);
	}
	else if (todel->right == TNULL)
	{
		x = todel->left;
		rbTransplant(todel, todel->left);
	}
	else
	{
		y = minimum(todel->right);
		color = y->color;
		x = y->right;
		if (y->parent == todel)
		{
			x->parent = y;
		}
		else
		{
			rbTransplant(y, y->right);
			y->right = todel->right;
			y->right->parent = y;
		}

		rbTransplant(todel, y);
		y->left = todel->left;
		y->left->parent = y;
		y->color = todel->color;
	}
	delete todel;
	if (color == 0)
	{
		deleteFix(x);
	}
}

void rbTransplant(NodePtr u, NodePtr v)
{
	if (u->parent == nullptr)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

