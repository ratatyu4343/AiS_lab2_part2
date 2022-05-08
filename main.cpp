#include <iostream>
#include <BTree.h>

int main()
{
    double arr[] = {1, 2, 3, 4, 5};
    std::cout << "Input t: ";
    int t_int;
    std::cin >> t_int;
    BTree t(arr, 5, t_int);
    while(true)
    {
        int n;
        std::cout << "\n1 - Add\n2 - Delete\n3 - Search()\n4 - Exit()\n>>> ";
        std::cin >> n;
        if(n == 1)
        {
            double f;
            std::cout << "Input item: ";
            std::cin >> f;
            t.insert_item(f);
        }
        if(n == 2)
        {
            double f;
            std::cout << "Input item: ";
            std::cin >> f;
            t.delete_node(f);
        }
        if(n == 3)
        {
            double f;
            std::cout << "Input item: ";
            std::cin >> f;
            if(t.search_item(f).first)
                t.show_item(t.search_item(f).first);
            else
                std::cout << "Can`t find that!";
        }
        if(n == 4)
        {
            return 0;
        }
    }
}
