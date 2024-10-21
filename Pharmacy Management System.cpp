#include<iostream>
#include<fstream> //used for file handling
#include<cstring> //used for string related functions

using namespace std;

class earn //For storing the data of total earnings
{
        public:
        double profit;
        void show()     //Function for displaying the data
	{
            ifstream x("sales.txt"); //Opens a file for reading the earnings
            if(!x)
            cout<<"EARNINGS = 0 \n";
            else
            {
                x>>profit;
                cout<<"\nTOTAL EARNINGS PER YEAR:  "<<profit<<endl; //It will display the total earnings in sales.txt file
                x.close();
            }
        }
};
class product:public virtual earn   //Inherited virtually from class earn
{
        public:
           int quan;
           char name[20];
           char id[20];
           double percost;
           double persell;
           double cost;
           double sell;
	   
           void cal() //function for calculating the total cost price, total sell price and profit of a whole year
      	   {	
	        cost=percost*quan;
        	sell=persell*quan;
                profit=profit +(sell-cost)*365;
	   }
           void file() //function for displaying a file of data of each and every medicine
           {
               char file[20];
               strcpy(file,name);
               strcat(file,".txt");
               ofstream f(file);
               f<< "\nMedicine name: "<<name;
               f<<"\nMedicine id: "<<id;
               f<<"\ncost price of medicine: "<<percost;
               f<<"\nselling price of medicine: "<<persell;
               f<<"\nquantity: "<<quan;
               f<<"\ntotal cost: "<<cost;
               f<<"\nsell: "<<sell;
               f.close();   
           }
           void get() //function for reading the medicine data and creating a file for it
           {
                int s;
                cout<<"\nnumber of medicines to add\n";
                cin>>s;
                for(int i=0;i<s;i++)
                {
                    cout<<"\nEnter medicine name: \n";
                    cin>>name;
                    cout<<"\nEnter medicine id: \n";
                    cin>>id;
                    cout<<"\nEnter cost price of medicine: \n";
                    cin>>percost;
                    cout<<"\nEnter selling price of medicine: \n";
                    cin>>persell;
                    cout<<"\nEnter the total medicine quantity: \n";
                    cin>>quan;
                    cal();  //calling cal function
                    file(); //calling file function
                }
 
            }
};

class amount:public product  //Inherited from class product
{
    public:
    void add()  //function for adding medicine
    {
	    int ch;
	    while(1)
	    {
		    cout<<"1.)Input for Medicine\n2.)Exit\n";
		    cout<<"Enter choice\n";
		    cin>>ch;
		    if(ch==1)
                    {
		        get();
			ofstream x("sales.txt");
 			x<<profit;
 			x.close();
		    }
		    else if(ch==2)
			break;
		    else
			cout<<"Invaid Option. Please re-enter\n";
	    }
    }
    void update_item()  //function for updating the items in stock
    {
        {
            char name[20];
	    int id;
            cout<<"\nEnter medicine name to modify\n";
            cin>>name;
            char file[20];
            strcpy(file,name);
            strcat(file,".txt");
            fstream fout(file, ios::in|ios::out);
            if(!fout)
            {
    	        cout<<"file couldn't be opened. medicine name not found. \n";
	    }
	    else 
            {
	        cout<<"file found! \n";
                cout<<"\nupdate medicine name: \n";
  	        cin>>name;
                strcpy(file,name);
                strcat(file,".txt");
                ofstream f(file);
 	        cout<<"\nupdate cost of medicine: \n";
  	        cin>>percost;
 	        cout<<"\nupdate persell of medicine: \n";
  	        cin>>persell;
 	        cout<<"\nupdate total medicine quantity: \n";
 	        cin>>quan;
                cost=percost*quan;
                sell=persell*quan;
	        profit=profit +(sell-cost)*365;
  	        fout<<"\nmedicine name: "<<name<< "\nmedicine id: "<<id<<"\npercost of medicine: " <<percost<<"\nper sell of medicine: "<<persell<<"\nquantity: "<<quan<<"\n total cost: "<<cost<<"\nsell: "<<sell;
	        fout.close();
            }
        }
    }
};	
class order:public product  //Inherited from class product
{
    public: 
    void sell()  //function to accept orders from the user
    {
        char name[20];
        int q;
        cout<<"\nEnter medicine name\n";
        cin>>name;
        char file[20];
        strcpy(file,name);
        strcat(file,".txt");
        fstream fout(file, ios::in|ios::out);
        if(!fout)
        {
    	    cout<<"The medicine is not available. \n";
	}
        else
        {
            cout<<"The medicine is available. \n";
            cout<<"\nEnter the quantity: ";
            cin>>q;
            if(q>quan)
            {
                cout<<"\nNOT ENOUGH STOCK!!!";
            }
            else
            {
                cout<<"\nOrder successfully placed!";
                fout<<"\nMedicine name: "<<name<<endl;
                cout<<"\nQuantity: "<<q<<endl;
                cout<<"Total amount: "<<persell*q<<endl;
            }
        } 
    }
};
void admin()  //function for displaying the main menu
{
  while(1)
  {
 	cout<<"\n\t\t\t==============================\n";
	cout<<"\n\t\t\t  WELCOME TO THE PHARMACY STORE \n";
	cout<<"\n\t\t\t==============================\n\n";
	cout<<"\n\t\t\t* * * * * * * * * * * * * * * *\n";
 	cout<<"\n\t\t\t1. Add Medicines\n\n\t\t\t2. Show profit\n\n\t\t\t3. Search Medicine Details\n\n\t\t\t4. Modify Medicine Details\n\n\t\t\t5. Sell Medicines\n\n\t\t\t6. Exit\n";
  cout<<"\n\n\t\t\tSelect your choice: ";
  int u;
  cin>>u;
    if(u==1)
    {
        amount a;  //object 'a' created 
        a.show();  //calling for function show
        a.add();   //calling for function add
    }
    else if(u==2)
    {
        amount d;  //object 'd' created
        d.show();  //calling for function show
    }
    else if(u==3)
    {  
        char name[20];
        char c;
        cout<<"\nINPUT name to search\n";
        cin>>name;
        char file[20];
        strcpy(file,name);
        strcat(file,".txt");
        ifstream x(file);
        if(!x)
        {
    	    cout<<"file couldn't be opened. product ID not found. \n";
	}
        while(x)
        {
            x.get(c);
            cout<<c;
        }
    x.close();
    }
    else if(u==4)
    {
	    amount u;          //object 'u' created
	    u.update_item();  //calling for function update_item
    }
    else if(u==5)
    {
        order o;         //object 'o' created
        o.sell();        //calling for function add
    }
}
}
int main()
{
    int ch;
    while(1)
    {
        cout<<"\n \t\t\t=========================\n";
        cout<<"\n\t\t\tPHARMACY MANAGEMENT SYSTEM  \n";
        cout<<"\n \t\t\t=========================\n\n";
        cout<<"\n \t\t\t* * * * * * * * * * * * ";
        cout<<"\n\t\t\t  1. ENTER SYSTEM";
        cout<<"\n\t\t\t  2. EXIT";
        cout<<"\n\t\t\t* * * * * * * * * * * *\n";
        cout<<"\n\t\t\t Enter Your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                admin();  //Admin function will be called if the user chooses 1
                break;
            case 2:
                exit(0);  //The user will exit from the system if he chooses 2
                break;
            default:
                cout<<"Enter valid choice\n";
                break;
        }
    }
    return 0;
}


