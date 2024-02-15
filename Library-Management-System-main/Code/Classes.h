using namespace std;
class Date
{
    int d;
    int m;
    int y;

public:
    void Set_Date(int day,int month,int year)
    {
        d = day;
        m = month;
        y = year;
    }

    string Get_Date()
    {return to_string(d) + "/" + to_string(m) + "/" + to_string(y);}

    int Get_D() {return d;}
    int Get_M() {return m;}
    int Get_Y() {return y;}
};

class Issued_Books
{
    int id;
    int book_no;
    string name;
    Date doi;

public:

    void Copy (Issued_Books *I)
    {
        id = I->Get_id();
        book_no = I->Get_book_no();
        name = I->Get_name();
        doi.Set_Date(I->doi.Get_D(),I->doi.Get_M(),I->doi.Get_Y());
    }


    int  Get_id()        {return id;}
    void Set_id(int i)   {id = i;}

    int  Get_book_no()       {return book_no;}
    void Set_book_no(int i)  {book_no = i;}

    string Get_name()          {return name;}
    void   Set_name (string s) {name = s;}

    string Get_Date(){return doi.Get_Date();}
    void   Set_Date(int dd,int mm,int yyyy){ doi.Set_Date(dd,mm,yyyy);}
};

class Book
{
    static int book_id;
    int Id;
    string Name;
    int T_Qty;            //Total Quantity
    int A_Qty;            //Available Quantity
    int *Availablity;     // Each book is unique, though identical,
                          //Availablity is set in Set_Details_of_book() function

public :

    Book()
    { Id=book_id;
      book_id++; }   ///  constructor


    void Set_Id(int i)   {Id = i;}
    int  Get_Id()         {return Id;}

    void   Set_Name(string n)    {Name = n;}
    string Get_Name()          {return Name;}

    void Set_T_Qty(int i)  {T_Qty = i;}
    int  Get_T_Qty()       {return T_Qty;}

    void Set_A_Qty(int i)  {A_Qty = i;}
    int  Get_A_Qty()        {return A_Qty;}

    void Inc_A_Qty() {A_Qty++;}/// If Book is received, A_Qty ++
    void Dec_A_Qty()  {A_Qty--;}///If Book is issued, A_Qty --


    void Allocate_Availablity(){Availablity = new int[T_Qty];}
    int  Get_Availablity(int index) {return Availablity[index];}

    void Assign_Availablity(int index,int value){Availablity[index] = value;}

    void free_Availablity() {delete Availablity;}

    void Display_book_nos()
    {

        int k;
        for(k=0;k<Get_T_Qty();k++)
        {
            if(Get_Availablity(k)==1)
                cout<<k<<",";
            if(k%10==0&&k!=0)
            {
                cout<<"\n";
                cout<<setw(32)<<"";
            }
        }
        k--;
        int flag=0;
        while(k%10!=0)
        {cout<<"   ";k++; flag=1;}
        if(flag==1)
            cout<<"   ";

        cout<<endl;
    }



};
int Book::book_id = 100;



class Student
{

    int GrNo;
    string Name;
    Issued_Books *I_Books;
    int no_issued_books;
    //string email;
public:

    int Get_GrNo()        {return GrNo;}
    void Set_GrNo(int no) {GrNo = no;}

    string GetName()       {return Name;}
    void Set_Name(string s){Name = s;}

    int Get_no_issued_books()       {return no_issued_books;}
    void Set_no_issued_books(int i) {no_issued_books = i;}


    void Allocate_I_Books()        {I_Books = new Issued_Books[5];}

    void free_I_Books()            {delete I_Books;}

    Issued_Books* Get_I_Books(int index) {return &I_Books[index];}


    int Verifying_Id(int x) //x refers to id passed for verifying
    {
        for(int j=0;j<no_issued_books;j++)// checks if book is already issued.
        {
            if(x==I_Books[j].Get_id())
                return -1;
        }
        return 1;
    }


  /*  void Set_email(string s) { email = s;}
    string Get_email()       {return email;}*/

};
