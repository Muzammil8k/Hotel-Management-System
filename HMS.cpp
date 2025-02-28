//open console in fullscreen
//add admin.txt, customer.txt, hotel.txt in same folder
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<iomanip>
#include<sstream>
#include<vector>
using namespace std;

void static head()
{
	system("cls");
	cout << endl;
	cout << "     Malik Hotel" << string(124, ' ') << "Shaheed-e-Millat Road" << endl;
	cout << "  _________________"<< string(121, ' ') <<"Near Haider Road" << endl;
	cout << "     Rawalpindi"<< string(125, ' ') <<"Rawalpindi 4600, Pakistan" << endl;
	cout << string(140, ' ') <<"Tel: 051-54739281" << endl;
	cout << "\n\n";
}
string static space()
{
	return "\n    \t\t\t\t\t\t\t\t";
}
void static redirect()
{
	cout << space() << "Redirecting....." << endl;
	_Thrd_sleep_for(1500);
}
void first_page();

class User
{
protected:
	string password, name;
public:
	User(){}
};

class Admin : public User
{

public:
	void login();
	void admin_portal();
	void admin_options();
	void customer_options();
	void room_options();
	void cab_options();
	void food_options();
	void get_details();
	void display();
	void add_admin();
	void search_admin();
	void delete_admin();
	void record();
};

class Customer :public User
{
protected:
	string address, gender, number;
	int age, id;
public:
	Customer() { id = 1000; age = 0; }
	string get_name() { return name; }
	int get_id() { return id; }
	void get_details();
	int generate_id();
	void display();
	bool login(string n, string p);
	void add_customer();
	bool search_customer();
	void update_customer();
	void delete_customer();
	void record();
	void customer_portal1();
	void customer_portal2();
};

class Cab
{
protected:
	string name;
	float price;
public:
	Cab(string n = "", float p = 0.0) : name(n), price(p) {}
	string get_name() { return name; }
	float get_price() { return price; }
	void display();
	void add_cab();
	bool search_cab();
	void update_cab();
	void delete_cab();
	void record();
};

class Room
{
protected:
	string name;
	float price;
public:
	Room(string n = "", float p = 0.0) : name(n), price(p)  {}
	string get_name() { return name; }
	float get_price() { return price; }
	void display();
	void get_details();
	void add_room(string category);
	bool search_room(string category);
	void update_room(string category);
	void delete_room(string category);
	void record();
};

class Food
{
protected:
	string name, category;
	float price;
	int id;
public:
	
	Food(int i=0, string c = "", string n = "", float p = 0.0) : id(i), category(c), name(n),  price(p) {}
	int get_id() { return id; }
	string get_category() { return category; }
	string get_name() { return name; }
	float get_price() { return price; }
	void display();
	int generate_id();
	void get_details();
	void add_food();
	bool search_food();
	void update_food();
	void delete_food();
	void record();
};

class Hotel 
{
protected:
	vector<Room> room_package, room_type;
	vector<Cab> cab;
	vector<Food> food;
	vector<string> selected_food;
	vector<float> selected_food_price;
	float room_cost,cab_cost,food_cost;

public:
	Hotel():room_cost(0), cab_cost(0), food_cost(0){}
	void load_file();
	int choose_option(vector<Room> vec);
	void book_room();
	void book_cab();
	void book_food();
	float get_room_cost()  { return room_cost; }
	float get_cab_cost()  { return cab_cost; }
	float get_food_cost()  { return food_cost; }
};

class Bill
{
	float room_cost, cab_cost, food_cost;
	float subtotal, total;
	float tax, tax_rate;
	float service_fee, service_rate;
public:
	Bill(Hotel h);
	void show_bill(Customer c);
};

int main()
{
	system("color E4");
	first_page();
}

//Admin Functions
void Admin::login()
{
	string n, p;
	bool found = false;
	ifstream read("admin.txt");

	head();
	cout << space() << "Enter name: ";
	cin.ignore();
	getline(cin, n);
	cout << space() << "Enter password: ";
	cin >> p;

	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured opening admin.txt" << endl;
		redirect();
		return first_page();
	}

	while (getline(read, name, '|'))
	{
		getline(read, password);
		if (name == n && password == p)
		{
			found = true;
			break;
		}
	}

	read.close();

	if (found)
		admin_portal();
	else
	{
		head();
		cout<<space() << "\aWrong username or password" << endl;
		redirect();
		return first_page();
	}
}
void Admin::get_details()
{
	cout << space() << "Enter name: ";
	cin.ignore();
	getline(cin, name);
	cout << space() << "Enter password: ";
	cin >> password;
}
void Admin::display()
{
	cout << space() << "Name: " << name << endl;
	cout << space() << "Password: " << password << endl << endl;
}

void Admin::add_admin()
{
	ofstream write("admin.txt", ios::app);
	head();
	get_details();

	if (write.fail())
	{
		head();
		cout << space() << "\aAn error ocured opening admin.txt" << endl;
		redirect();
		return;
	}
	
	write << name << "|" << password << endl;
	write.close();

	head();
	cout << space() << "Account created successfully" << endl;
	redirect();
}
void Admin::search_admin()
{
	string n;
	char ch;
	bool found = false;
	ifstream read("admin.txt");

	head();
	cout << space() << "Enter name to search: ";
	cin.ignore();
	getline(cin, n);

	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured opening admin.txt " << endl;
		redirect();
		return;
	}

	while (getline(read, name, '|'))
	{
		getline(read, password);
		if (name == n)
		{
			found = true;
			break;
		}
	}
	read.close();
	if (found)
	{
		head();
		cout << space() << "Admin Found" << endl;
		display();
		_Thrd_sleep_for(1500);
		cout << "\nEnter any letter to return to admin options: ";
		cin >> ch;
		return;
	}
	head();
	cout << space() << "\aAdmin not found" << endl;
	redirect();
}
void Admin::delete_admin()
{
	string n, p;
	bool found = false;
	fstream file1("admin.txt"), file2("admin2.txt", ios::app);
	
	if (file1.fail() || file2.fail())
	{
		head();
		cout << space() << "\aFile could not be opened" << endl;
		redirect();
		return;
	}

	head();
	cout << space() << "Enter details of admin to delete" << endl;
	cout << space() << "Enter name: ";
	cin.ignore();
	getline(cin, n);
	cout << space() << "Enter password: ";
	cin >> p;

	while (getline(file1, name, '|'))
	{
		getline(file1, password);
		if (name == n && password == p)
			found = true;
		else
			file2 << name << "|" << password << endl ;
	}
	file1.close();
	file2.close();
	remove("admin.txt");
	rename("admin2.txt", "admin.txt");

	if (!found)
	{
		head();
		cout << space() << "\aAdmin not found" << endl;
		redirect();
		return;
	}
	head();
	cout << space() << "Admin deleted" << endl;
	redirect();
}
void Admin::record()
{
	ifstream read("admin.txt");

	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured opening admin.txt" << endl;
		redirect();
		return;
	}
	head();
	while (getline(read, name, '|'))
	{
		getline(read, password);
		display();
	}
	read.close();
	char ch;
	_Thrd_sleep_for(1500);
	cout  << "\nEnter any letter to return to admin options: ";
	cin >> ch;
}

void Admin::admin_portal()
{
	int choice=0;
	head();
	cout << space() << "1. Admin options" << endl;
	cout << space() << "2. Customer options" << endl;
	cout << space() << "3. Room options" << endl;
	cout << space() << "4. Cab options" << endl;
	cout << space() << "5. Food options" << endl;
	cout << space() << "6. Go back to first page" << endl;
	cout << space() << "7. Exit program" << endl;
	cout << space() << "Enter your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		admin_options();
	case 2:
		customer_options();
	case 3:
		room_options();
	case 4:
		cab_options();
	case 5:
		food_options();
	case 6:
		return first_page();
	case 7:
	{
		head();
		cout << space() << "Goodbye";
		exit(0);
	}
	default:
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return admin_portal();
	}
}

void Admin::admin_options()
{
	int choice = 0;
	do
	{
		head();
		cout << space() << "1. Add admin" << endl;
		cout << space() << "2. Search admin" << endl;
		cout << space() << "3. Delete admin" << endl;
		cout << space() << "4. Show admin record" << endl;
		cout << space() << "5. Go back to admin portal" << endl;
		cout << space() << "6. Exit program" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			add_admin();
			break;
		case 2:
			search_admin();
			break;
		case 3:
			delete_admin();
			break;
		case 4:
			record();
			break;
		case 5:
			return admin_portal();
		case 6:
		{
			head();
			cout << space() << "Goodbye";
			exit(0);
		}
		default:
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			return admin_options();
		}
	} while (true);
}
void Admin::customer_options()
{
	int choice = 0;
	do
	{
		head();
		cout << space() << "1. Add customer" << endl;
		cout << space() << "2. Search customer" << endl;
		cout << space() << "3. Update Customer" << endl;
		cout << space() << "4. Delete customer" << endl;
		cout << space() << "5. Show customer record" << endl;
		cout << space() << "6. Go back to admin portal" << endl;
		cout << space() << "7. Exit program" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		Customer c;
		switch (choice)
		{
		case 1:
			c.add_customer();
			break;
		case 2:
		{
			if (c.search_customer())
			{
				head();
				cout << "Customer found" << endl;
				c.display();
				_Thrd_sleep_for(2000);
				char ch;
				cout << "Enter any letter to return to customer options: ";
				cin >> ch;
			}
			break;
		}
		case 3:
			c.update_customer();
			break;
		case 4:
			c.delete_customer();
			break;
		case 5:
			c.record();
			break;
		case 6:
			return admin_portal();
		case 7:
		{
			head();
			cout << space() << "Goodbye";
			exit(0);
		}
		default:
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			return customer_options();
		}
	} while (true);
}
void Admin::room_options()
{
	int choice;
	do
	{
		head();
		cout << space() << "1. Add room" << endl;
		cout << space() << "2. Search room" << endl;
		cout << space() << "3. Update room" << endl;
		cout << space() << "4. Delete room" << endl;
		cout << space() << "5. Show room record" << endl;
		cout << space() << "6. Go back to admin portal" << endl;
		cout << space() << "7. Exit program" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		Room r;
		switch (choice)
		{
		case 1:
		{
			head();
			cout << space() << "1. Add room package" << endl;
			cout << space() << "2. Add room type" << endl;
			cout << space() << "Enter your choice: ";
			cin >> choice;
			if (choice == 1)
				r.add_room("Room Package");
			else if (choice == 2)
				r.add_room("Room Type");
			else
			{
				head();
				cout << space() << "\aInvalid Option" << endl;
				redirect();
			}
			break;
		}
		case 2:
		{
			head();
			cout << space() << "1. Search room package" << endl;
			cout << space() << "2. Search room type" << endl;
			cout << space() << "Enter your choice: ";
			cin >> choice;
			if (choice == 1)
			{
				if (r.search_room("Room Package"))
				{
					head();
					r.display();
					char ch;
					cout  << "Enter any letter to continue: ";
					cin >> ch;
				}
				else
					break;
			}
			else if (choice == 2)
			{
				if (r.search_room("Room Type"))
				{
					head();
					r.display();
					char ch;
					cout <<  "Enter any letter to continue: ";
					cin >> ch;
				}
				else
					break;
			}
			else
			{
				head();
				cout << space() << "\aInvalid Option" << endl;
				redirect();
			}
			break;
		}
		case 3:
		{
			head();
			cout << space() << "1. Update room package" << endl;
			cout << space() << "2. Update room type" << endl;
			cout << space() << "Enter your choice: ";
			cin >> choice;
			if (choice == 1)
				r.update_room("Room Package");
			else if (choice == 2)
				r.update_room("Room Type");
			else
			{
				head();
				cout << space() << "\aInvalid Option" << endl;
				redirect();
				return room_options();
			}
			break;
		}
		case 4:
		{
			head();
			cout << space() << "1. Delete room package" << endl;
			cout << space() << "2. Delete room type" << endl;
			cout << space() << "Enter your choice: ";
			cin >> choice;
			if (choice == 1)
				r.delete_room("Room Package");
			else if (choice == 2)
				r.delete_room("Room Type");
			else
			{
				head();
				cout << space() << "\aInvalid Option" << endl;
				redirect();
				return room_options();
			}
			break;
		}
		case 5:
		{
			r.record();
			break;
		}
		case 6:
			return admin_portal();
		case 7:
		{
			head();
			cout << space() << "Goodbye";
			exit(0);
		}
		default:
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			return room_options();
		}
	} while (true);
}
void Admin::cab_options()
{
	int choice;
	do
	{
		head();
		cout << space() << "1. Add cab" << endl;
		cout << space() << "2. Search cab" << endl;
		cout << space() << "3. Update cab" << endl;
		cout << space() << "4. Delete cab" << endl;
		cout << space() << "5. Show cab record" << endl;
		cout << space() << "6. Go back to admin portal" << endl;
		cout << space() << "7. Exit program" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		Cab b;
		switch (choice)
		{
		case 1:
		{
			b.add_cab();
			break;
		}
		case 2:
		{
			if (b.search_cab())
			{
				head();
				b.display();
				char ch;
				cout << "Enter any letter to continue: ";
				cin >> ch;
			}
			break;
		}
		case 3:
		{
			b.update_cab();
			break;
		}
		case 4:
		{
			b.delete_cab();
			break;
		}
		case 5:
		{
			b.record();
			break;
		}
		case 6:
			return admin_portal();
		case 7:
		{
			head();
			cout << space() << "Goodbye";
			exit(0);
		}
		default:
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			return room_options();
		}
	} while (true);
}
void Admin::food_options()
{
	int choice;
	do
	{
		head();
		cout << space() << "1. Add food" << endl;
		cout << space() << "2. Search food" << endl;
		cout << space() << "3. Update food" << endl;
		cout << space() << "4. Delete food" << endl;
		cout << space() << "5. Show food record" << endl;
		cout << space() << "6. Go back to admin portal" << endl;
		cout << space() << "7. Exit program" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		Food f;
		switch (choice)
		{
		case 1:
		{
			f.add_food();
			break;
		}
		case 2:
		{
			if (f.search_food())
			{
				head();
				f.display();
				char ch;
				cout << "Enter any letter to continue: ";
				cin >> ch;
			}
			break;
		}
		case 3:
		{
			f.update_food();
			break;
		}
		case 4:
		{
			f.delete_food();
			break;
		}
		case 5:
		{
			f.record();
			break;
		}
		case 6:
			return admin_portal();
		case 7:
		{
			head();
			cout << space() << "Goodbye";
			exit(0);
		}
		default:
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			return room_options();
		}
	} while (true);
}

//Customer Functions
void Customer::get_details()
{
	cout << space() << "Enter name: ";
	cin.ignore();
	getline(cin, name);
	cout << space() << "Enter password: ";
	cin >> password;
	cout << space() << "Enter age: ";
	cin >> age;
	cout << space() << "Enter gender: ";
	cin >> gender;
	cout << space() << "Enter number: ";
	cin >> number;
	cout << space() << "Enter address: ";
	cin.ignore();
	getline(cin, address);
}
int Customer::generate_id()
{
	string line, str_id;
	ifstream read("customer.txt");

	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, str_id, '|');
	}
	read.close();
	id = stoi(str_id);
	return ++id;
}
bool Customer::login(string n, string p)
{
	bool found = false;
	string str_id, str_age;
	ifstream read("customer.txt");

	if (read.fail())
	{
		head();
		cout << space() << "\aFile could not be opened" << endl;
		redirect();
		return 0;
	}

	while (getline(read, str_id, '|'))
	{
		getline(read, name, '|');
		getline(read, password, '|');
		getline(read, str_age, '|');
		getline(read, gender, '|');
		getline(read, number, '|');
		getline(read, address);
		id = stoi(str_id);
		age = stoi(str_age);

		if (name == n && password == p)
		{
			found = true;
			read.close();
			break;
		}
	}
	if (found)
		return 1;
	else
	{
		head();
		cout << space() << "Invalid username or password" << endl;
		redirect();
		read.close();
		return 0;
	}
}
void Customer::display()
{
	cout << space() << "Id: " << id << endl;
	cout << space() << "Name: " << name << endl;
	cout << space() << "Password: " << password << endl;
	cout << space() << "Age: " << age << endl;
	cout << space() << "Gender: " << gender << endl;
	cout << space() << "Number: " << number << endl;
	cout << space() << "Address: " << address << endl << endl;
}

void Customer::add_customer()
{
	head();
	get_details();

	ofstream write("customer.txt", ios::app);
	if (write.fail())
	{
		head();
		cout << space() << "\aAn error ocured" << endl;
		cout << space() << "Redirecting....." << endl;
		_Thrd_sleep_for(2000);
		return;
	}
	write << generate_id() << "|" << name << "|" << password << "|" << age << "|" << gender << "|" << number << "|" << address << endl;
	write.close();
	head();
	cout << space() << "Account created successfully" << endl;
	cout << space() << "Given Id: "<< id << endl;
	redirect();
}
bool Customer::search_customer()
{
	int i;
	bool found = false;
	string str_id, str_age;
	ifstream read("customer.txt");

	head();
	cout << space() << "Enter customer id to search: ";
	cin >> i;
	
	if (read.fail())
	{
		head();
		cout << space() << "\aFile could not be opened"<<endl;
		redirect();
		return 0;
	}

	while (getline(read, str_id,'|'))
	{
		getline(read, name, '|');
		getline(read, password, '|');
		getline(read, str_age, '|');
		getline(read, gender, '|');
		getline(read, number, '|');
		getline(read, address);
		id = stoi(str_id);
		age = stoi(str_age);

		if (id == i )
		{
			found = true;
			break;
		}
	}
	read.close();
	if (found)
		return 1;
	else
	{
		head();
		cout << space() << "Customer not found" << endl;
		redirect();
		return 0;
	}
}
void Customer::update_customer()
{
	int i;
	bool found = false;
	string str_id, str_age;
	fstream file1("customer.txt"), file2("customer2.txt", ios::app);

	if (file1.fail() || file2.fail())
	{
		head();
		cout << space() << "\aFile could not be opened" << endl;
		cout << space() << "Redirecting....." << endl;
		_Thrd_sleep_for(2000);
		return;
	}

	head();
	cout << "Enter id of customer to update" << endl;
	cout << space() << "Enter id: ";
	cin >> i;

	while (getline(file1, str_id, '|'))
	{
		getline(file1, name, '|');
		getline(file1, password, '|');
		getline(file1, str_age, '|');
		getline(file1, gender, '|');
		getline(file1, number, '|');
		getline(file1, address);
		age = stoi(str_age);
		id = stoi(str_id);

		if (id == i)
		{
			head();
			display();
			cout << "Enter new details" << endl;
			get_details();
			found = true;
			file2 << id << "|" << name << "|" << password << "|" << age << "|" << gender << "|" << number << "|" << address << endl;
		}
		else
			file2 << id << "|" << name << "|" << password << "|" << age << "|" << gender << "|" << number << "|" << address << endl;
	}
	file1.close();
	file2.close();
	remove("customer.txt");
	rename("customer2.txt", "customer.txt");

	if (found)
	{
		head();
		cout << space() << "Customer updated" << endl;
		redirect();
		return;
	}
	head();
	cout << space() << "\aCustomer not found" << endl;
	redirect();
}
void Customer::delete_customer()
{
	int i;
	bool found = false;
	string str_id, str_age;
	fstream file1("customer.txt"), file2("customer2.txt", ios::app);

	if (file1.fail() || file2.fail())
	{
		head();
		cout << space() << "\aFile could not be opened" << endl;
		redirect();
		return;
	}
	
	head();
	cout << "Enter id of customer to delete" << endl;
	cout << space() << "Enter id: ";
	cin >> i;

	while (getline(file1, str_id, '|'))
	{
		getline(file1, name, '|');
		getline(file1, password, '|');
		getline(file1, str_age, '|');
		getline(file1, gender, '|');
		getline(file1, number, '|');
		getline(file1, address);
		age = stoi(str_age);
		id = stoi(str_id);

		if (id == i)
			found = true;
		else
			file2 << id << "|" << name << "|" << password << "|" << age << "|" << gender << "|" << number << "|" << address << endl;
	}
	file1.close();
	file2.close();
	remove("customer.txt");
	rename("customer2.txt", "customer.txt");

	if (found)
	{
		head();
		cout << space() << "Customer deleted" << endl;
		redirect();
		return;
	}
	head();
	cout << space() << "\aCustomer not found" << endl;
	redirect();
}
void Customer::record()
{
	string str_id, str_age;
	ifstream read("customer.txt");

	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured" << endl;
		redirect();
		return;
	}
	head();
	while (getline(read, str_id, '|'))
	{
		getline(read, name, '|');
		getline(read, password, '|');
		getline(read, str_age, '|');
		getline(read, gender, '|');
		getline(read, number, '|');
		getline(read, address);
		age = stoi(str_age);
		id = stoi(str_id);

		display();
		char ch;
		cout << "Show another record(Y/N): ";
		cin >> ch;
		if (ch != 'y' && ch != 'Y')
			break;
	}
	read.close();
}

void Customer::customer_portal1()
{
	int choice = 0;
	head();
	cout << space() << "1. Login" << endl;
	cout << space() << "2. Signup" << endl;
	cout << space() << "3. Go back" << endl;
	cout << space() << "4. Exit Program" << endl;
	cout << space() << "Enter your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		string Name, Pass;

		head();
		cout << space() << "Enter name: ";
		cin.ignore();
		getline(cin,Name);
		cout << space() << "Enter password: ";
		cin >> Pass;

		if (login(Name, Pass))
			customer_portal2();
		else
			return customer_portal1();
	}
	else if (choice == 2)
	{
		add_customer();
		return customer_portal1();
	}
	else if (choice == 3)
		return first_page();
	else if (choice == 4)
	{
		head();
		cout << space() << "Goodbye";
		exit(0);
	}
	else
	{
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return customer_portal1();
	}
}
void Customer::customer_portal2()
{
	Hotel h;
	h.load_file();

	int choice;
	do
	{
		head();
		cout << space() << "1. Room booking" << endl;
		cout << space() << "2. Cab booking" << endl;
		cout << space() << "3. Food menu" << endl;
		cout << space() << "4. Get bill" << endl;
		cout << space() << "5. Go back" << endl;
		cout << space() << "6. Exit program" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			h.book_room();
			break;
		}
		case 2:
		{
			h.book_cab();
			break;
		}
		case 3:
		{
			h.book_food();
			break;
		}
		case 4:
		{
			Bill b(h);
			b.show_bill(*this);
			char ch;
			cout << "Enter any character to continue: ";
			cin >> ch;
			break;
		}
		case 5:
			customer_portal1();
		case 6:
		{
			head();
			cout << space() << "Goodbye";
			exit(0);
		}
		default:
		{
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			break;
		}
		}
	} while (true);
}

//Cab Functions
void Cab::display()
{
	cout << space() << "Name: " << name << endl;
	cout << space() << "Price: " << price << endl << endl;
}

void Cab::add_cab()
{
	head();
	cout << space() << "Enter name: ";
	cin.ignore();
	getline(cin, name);
	cout << space() << "Enter price: ";
	cin >> price;

	ofstream write("hotel.txt", ios::app);
	if (write.fail())
	{
		head();
		cout << space() << "\aCould not write data to hotel.txt" << endl;
		redirect();
		return;
	}
	write << "Cab" << "|" << name << "|" << price << endl;
	write.close();
	head();
	cout << space() << "Cab added" << endl;
	redirect();
}
bool Cab::search_cab()
{
	bool found = false;
	string categ, line;
	string n;
	ifstream read("hotel.txt");

	head();
	cout << space() << "Enter cab name: ";
	cin.ignore();
	getline(cin, n);
	
	if (read.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return 0;
	}
	
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');

		if (categ == "Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			if(name==n)
			{
				found = true;
				break;
			}
		}	
	}
	read.close();

	if (found)
		return 1;
	else
	{
		head();
		cout << space() << "Cab not found" << endl;
		redirect();
		return 0;
	}
}
void Cab::update_cab()
{
	string n,categ, line;
	bool found = false;
	fstream file1("hotel.txt"), file2("hotel2.txt", ios::app);

	head();
	cout << space() << "Enter cab name: ";
	cin.ignore();
	getline(cin, n);
	
	if (file1.fail() || file1.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}

	while (getline(file1, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');

		if (categ == "Room Package" || categ == "Room Type" || categ == "Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			if (categ == "Cab" && name == n)
			{
				head();
				cout << space() << "Category: " << categ << endl;
				display();

				cout << "Press enter to input new details" << endl;
				cin.ignore();
				cout << space() << "Enter name: ";
				getline(cin, name);
				cout << space() << "Enter price: ";
				cin >> price;
				found = true;
				file2 << categ << "|" << name << "|" << price << endl;
			}
			else
				file2 << categ << "|" << name << "|" << price << endl;
		}
		else if (categ == "Food")
		{
			string id, categ2;
			getline(stream, id, '|');
			getline(stream, categ2, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			file2 << categ << "|" << id << "|" << categ2 << "|" << name << "|" << price << endl;
		}
	}
	file1.close();
	file2.close();
	remove("hotel.txt");
	rename("hotel2.txt", "hotel.txt");

	if (found)
	{
		head();
		cout << space() << "Cab updated" << endl;
		redirect();
	}
	else
	{
		head();
		cout << space() << "\aCab not found" << endl;
		redirect();
	}
}
void Cab::delete_cab()
{
	string n, categ, line;
	bool found = false;
	fstream file1("hotel.txt"), file2("hotel2.txt", ios::app);

	head();
	cout << space() << "Enter cab name: ";
	cin.ignore();
	getline(cin, n);

	if (file1.fail() || file1.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}
	
	while (getline(file1, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');

		if (categ == "Room Package" || categ == "Room Type" || categ == "Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			if (categ == "Cab" && name == n)
				found = true;
			else
				file2 << categ << "|" << name << "|" << price << endl;
		}
		else if (categ == "Food")
		{
			string id, categ2;
			getline(stream, id, '|');
			getline(stream, categ2, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			file2 << categ << "|" << id << "|" << categ2 << "|" << name << "|" << price << endl;
		}
	}
	file1.close();
	file2.close();
	remove("hotel.txt");
	rename("hotel2.txt", "hotel.txt");

	if (found)
	{
		head();
		cout << space() << "Cab deleted" << endl;
		redirect();
	}
	else
	{
		head();
		cout << space() << "\aCab not found" << endl;
		redirect();
	}
}
void Cab::record()
{
	string category, line;
	ifstream read("hotel.txt");

	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured" << endl;
		redirect();
		return;
	}

	head();
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, category, '|');
		if (category == "Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			cout << space() << "Category: " << category << endl;
			display();
			char ch;
			cout << "Show another record(Y/N): ";
			cin >> ch;
			if (ch != 'y' && ch != 'Y')
				break;
		}
	}
	read.close();
}

//Room Functions
void Room::display()
{
	cout << space() << "Name: " << name << endl;
	cout << space() << "Price: " << price << endl << endl;
}
void Room::get_details()
{
	cout << space() << "Enter name: ";
	cin.ignore();
	getline(cin, name);
	cout << space() << "Enter price: ";
	cin >> price;
}

void Room::add_room(string category)
{
	head();
	get_details();

	ofstream write("hotel.txt", ios::app);
	if (write.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}
	write << category << "|" << name << "|" << price << endl;
	write.close();
	head();
	cout << space() << "Room added" << endl;
	redirect();
}
bool Room::search_room(string category)
{
	string n, categ, line;
	bool found = false;
	ifstream read("hotel.txt");

	head();
	cout << space() << "Enter " << category << " name: ";
	cin.ignore();
	getline(cin, n);
	
	if (read.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return 0;
	}
	
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');
		if (categ == category)
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			if (categ == category && name == n)
			{
				found = true;
				break;
			}
		}
	}
	read.close();
	if (found)
		return 1;
	else
	{
		head();
		cout << space() << "Room not found" << endl;
		redirect();
		return 0;
	}
}
void Room::update_room(string category)
{
	string n, categ, line;
	bool found = false;
	fstream file1("hotel.txt"), file2("hotel2.txt", ios::app);

	head();
	cout << space() << "Enter " << category << " name: ";
	cin.ignore();
	getline(cin, n);

	if (file1.fail() || file1.fail())
	{
		head();
		cout << space() << "\aCould not write data to hotel.txt" << endl;
		_Thrd_sleep_for(2000);
		return;
	}

	while (getline(file1, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');
		if (categ == "Room Package" || categ == "Room Type" || categ == "Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			if (categ == category && name == n)
			{
				head();
				cout << space() << "Category: " << categ << endl;
				display();
				
				cout << "Press enter to input new details" << endl;
				cin.ignore();
				cout << space() << "Enter name: ";
				getline(cin, name);
				cout << space() << "Enter price: ";
				cin >> price;
				found = true;
				file2 << categ << "|" << name << "|" << price << endl;
			}
			else
				file2 << categ << "|" << name << "|" << price << endl;
		}
		else if (categ == "Food")
		{
			string id, categ2;
			getline(stream, id, '|');
			getline(stream, categ2, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			file2 << categ << "|" << id << "|" << categ2 << "|" << name << "|" << price << endl;
		}
	}
	file1.close();
	file2.close();
	remove("hotel.txt");
	rename("hotel2.txt", "hotel.txt");

	if (found)
	{
		head();
		cout << space() << "Room updated" << endl;
		redirect();
	}
	else
	{
		head();
		cout << space() << "\aRoom not found" << endl;
		redirect();
	}	
}
void Room::delete_room(string category)
{
	string n, categ, line;
	bool found = false;
	fstream file1("hotel.txt"), file2("hotel2.txt", ios::app);

	head();
	cout << space() << "Enter " << category << " name: ";
	cin.ignore();
	getline(cin, n);

	if (file1.fail() || file1.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}
	
	while (getline(file1, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');
		if (categ == "Room Package" || categ == "Room Type" || categ == "Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			if (categ == category && name == n)
				found = true;
			else
				file2 << categ << "|" << name << "|" << price << endl;
		}
		else if (categ == "Food")
		{
			string id, categ2;
			getline(stream, id, '|');
			getline(stream, categ2, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			file2 << categ << "|" << id << "|" << categ2 << "|" << name << "|" << price << endl;
		}
	}
	file1.close();
	file2.close();
	remove("hotel.txt");
	rename("hotel2.txt", "hotel.txt");

	if (found)
	{
		head();
		cout << space() << "Room deleted" << endl;
		redirect();
	}
	else
	{
		head();
		cout << space() << "\aRoom not found" << endl;
		redirect();
	}	
}
void Room::record()
{
	string category, line;
	ifstream read("hotel.txt");

	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured" << endl;
		cout << space() << "Redirecting....." << endl;
		_Thrd_sleep_for(2000);
		return;
	}
	head();
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, category, '|');
		if (category == "Room Package" || category == "Room Type")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			cout << space() << "Category: " << category << endl;
			display();
			char ch;
			cout << "Show another record(Y/N): ";
			cin >> ch;
			if (ch != 'y' && ch != 'Y')
				break;
		}
	}
	read.close();
}

//Food Functions
void Food::display()
{
	cout << space() << "Category: " << category << endl;
	cout << space() << "Name: " << name << endl;
	cout << space() << "Price: " << price << endl << endl;
}
int Food::generate_id()
{
	string line,str_id;
	ifstream read("hotel.txt");

	while (getline(read, line))
	{
		istringstream stream(line);
		string categ;
		getline(stream, categ, '|');
		if (categ == "Food")
			getline(stream, str_id, '|');
	}
	read.close();
	id = stoi(str_id);
	return ++id;
}
void Food::get_details()
{
	cout << space() << "Enter category: ";
	cin.ignore();
	getline(cin, category);
	cout << space() << "Enter name: ";
	getline(cin, name);
	cout << space() << "Enter price: ";
	cin >> price;
}

void Food::add_food()
{
	head();
	get_details();

	ofstream write("hotel.txt", ios::app);
	if (write.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}
	write << "Food" << "|" << generate_id() << "|" << category << "|" << name << "|" << price << endl;
	write.close();
	head();
	cout << space() << "Food added" << endl;
	cout << space() << "Assigned id: "<< id << endl;
	redirect();
}
bool Food::search_food() 
{
	int i;
	bool found = false;
	string line, categ, id_str;
	ifstream read("hotel.txt");

	head();
	cout << space() << "Enter food id: ";
	cin >> i;
	
	if (read.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return 0;
	}
	
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, categ, '|');
		if (categ == "Food")
		{
			getline(stream, id_str, '|');
			getline(stream, category, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			id = stoi(id_str);

			if ( id == i)
			{
				found = true;
				break;
			}
		}
		
	}
	read.close();
	if (found)
		return 1;
	else
	{
		head();
		cout << space() << "Food not found" << endl;
		redirect();
		return 0;
	}
}
void Food::update_food()
{
	int i;
	bool found = false;
	string  line;
	fstream file1("hotel.txt"), file2("hotel2.txt", ios::app);

	head();
	cout << space() << "Enter food id: ";
	cin >> i;

	if (file1.fail() || file1.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}

	while (getline(file1, line))
	{
		istringstream stream(line);
		getline(stream, category, '|');
	
		if (category != "Food")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			file2 << category << "|" << name << "|" << price << endl;
		}
		else if(category=="Food")
		{
			string id_str;
			getline(stream, id_str, '|');
			getline(stream, category, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			id = stoi(id_str);

			if (id == i)
			{
				head();
				display();
				cout << "Enter new details";
				get_details();
				file2 << "Food" << "|" << id << "|" << category << "|" << name << "|" << price << endl;
				found = true;
			}
			else
			{
				file2 << "Food" << "|" << id << "|" << category << "|" << name << "|" << price << endl;
			}
		}
	}
	file1.close();
	file2.close();
	remove("hotel.txt");
	rename("hotel2.txt", "hotel.txt");

	if (found)
	{
		head();
		cout << space() << "Food updated" << endl;
		redirect();
		return;
	}
	head();
	cout << space() << "\aFood not found" << endl;
	redirect();
}
void Food::delete_food()
{
	int i;
	bool found = false;
	string  line;
	fstream file1("hotel.txt"), file2("hotel2.txt", ios::app);

	head();
	cout << space() << "Enter food id: ";
	cin >> i;

	if (file1.fail() || file1.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}

	while (getline(file1, line))
	{
		istringstream stream(line);
		getline(stream, category, '|');

		if (category != "Food")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			file2 << category << "|" << name << "|" << price << endl;
		}
		else
		{
			string id_str;
			getline(stream, id_str, '|');
			getline(stream, category, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			id = stoi(id_str);

			if (id == i)
			{
				found = true;
			}
			else
			{
				file2 << "Food" << "|" <<id<<"|" << category << "|" << name << "|" << price << endl;
			}
		}
	}
	file1.close();
	file2.close();
	remove("hotel.txt");
	rename("hotel2.txt", "hotel.txt");

	if (found)
	{
		head();
		cout << space() << "Food deleted" << endl;
		redirect();
		return;
	}
	head();
	cout << space() << "\aFood not found" << endl;
	redirect();
}
void Food::record()
{
	ifstream read("hotel.txt");
	if (read.fail())
	{
		head();
		cout << space() << "\aAn error ocured" << endl;
		redirect();
		return;
	}

	head();
	string line;
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, category, '|');
		if (category == "Food")
		{

			string id_str;
			getline(stream, id_str, '|');
			getline(stream, category, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			id = stoi(id_str);
			display();
			char ch;
			cout << "Show another record(Y/N): ";
			cin >> ch;
			if (ch != 'y' && ch != 'Y')
			{
				break;
			}
		}
	}
	read.close();
}

//Hotel Functions
void Hotel::load_file()
{
	string category, name, line;
	float price;
	ifstream read("hotel.txt");

	if (read.fail())
	{
		head();
		cout << space() << "\aCould not open hotel.txt" << endl;
		redirect();
		return;
	}
	
	while (getline(read, line))
	{
		istringstream stream(line);
		getline(stream, category, '|');

		if(category=="Room Package"||category=="Room Type"||category=="Cab")
		{
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();

			if (category == "Room Package")
				room_package.push_back({ name,price });
			else if (category == "Room Type")
				room_type.push_back({ name,price });
			else if (category == "Cab")
				cab.push_back({ name,price });
		}
		else if (category == "Food")
		{
			string id_str, categ2;
			int id;
			getline(stream, id_str, '|');
			getline(stream, categ2, '|');
			getline(stream, name, '|');
			stream >> price;
			stream.ignore();
			id = stoi(id_str);
			food.push_back({id,categ2,name,price});
		}
	}
	read.close();
}

int Hotel::choose_option(vector<Room> vec)
{
	int choice = 0;
	for (int i = 0; i < vec.size(); i++)
		cout << space() << i + 1 << ". " << vec[i].get_name() << " - Rs." << vec[i].get_price() << endl;
	cout << space() << "Enter your choice: ";
	cin >> choice;
	if (choice >= 1 && choice <= vec.size())
		return choice - 1;
	else
	{
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return choose_option(vec);
	}
}
void Hotel::book_room()
{
	head();
	cout << "Room Packages" << endl;
	int package_index = choose_option(room_package);

	head();
	cout << "Room Types" << endl;
	int type_index = choose_option(room_type);
	
	head();
	cout  << "You selected" << endl;
	cout << space() << room_package[package_index].get_name() << ": " << room_package[package_index].get_price() << endl;
	cout << space() << room_type[type_index].get_name() << ": " << room_type[type_index].get_price() << endl;
	cout << space() << "Total cost: " << room_package[package_index].get_price() + room_type[type_index].get_price() << endl << endl;

	cout << space() << "1. Confirm selection" << endl;
	cout << space() << "2. Select another" << endl;
	int choice = 0;
	cout << space() << "Enter your choice: ";
	cin >> choice;

	if (choice == 1)
	{
		head();
		cout << space() << "Purchase successfull" << endl;
		redirect();
		room_cost += room_package[package_index].get_price() + room_type[type_index].get_price();
	}
	else if (choice == 2)
		return book_room();
	else
	{
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return book_room();
	}
}
void Hotel::book_cab()
{
	int index, choice;
	float km;

	head();
	cout << "Available cabs" << endl;
	for (int i = 0; i < cab.size(); i++)
		cout << space() << i + 1 << ". " << cab[i].get_name() << " - Rs." << cab[i].get_price() <<" per km" << endl;
	cout << space() << "Enter your choice: ";
	cin >> choice;

	if (choice >= 1 && choice <= cab.size())
		index= choice - 1;
	else
	{
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return book_cab();
	}
	
	head();
	cout << space() << "Enter kilometres to travel: ";
	cin >> km;
	head();
	cout  << "You selected" << endl;
	cout << space() << cab[index].get_name() << endl;
	cout << space() << "You total cost for travel is: " << cab[index].get_price() * km << endl << endl;

	cout << space() << "1. Confirm selection" << endl;
	cout << space() << "2. Select another" << endl;
	cout << space() << "Enter your choice: ";
	cin >> choice;

	if (choice == 1)
	{
		head();
		cout << space() << "Purchase successfull" << endl;
		redirect();
		cab_cost += cab[index].get_price() * km;
	}
	else if (choice == 2)
		return book_cab();
	else
	{
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return book_cab();
	}
}
void Hotel::book_food()
{
	int index_name, index_categ, choice;
	vector<string> category, name;
	vector<float> price;
	string temp = "";
	int counter = 0;

	head();
	for (int i = 0; i < food.size(); i++)
	{
		if (temp != food[i].get_category())
		{
			category.push_back(food[i].get_category());
			cout << space() << ++counter << ". " << food[i].get_category() << endl;
		}
		temp = food[i].get_category();
	}
	cout << space() << "Enter your choice: ";
	cin >> choice;

	if (choice >= 1 && choice <= counter)
	{
		head();
		index_categ = choice-1;
		counter = 0;
		for (int i = 0; i < food.size(); i++)
		{
			if(food[i].get_category()==category[index_categ])
			{
				name.push_back(food[i].get_name());
				price.push_back(food[i].get_price());
				cout << space() << ++counter << ". " << food[i].get_name() << " - Rs." << food[i].get_price() << endl;
			}
		}
		cout << space() << "Enter your choice: ";
		cin >> choice;
		index_name = choice-1;

		selected_food.push_back(name[index_name]);
		selected_food_price.push_back(price[index_name]);
		food_cost += price[index_name];

		head();
		cout << "You selected" << endl;
		for (int i = 0; i < selected_food.size(); i++)
			cout << space() << i + 1 << ". " << selected_food[i] << ": " << selected_food_price[i] << endl;
		cout << space() << "Total: " << food_cost << endl << endl;

		cout << space() << "1. Confirm selection" << endl;
		cout << space() << "2. Select more" << endl;
		cout << space() << "Enter your choice: ";
		cin >> choice;
		if (choice == 1)
		{
			head();
			cout << space() << "Purchase successfull" << endl;
			redirect();
		}
		else if (choice == 2)
		{
			return book_food();
		}
		else
		{
			head();
			cout << space() << "\aInvalid Option" << endl;
			redirect();
			return book_food();
		}
	}
	else
	{
		head();
		cout << space() << "\aInvalid Option" << endl;
		redirect();
		return book_food();
	}
}

//Bill Functions
Bill::Bill(Hotel h)
{
	tax_rate = 0.15;
	service_rate = 0.05;

	room_cost = h.get_room_cost();
	cab_cost = h.get_cab_cost();
	food_cost = h.get_food_cost();
}
void Bill::show_bill(Customer c)
{
	subtotal = room_cost + cab_cost + food_cost;
	tax = subtotal * tax_rate;
	service_fee = subtotal * service_rate;
	total = subtotal + tax + service_fee;

	head();
	cout  << space() << "------------------------------------"  << endl;
	cout  << space() << "               BILL                 "  << endl;
	cout  << space() << "------------------------------------"  << endl;
	cout << space() << setw(20) << left << "Customer Name" << ": " << c.get_name() << endl;
	cout << space() << setw(20) << left << "Customer ID" << ": " << c.get_id() << endl;
	cout << space() << "------------------------------------" << endl;
	cout << space() << setw(20) << left << "Room Cost" << ": Rs. " << room_cost << endl;
	cout << space() << setw(20) << left << "Cab Cost" << ": Rs. " << cab_cost << endl;
	cout << space() << setw(20) << left << "Food Cost" << ": Rs. " << food_cost << endl;
	cout << space() << "------------------------------------" << endl;
	cout << space() << setw(20) << left << "Subtotal" << ": Rs. " << subtotal << endl;
	cout << space() << setw(20) << left << "Tax" << ": Rs. " << tax << endl;
	cout << space() << setw(20) << left << "Service Fee" << ": Rs. " << service_fee << endl;
	cout << space() << "------------------------------------" << endl;
	cout << space() << setw(20) << left << "Total" << ": Rs. " << total << endl;
	cout << space() << "------------------------------------" << endl;
}

void first_page()
{
	int choice = 0;
	head();
	cout << space() << "1. Admin Portal" << endl;
	cout << space() << "2. Customer Portal" << endl;
	cout << space() << "3. Exit Program" << endl;
	cout << space() << "Enter your choice: ";
	cin >> choice;
	Admin admin;
	Customer customer;
	switch (choice)
	{
	case 1:
		admin.login();
	case 2:
		customer.customer_portal1();
	case 3:
	{
		head();
		cout << space() << "Goodbye";
		exit(0);
	}
	default:
		head();
		cout << space() << "\aInvalid Option" << endl;
		cout << space() << "Redirecting....." << endl;
		_Thrd_sleep_for(2000);
		first_page();
	}
}
