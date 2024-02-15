using namespace std;
void Display_all_books(Book *b,int n)
{

    cout<<"\n\n "<<"ID "<<"  "<<setw(25)<<left<<"Name"<<"  "<<"Total Qty"<<"  "<<"Available Qty"<<"  "<<"Available Book Nos"<<setw(22)<<""<<"Scrapped Book nos.\n\n";
    for(int i=0;i<n;i++)
    {
        cout<<" "<<b[i].Get_Id()<<"  ";
        cout<<setw(25)<<left<<b[i].Get_Name()<<"  ";
        cout<<"   "<<setw(6)<<left<<b[i].Get_T_Qty()<<"  "; //return total quantity
        cout<<"     "<<setw(8)<<left<<b[i].Get_A_Qty()<<"  ";//returns availaible quantity

        //Display available book numbers
        //b[i].Display_book_nos();

        int k,answer,q=b[i].Get_T_Qty();
        for(k=0;k<q;k++)
        {
            answer = b[i].Get_Availablity(k);

            if(answer==1)
                cout<<k<<",";
            if(k%10==0&&k!=0)
            {
                cout<<"\n";
                cout<<setw(44+15)<<"";
            }
        }
        k--;
        int flag=0;
        while(k%10!=0)
        {cout<<"   ";k++; flag=1;}
        if(flag==1)
            cout<<"   ";

        cout<<setw(18)<<"";
        for(int k=0;k<q;k++)
            if(b[i].Get_Availablity(k)==-1)
                cout<<k<<",";

        cout<<"\n\n";
    }
}

void Students_with_books(Student *s,int n)
{
    Issued_Books *I;
    cout<<"\n\n "<<setw(8)<<left<<"Grno"<<"  "<<setw(25)<<left<<"Name"<<"  "<<"Book ID"<<"  "<<"Book No"<<"  "<<setw(22)<<left<<"Book Name"<<"  "<<"Date of Issuing"<<"\n\n";
    for(int i=0;i<n;i++)
    {
        I = s[i].Get_I_Books(0);
        cout<<" "<<s[i].Get_GrNo()<<"  ";
        cout<<setw(30)<<left<<s[i].GetName()<<"  ";

        cout<<"  "<<I->Get_id()<<"   ";
        cout<<"    "<<I->Get_book_no()<<"   ";
        cout<<"  "<<setw(20)<<left<<I->Get_name()<<"  ";
        cout<<"  "<<I->Get_Date();
        cout<<endl;
        for(int j=1;j<s[i].Get_no_issued_books();j++)
        {
            I = s[i].Get_I_Books(j);
            cout<<setw(35)<<" ";
            cout<<"  "<<I->Get_id()<<"   ";
            cout<<"    "<<I->Get_book_no()<<"";
            cout<<"  "<<setw(20)<<left<<I->Get_name()<<"  ";
            cout<<""<<I->Get_Date();
            cout<<endl;
        }
        cout<<"\n\n";

    }

}

void Display(Book *B,int n_books,Student *S,int n_stu)
{
    cout<< "  1 : Display all Books\n";
    cout<< "  2 : Display Students with Books\n";
    int choice;
    cout<< "\n Enter your choice : ";
    cin>>choice;

    switch(choice)
    {
        case 1: Display_all_books(B,n_books);
                break;
        case 2: Students_with_books(S,n_stu);
                break;
        default: cout<<"\nInvalid choice.\n";
    }
}


