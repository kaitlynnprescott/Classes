import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileReader;

public class BinaryTree<E>
{
    /** Class to encapsulate a tree node. */
    private static class Node<E>
    {
        /** The information stored in this node. */
        public E data;
        /** Reference to the left child. */
        public Node<E> left;
        /** Reference to the right child. */
        public Node<E> right;

        /**
         * Construct a node with given data and no children.
         * @param data The data to store in this node
         */
        public Node(E data)
        {
            this.data = data;
            left = null;
            right = null;
        }

        /**
         * Returns a string representation of the node.
         * @return A string representation of the data fields
         */
        public String toString()
        {
            return data.toString();
        }
    }

    /** The root of the binary tree */
    private Node<E> root;

    /** Construct an empty BinaryTree */
    public BinaryTree()
    {
        root = null;
    }

    /**
     * Construct a BinaryTree with a specified root.
     * Should only be used by subclasses.
     * @param root The node that is the root of the tree.
     */
    private BinaryTree(Node<E> root)
    {
        this.root = root;
    }

    /**
     * Constructs a new binary tree with data in its root,leftTree
     * as its left subtree and rightTree as its right subtree.
     */
    public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree)
    {
        root = new Node<E>(data);
        if (leftTree != null)
        {
            root.left = leftTree.root;
        }
        else
        {
            root.left = null;
        }
        if (rightTree != null)
        {
            root.right = rightTree.root;
        }
        else
        {
            root.right = null;
        }
    }

    /**
     * Return the data field of the root
     * @return the data field of the root
     *         or null if the root is null
     */
    public E getData()
    {
        if (root != null)
        {
            return root.data;
        }
        else
        {
            return null;
        }
    }

    public String toString()
    {
        return preorderToString();
    }

    /**
     * Method to read a binary tree.
     * @pre The input consists of a preorder traversal of the binary tree. The line "null" indicates a null tree.
     * @param bR The input file
     * @return The binary tree
     * @throws IOException If there is an input error
     */
    public static BinaryTree<String> readBinaryTree(BufferedReader bR) throws IOException
    {
        // Read a line and trim leading and trailing spaces.
        String data = bR.readLine().trim();
        if (data.equals("null"))
        {
            return null;
        }
        else
        {
            BinaryTree<String> leftTree = readBinaryTree(bR);
            BinaryTree<String> rightTree = readBinaryTree(bR);
            return new BinaryTree<String>(data, leftTree, rightTree);
        }
    }

    /**
     * Method to return the preorder traversal of the binary tree
     * as a sequence of strings each separated by a space.
     * @return A preorder traversal as a string
     */
    public String preorderToString()
    {
        StringBuilder stb = new StringBuilder();
        preorderToString(stb, root);
        return stb.toString();
    }

    private void preorderToString(StringBuilder stb, Node<E> root)
    {
        // TODO: append to the string builder using the append() method
        // to generate a preorder representation of our tree.
    }

    /**
     * Method to return the postorder traversal of the binary tree
     * as a sequence of strings each separated by a space.
     * @return A postorder traversal as a string
     */
    public String postorderToString()
    {
        StringBuilder stb = new StringBuilder();
        postorderToString(stb, root);
        return stb.toString();
    }

    private void postorderToString(StringBuilder stb, Node<E> root)
    {
        // TODO: append to the string builder using the append() method
        // to generate a preorder representation of our tree.
    }

    /**
     * Method to return the inorder traversal of the binary tree
     * as a sequence of strings each separated by a space.
     * @return An inorder string representation of the tree
     */
    public String inorderToString()
    {
        StringBuilder stb = new StringBuilder();
        inorderToString(stb, root);
        return stb.toString();
    }

    private void inorderToString(StringBuilder stb, Node<E> root)
    {
        // TODO: append to the string builder using the append() method
        // to generate a preorder representation of our tree.
    }

    /**
     * Returns the height of the tree starting at root.
     * A null root starts at height -1.
     */
    public int height()
    {
        return height(root);
    }

    private int height(Node<E> root)
    {
        // TODO: come up with a recursive algorithm
        // to generate the height of a binary tree
    }

    /**
     * Returns the count of leaves in the binary tree starting at root.
     * For this method, a leaf is a non-null node that has no children.
     */
    public int leafCount()
    {
        return leafCount(root);
    }

    private int leafCount(Node<E> root)
    {
        // TODO: come up with a recursive algorithm
        // to generate the number of leaves in a binary tree
    }

    /**
     * Returns the width of the binary tree at the designated level.
     * Width is defined as the number of nodes residing at a level.
     */
    public int width(int level)
    {
        return width(root, level);
    }

    private int width(Node<E> root, int level)
    {
        // TODO: come up with a recursive algorithm
        // to generate the width of a binary tree
    }

    public static void main(String[] args)
    {
        BinaryTree<String> br1 = new BinaryTree<String>();
        try
        {
            br1 = readBinaryTree(new BufferedReader(new FileReader("ourTree.in")));
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        System.out.println("--------------TESTING preorderToString--------------");
        System.out.println("Given   : " + br1.preorderToString());
        System.out.println("Expected: 30 15 4 20 18 19 35 32 38");

        System.out.println("--------------TESTING inorderToString--------------");
        System.out.println("Given   : " + br1.inorderToString());
        System.out.println("Expected: 4 15 18 19 20 30 32 35 38");

        System.out.println("--------------TESTING postorderToString--------------");
        System.out.println("Given   : " + br1.postorderToString());
        System.out.println("Expected: 4 19 18 20 15 32 38 35 30");

        System.out.println("--------------TESTING height--------------");
        System.out.println("Given   : The binary tree's height is " + br1.height());
        System.out.println("Expected: The binary tree's height is 4");

        System.out.println("--------------TESTING leafCount--------------");
        System.out.println("Given   : The number of leaves in the binary tree is " + br1.leafCount());
        System.out.println("Expected: The number of leaves in the binary tree is 4");

        System.out.println("--------------TESTING width--------------");
        System.out.println("Given   : The binary tree's width at level one is " + br1.width(1));
        System.out.println("Expected: The binary tree's width at level one is 2");

        System.out.println("--------------TESTING width--------------");
        System.out.println("Given   : The binary tree's width at level two is " + br1.width(2));
        System.out.println("Expected: The binary tree's width at level two is 4");
    }
}
