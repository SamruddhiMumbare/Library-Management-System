#include <algorithm>
#include <string.h>
#include <iostream>
#include <iomanip>
#include<stdlib.h>
#include <fstream>
#include <conio.h>
#include "Classes.h"
#include "DisplayFunctions.h"

using namespace std;

int Check_Availablity(Book *,int id,int n_books);

int Menu()
{
    cout<<  "\n***********LIBRARY MANAGEMENT SYSTEM*************\n";
    int choice;
    cout << "\n                              MENU\n\n";
    cout << "  0  : exit\n";
    cout << "  1  : Issue a book\n";
    cout << "  2  : Receive a book\n";
    cout << "  3  : Display \n";
    cout << "  4  : Modify \n";

    cout << "  5  : Add new books to library\n";
    cout << "  6  : Delete book from library (SCRAP)\n";
    cout << "  7  : Save the file\n";
    cout << "  8  : Retrieve from file\n";

    cout<<  "*********************************************************************";
    cout << "\n\n  Enter your choice: ";
    cin  >> choice;
    cout<<endl;
    return choice;
}

int Add_new_books_to_library(Book* B,int n)
{
    // Increase qty of available books ?????????

    int choice=1;
    string name;
    int qty;
    while(choice==1)
    {
        fflush(stdin);
        cout<<"  Enter Book Name  : ";
        getline(cin,name);
        cout<<"  Enter Quantity   : ";
        cin>>qty;

        if(qty > 0)
        {
            B[n].Set_Name(name); //all present in classes.h in book class
            B[n].Set_A_Qty(qty);
            B[n].Set_T_Qty(qty);
            B[n].Allocate_Availablity();

           for(int i=0;i<qty;i++)
            {
                B[n].Assign_Availablity(i,1);
            }

           n++;
        }
        else
            cout<<"\nInvalid Quantity.\n";

        cout<<"\n  Press 1 to add more books, 0 to stop adding: ";
        cin>>choice;
        cout<<endl;
    }
    if(choice!=0)
        cout<<"  Invalid Choice.\n";


    return n;
}

int Issue_a_book(Student* S,Book * B,int n_books,int n_students)
{
    int grno,i,B_index,bno;
    cout<<"  Enter your grno : ";
    cin>>grno;

    //Check if student is in database
    for(i=0;i<n_students;i++)
        if(grno==S[i].Get_GrNo())
            break;          // i will be index of that student if he is in database as we are breaking the loop



     if(i<n_students)       ///In database
     {
        if(S[i].Get_no_issued_books() >= 5)
            cout<<"\nMore Books cannot be issued to you.\n";

        else
        {
            int id,flag;
            cout<<"  Enter book id   : ";
            cin>>id;

            flag = S[i].Verifying_Id(id);
            if(flag==-1)        //-1 will be returned if he already has that ids book
                cout<<"\nYou already have this Id's Book.\n";

            else
            {
                B_index = Check_Availablity(B,id,n_books);

                if(B_index==-1)
                    cout<<"\n  Book Not Available Currently\n";
                else
                {
                    cout<<"  Displaying available book nos : ";
                    B[B_index].Display_book_nos();

                    char choice;
                    cout<<"\n  Do you want the book [y/n]: ";//I am asking this because books will be shown to him, he will check the condition of book and then decide whether to take or not
                    cin>>choice;

                    if(choice=='y' || choice=='Y')
                    {

                        int no_i_book = S[i].Get_no_issued_books();
                        Issued_Books *I = S[i].Get_I_Books(no_i_book);
                        int dd,mm,yyyy;
                      //  string email;
                        I->Set_id(id);
                        cout<<"  Enter book no : ";
                        cin>>bno;
                        I->Set_book_no(bno);
                        I->Set_name( B[B_index].Get_Name());
                        /*cout << "  Enter email id :  ";
                        cin  >> email;
                        S[i].Set_email(email);*/
                        cout<<"  Enter date of issueing :  ";
                        scanf("%d/%d/%d",&dd,&mm,&yyyy);
                        I->Set_Date(dd,mm,yyyy);

                       S[i].Set_no_issued_books( no_i_book+1);
                       B[B_index].Assign_Availablity(bno,0);
                       B[B_index].Dec_A_Qty();
                    }

                }
            }
        }
     }

     else                   ///New student
     {
        int id,flag;
        cout<<"  Enter book id : ";

        cin>>id;
        B_index = Check_Availablity(B,id,n_books);
        if(B_index!=-1)
        {
            cout<<"  Displaying available book nos : ";
            B[B_index].Display_book_nos();
            char choice;
            cout<<"  Do you want the book [y/n]: ";//I am asking this because books will be shown to him, he will check the condition of book and then decide whether to take or not
            cin>>choice;
            if(choice=='y' || choice=='Y')
            {

                int dd,mm,yyyy;
                string temp_name;
               // string email;
                S[i].Set_GrNo(grno);

               // cout<<"==============";
                S[i].Allocate_I_Books();
                Issued_Books *I = S[i].Get_I_Books(0);
                I->Set_id(id);
                cout<<"  Enter book no : ";
                cin>>bno;

                cout<<"\n  Enter name of student : ";
                fflush(stdin);
                getline(cin,temp_name);      //Inputting student's Name
                S[i].Set_Name(temp_name);

                I->Set_book_no(bno);
                I->Set_name( B[B_index].Get_Name());

                /*cout << "  Enter email id :  ";
                cin  >> email;
                S[i].Set_email(email);*/

                cout<<"  Enter date of issueing :  ";
                scanf("%d/%d/%d",&dd,&mm,&yyyy);
                I->Set_Date(dd,mm,yyyy);

                S[i].Set_no_issued_books(1);
                B[B_index].Assign_Availablity(bno,0);
                B[B_index].Dec_A_Qty();

                n_students++;
            }
            else
                cout<<"\n  You chose not to issue book.\n";

        }
        else
            cout<<"\nBook Not Available Currently\n";
     }
    return n_students;
}

int Check_Availablity(Book *B,int id,int n_books)
{
    ///This function will return index of book in our array
    for(int i=0;i<n_books;i++)
        if(id==B[i].Get_Id())
        {
            if(B[i].Get_A_Qty()>0)
                return i;
            else
                return -1;
        }

    return -1;
}

int Receive_a_book(Student * S, Book * B,int n_students, int n_books)
{


    int grno,i,id,k;
   cout<<"  Enter Your GrNo : ";
   cin>>grno;

   for(i=0;i<n_students;i++)
      if(S[i].Get_GrNo()==grno)
         break;

    if(i<n_students)
    {
        int flag=0,bno;
        int no_i_books = S[i].Get_no_issued_books();
        if(no_i_books > 1)
        {
            cout<<"  Enter the book id you want to return : ";
            cin >>id;
        }
        else
            id = S[i].Get_I_Books(0)->Get_id();

        Issued_Books * I ;
        for( k=0;k<no_i_books;k++)
        {
            I = S[i].Get_I_Books(k);
            if(id == I->Get_id())
                {flag=1;break;}
        }

        if(flag==1)
        {
            bno = I->Get_book_no();
            S[i].Set_no_issued_books(no_i_books-1);
            S[i].Get_I_Books(k)->Copy( S[i].Get_I_Books(no_i_books-1) );


            for(k=0;k<n_books;k++)
                if(B[k].Get_Id() == id)
                {
                    B[k].Inc_A_Qty();
                    B[k].Assign_Availablity(bno,1);
                    break;
                }
            if(no_i_books==1)
                n_students--;
        }
        else
            cout<<"\nInvalid Book ID\n";

    }

    else
        cout<<"\nStudent is not in database only, how can you give a book\n";
    return n_students;



}

int Del_book_from_library(Book *B,int n_books)
{

    int id,bno,i;
    cout<<"  Enter book id & book no to be deleted\n";
    cin>>id;
    cin>>bno;

    for(i=0;i<n_books;i++)  /// i will be index of the book with id entered,
        if( id==B[i].Get_Id()   )
            break;


    if(i<n_books)
    {
        int availablity = B[i].Get_Availablity(bno);

        if(B[i].Get_T_Qty()==1 && availablity==1)
        {
           B[i] = B[n_books-1];
           return n_books-1;
        }
        else if( availablity==1 )
        {
            B[i].Assign_Availablity(bno,-1);
            B[i].Dec_A_Qty();
        }
        else if( availablity==0 )
            cout<<"\nBook is issued to someone.\n";
        else if(bno >= B[i].Get_T_Qty())
            cout<<"\nBook No "<<bno<<" book is not present\n";
        else
            cout<<"\nBook is already scrapped.\n";
    }

    else
        cout<<"\nBook is not in the database, so you cannot delete it\n";



    return n_books;


}

void Modify_student(Student *S,int n_students)
{

    int grno,i;     //i will be index of student in database
    cout<<" Enter Grno of student to modify : ";
    cin>>grno;

    for(i=0;i<n_students;i++)
        if(S[i].Get_GrNo()==grno)
            break;

   if(i<n_students)
   {

       cout<<"\n  Displaying GrNo and Name of student you want to modify :\n";
       cout<<"  "<<S[i].Get_GrNo()<<"   "<<S[i].GetName()<<endl;

       cout<<"\n  Press 1 : To modify GrNo"<<endl;
       cout<<"  Press 2 : To modify Name"<<endl;
       int choice;
       cout<<"\n  Enter your choice : ";
       cin>>choice;

       switch(choice)
       {
            case 1:
                    cout<<"Enter new GrNo : ";
                    cin>>grno;
                    S[i].Set_GrNo(grno);
                    break;
            case 2:
                    string str;
                    cout<<"Enter new Name : ";
                    fflush(stdin);
                    getline(cin,str);
                    S[i].Set_Name(str);
                    break;
       }
       cout<<"\n  Displaying Modified GrNo and Name of  student .\n";
       cout<<"  "<<S[i].Get_GrNo()<<"   "<<S[i].GetName()<<endl;

   }
   else
        cout<<"\nStudent is not in database, so you cannot modify\n";

}

void Modify_book(Book *B,int n_books)
{
    int id,i;
    cout<<"Enter book id whose details you want to modify : ";
    cin>>id;

    for(i=0;i<n_books;i++)
        if(id == B[i].Get_Id())
            break;

    if(i<n_books)
    {
        cout<<"Displaying book id and name of the book : ";
        cout<<" "<<B[i].Get_Id() <<"  "<< B[i].Get_Name()<<endl;
        char ch;
        cout<<"Do you want to modify name[y/n] : ";
        cin>>ch;

        if(ch=='y' || ch=='Y')
        {
            string n;
            cout<<"Enter new name :";
            //  ifflush(stdin);
            getline(cin,n);

            B[i].Set_Name(n);    ///This function should also change the name in the issued student************
        }

    }
    else
        cout<<"\nBook is not in database.\n";

}

void Modify(Book *B,int n_books,Student *S,int n_students)
{
    int c;
    cout<<"  1 : Modify a student \n" ;
    cout<<"  2 : Modify a book \n";
    cout<<"\n  Enter your choice : ";
    cin>>c;

    switch(c)
    {
        case 1  : Modify_student(S,n_students);
                  break;
        case 2  : Modify_book(B,n_books);
                  break;
        default : cout<<"Invalid Choice.\n";

    }
}

void SaveFiles(Student*S,Book*B,int n_students,int n_books)
{

    ///Saving No of books and students ;;;
    ofstream F_values;
    F_values.open("B & S count.txt",ios::out);
    F_values<< n_books<< " "<<n_students;
    F_values.close();


    ///Saving Book Array
    ofstream BookArray;
    BookArray.open("BookArray.txt",ios::out);

    for(int i=0;i<n_books;i++)
    {

        BookArray << B[i].Get_Id()<<"\n"
                  << B[i].Get_Name()<<"\n"
                  << B[i].Get_T_Qty()<<" "<< B[i].Get_A_Qty()
                  <<"\n";

        int Tqty = B[i].Get_T_Qty();
        for(int j=0;j < Tqty;j++)
            BookArray << B[i].Get_Availablity(j)<<" ";

        B[i].free_Availablity();

        BookArray<<"\n"<<"\n";
    }
    cout<<"BookArray written in file succesfully.\n";
    BookArray.close();


    ///Saving Student array


    ofstream StudArray;
    StudArray.open("StudentsArray.txt",ios::out);


    for(int i=0;i<n_students;i++)
    {
        StudArray << S[i].Get_GrNo()<<"\n"
                  << S[i].GetName()<<"\n"
                //  << S[i].Get_email()<<"\n"
                  << S[i].Get_no_issued_books()<<"\n";

        Issued_Books *I;
        for(int j=0; j<S[i].Get_no_issued_books();j++)
        {
            I = S[i].Get_I_Books(j);
            StudArray << I->Get_id()<<" "
                      << I->Get_book_no() << " "
                      << I->Get_Date() << "\n"
                      << I->Get_name() << "\n";
        }

        StudArray << "\n"<<"\n";
    }

    cout<<"Student Array written in file succesfully.\n";
    StudArray.close();


}

void RetrieveFiles(Student*S,Book*B,int *n_students,int *n_books)
{
    ///Retrieving No of Books and Students

    ifstream F_values;
    F_values.open("B & S count.txt",ios::in);
    F_values>> *n_books >> *n_students;
    F_values.close();

    //cout<<endl<<"S: "<<*n_students<<" B: "<<*n_books<<endl;

    ///Retrieving Books
    ifstream BookArray;
    BookArray.open("BookArray.txt",ios::in);
    BookArray.seekg(0);
    int id;
    string name;
    int T_Qty,A_Qty;

    for(int i=0;i< *n_books;i++)
    {

        BookArray >> id ;
        BookArray >> name ;
        BookArray >>  T_Qty >> A_Qty ;

        B[i].Set_Id(id);
        B[i].Set_Name(name);
        B[i].Set_T_Qty(T_Qty);
        B[i].Set_A_Qty(A_Qty);

        B[i].Allocate_Availablity();

        int availablity;
        for(int j=0;j<T_Qty;j++)
        {
            BookArray >> availablity;
            B[i].Assign_Availablity(j,availablity);
        }

    }

    cout<<"BookArray info read succesfully\n";
    BookArray.close();

    ifstream StudentArray;
    StudentArray.open("StudentsArray.txt",ios::in);
    StudentArray.seekg(0);

    int grno;
    string fname,lname;
  //  string email;
    int no_of_i_books;
    int bid,bno;
    int d,m,y;
    string bname;
    char c;
    for(int i=0;i<*n_students;i++)
    {
        StudentArray >> grno
                     >> fname >> lname
                    // >> email
                     >> no_of_i_books;

        S[i].Set_GrNo(grno);
        S[i].Set_Name(fname + " " + lname);
      //  S[i].Set_email(email);
        S[i].Set_no_issued_books(no_of_i_books);
        S[i].Allocate_I_Books();
        for(int j=0;j<no_of_i_books;j++)
        {
            StudentArray >> bid >> bno
                         >> d >> c >> m >> c >> y
                         >> bname;


            S[i].Get_I_Books(j)->Set_id(bid);
            S[i].Get_I_Books(j)->Set_book_no(bno);
            S[i].Get_I_Books(j)->Set_Date(d,m,y);
            S[i].Get_I_Books(j)->Set_name(bname);

        }

    }
    cout<<"\Student Array info read succesfully\n";
    StudentArray.close();

}

int main()
{

    Book B[50];
    Student S[50];
    int no_of_books=0;
    int no_of_students=0;
    int ans;
    while(1)
    {

        ans = Menu();
        switch(ans)
        {
            case 0 : exit(0);
            case 1 : no_of_students = Issue_a_book(S,B,no_of_books,no_of_students);
                     break;

            case 2 : no_of_students = Receive_a_book(S,B,no_of_students,no_of_books);
                     break;

            case 3 : Display(B,no_of_books,S,no_of_students);
                     break;

            case 4 : Modify(B,no_of_books,S,no_of_students);
                     break;

            case 5 : no_of_books = Add_new_books_to_library(B,no_of_books);
                     break;

            case 6 : no_of_books = Del_book_from_library(B,no_of_books);
                     break;

            case 7:  SaveFiles(S,B,no_of_students,no_of_books);
                     break;

            case 8:  RetrieveFiles(S,B,&no_of_students,&no_of_books);
                     break;

        }
    }
return 0;
}







