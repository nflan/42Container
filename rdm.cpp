/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:26:29 by nflan             #+#    #+#             */
/*   Updated: 2022/12/20 18:29:18 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void deleteFin(NodePtr n)
{
	NodePtr w;
	while (n != root && n->color == 0)
	{
		if (n == n->parent->left)
		{
			w = n->parent->right;
			if (w->color == 1)
			{
				w->color = 0;
				n->parent->color = 1;
				leftRotate(n->parent);
				w = n->parent->right;
			}

			if (w->left->color == 0 && w->right->color == 0)
			{
				w->color = 1;
				n = n->parent;
			}
			else
			{
				if (w->right->color == 0)
				{
					w->left->color = 0;
					w->color = 1;
					rightRotate(w);
					w = n->parent->right;
				}

				w->color = n->parent->color;
				n->parent->color = 0;
				w->right->color = 0;
				leftRotate(n->parent);
				n = root;
			}
		}
		else
		{
			w = n->parent->left;
			if (w->color == 1)
			{
				w->color = 0;
				n->parent->color = 1;
				rightRotate(n->parent);
				w = n->parent->left;
			}

			if (w->right->color == 0 && w->right->color == 0)
			{
				w->color = 1;
				n = n->parent;
			}
			else
			{
				if (w->left->color == 0)
				{
					w->right->color = 0;
					w->color = 1;
					leftRotate(w);
					w = n->parent->left;
				}

				w->color = n->parent->color;
				n->parent->color = 0;
				w->left->color = 0;
				rightRotate(n->parent);
				n = root;
			}
		}
	}
	n->color = 0;
}

