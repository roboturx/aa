#include <iostream>
#include <vector>

using namespace std;

void display(vector<int> &vectory)
{
    for (int i=0; i < vectory.size(); i++)
    {
        cout << vectory[i] << " - ";

    }
    cout << "\n";
}

int main()
{
    cout << "Hello world!" << endl;
    vector<int> vectory;
    cout << "vectorun ilk büyüklüğü = " << vectory.size() ;
    int x;
    cout << "enter 5 integer values";
    for (int i=0 ; i<5 ; i++)
    {
        cin >> x;
        vectory.push_back(x);

    }
    cout << "size after pushing ints = " << vectory.size() << "\n";
    cout << "current contents \n";
    display(vectory);
    vectory.push_back(6.6);
    cout << "size after pushing int 6.6 = " << vectory.size() << "\n";

    cout << "contents now ........... \n";
    display(vectory);
    vector<int>::iterator itr = vectory.begin();

    cout << "iterator no = " ;
//    cout << itr;
    itr = itr + 3;
    cout << "after itr +3 iterator no = ";
 //   cout << itr;

    vectory.insert(itr,1,9);
    cout << "\nContents after inserting: \n";
    display(vectory);

    cout << "delete 4. and 6. element";
    vectory.erase(vectory.begin()+3, vectory.begin()+5);

    cout << "\nContents after inserting: \n";
    display(vectory);
    cout << "\nEND\n";



    return 0;
}
