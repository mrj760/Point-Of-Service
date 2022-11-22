#include <iostream>
#include <string>
#include <pqxx/pqxx>
using namespace std;
int main()
{
    string connection_string("host=144.37.116.173 port=5432 dbname=mydb user=namcuong757");
    pqxx::connection conn(connection_string.c_str());
    pqxx::work wrk(conn);
    pqxx::result res = wrk.exec("SELECT * FROM client");
    if(res.size() < 1)
    {
        cout << "Empty table" << endl;
    }
    cout << "Phone Number \t\t" << "Name \t\t" << "address\t\t" << "zip\t\t" << endl;
    for(int i = 0; i < res.size(); i++)
    {
        cout << res[i][0] << "\t\t" << res[i][1] << "\t\t" << res[i][2] << "\t\t" << res[i][3] << endl;
    }

    return 0;
}