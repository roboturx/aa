#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int i, j;
	char str[ ] = "\nC++ is better than C 123";
	int len = strlen(str);
	char *substr = new char[len];
	cout<< "The main string is: "<<str;
	cout<<"\n\nEnter the substring to be searched: ";
	cin>>substr;
	int k;
	int len2=strlen(substr);
	for(i=0;i<len;i++)
	{
		k=i;
		for(j=0;j<len2;j++)
		{
			
			cout << "\n" << i << " - " 
			             << j << "   "
			             << "str[k] is ---  " 
			             << str[k] << "      substr[j] --- " << substr[j] ;
			if(str[k]==substr[j])
			{
				if(j==len2-1) 
				{
					cout<<"\n---------------------------------------------";
					cout<<"\nThe substring is present in the main string";
					cout<<"\n---------------------------------------------\n";
					cin.ignore(-1, '\n');
					cin.get( );
					exit(0);
				}
				k++;
			}
			else
				break;
		}
	}
	if(i==len)
	cout<<"\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	cout<<"\nThe substring is not present in the main string";
	cout<<"\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cin.get( );
}
