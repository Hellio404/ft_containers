#include "../includes/ft_tree.hpp"


namespace ft
{
     tree_node_base *tree_minimum(tree_node_base *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    tree_node_base *tree_maximum(tree_node_base *node)
    {
        while (node->right)
            node = node->right;
        return node;
    }

    bool tree_is_left_node(tree_node_base *node)
    {
        return node->parent->left == node;
    }

    bool tree_is_right_node(tree_node_base *node)
    {
        return node->parent->left != node;
    }

    tree_node_base *tree_next_node(tree_node_base *node)
    {
        if (node->right)
            return tree_minimum(node->right);
        while (tree_is_right_node(node))
            node = node->parent;
        return node->parent;
    }

    tree_node_base *tree_prev_node(tree_node_base *node)
    {
        if (node->left)
            return tree_maximum(node->left);
        while (tree_is_left_node(node))
            node = node->parent;
        return node->parent;
    }

    tree_node_base *_left_rotate(tree_node_base *a)
    {
        tree_node_base *a_parent = a->parent;
        tree_node_base *b = a->right;
        tree_node_base *b_left = b->left;

        if (tree_is_left_node(a))
            a_parent->left = b;
        else
            a_parent->right = b;

        b->parent = a_parent;
        b->left = a;
        a->parent = b;
        a->right = b_left;
        if (b_left)
            b_left->parent = a;
        return b;
    }

    tree_node_base *_right_rotate(tree_node_base *a)
    {
        tree_node_base *a_parent = a->parent;
        tree_node_base *b = a->left;
        tree_node_base *b_right = b->right;

        if (tree_is_left_node(a))
            a_parent->left = b;
        else
            a_parent->right = b;

        b->parent = a_parent;
        b->right = a;
        a->parent = b;
        a->left = b_right;
        if (b_right)
            b_right->parent = a;
        return b;
    }
}
