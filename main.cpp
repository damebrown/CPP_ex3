    //
// Created by daniel.brown1 on 9/16/18.
//

#include <iostream>
#include "my_set.h"

int main()
{
    auto set1 = new my_set<int>();
    int arr[10] = {-7, -1, 13, -1, 4, 19, -4, 20, 1000, 20};
    for (int i : arr)
    {
        set1->insert(i);
        cout <<":\n\tparent: "<< p.first._ptr->getParent()->getData();
        std::cout<<"node number "<<i;
        if (i == arr[0])
        {
            std::cout<<"set1 root: "<<set1->_root.get()->getData()<<"\n";
        }
        std::cout<<"set1 size: "<<set1->size()<<"\n";
    }
    set1->insert(-1);
    std::cout<<"set1 root: "<<set1->_root.get()->getData()<<"\n";
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(1);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(0);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(-2);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(2);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(-3);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(3);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(-4);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(4);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->insert(2);
    std::cout<<"set1 size: "<<set1->size()<<"\n";
    set1->clear();
    set1->empty() ? std::cout<< "set is empty" :std::cout<< "set is not empty";

}