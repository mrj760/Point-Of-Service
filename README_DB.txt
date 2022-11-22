Postgresql server information:
Host: 144.37.116.173
Port: 5432
username: namcuong757
password: none, but if it asks (Password1)
Database name: mydb
Compiled file: a.out

Setting up on your machine is extremely important for things to work:
1. Installing Postgresql (Make sure you can actually connect to your local server before executing anthying else)
2. Installing libpqxx (https://github.com/jtv/libpqxx), this is a API that help to connect C++ and Postgresql.
3. How to run the database.cpp: g++ -std=c++20 -I/opt/homebrew/include -L/opt/homebrew/lib database.cpp -lpqxx
-I : include path that for pqxx (change the path to fit with your machine)
-L : library path that go with lpqxx
-std=c++20: have to run in c++ 20 in order for code to work.

host: the default is CSUSM IP address. It might change depend on the change of IP address/

Value from Database will store in 2D array

Tasks need more attention: (Can delete when tasks are done)
a. Functions that include query to interact with Database such as insert, select, etc. Think about the needs of the project.
b. Display the databases in GUI. Using QTsql maybe?
c. Feel free to add
