#include <iostream> // cin && cout								| input output
#include <string> // string										| storing text
#include <unordered_map> // hash<string>hasher;					| hashing password
#include <fstream> //ifstream && ofstream && open() && close()  | file operations
#include <sstream> //stringstream								| used for file operations too

using namespace std;


//inprogram db
struct			LocDb
{
	string		login;
	string		password;
};


//"CountLines()" Function called for getting size for structure LocDb returns(Size)
int				CountLines(string fname)
{
	ifstream	file;
	int			_SizeOfDb = 0;
	string		c = "";
	file.open("Users.csv");
	while (getline(file, c))
	{
		_SizeOfDb++;
	}
	return _SizeOfDb;
}

//"GetFromFile()" called for filling structure "LocDb"
void			GetFromFile(LocDb *&DB, int &_SizeOfDb)
{
	ifstream	database;
	database.open("Users.csv");
	_SizeOfDb = CountLines("Users.csv");
	//cout << "Size of Struct : " << _SizeOfDb << "\n"; // debug
	
	int			LinePos = 0;
	string		Line = "";
	DB			= new LocDb[_SizeOfDb];
	while (getline(database, Line))
	{
		stringstream database(Line);

			
		getline(database, DB[LinePos].login, ';');
			
		getline(database, DB[LinePos].password, ';');
		
		/*cout << "Login : " << DB[LinePos].login << "\nPassoword : " << DB[LinePos].password << "\n";*/ //debug

		LinePos++;
	}
	database.close();

}

//"PutInFile()" called for saving user credentials into local file
void			PutInFile(string Login, size_t Password)
{
	ofstream database;
	database.open("Users.csv", ios::in | ios::out | ios::app);
	database << Login << ";" << Password << "\n";
	database.close();
}

//"LoginCheck()" called for checking if user used allowed symbols for his nickname returns(True | False)
bool			LoginCheck(string login)
{
	string		AllowedSymbols = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789_-";
	int			LoginPos = 0;

	while (LoginPos < login.length())
	{
		bool		ok = 0;
		int			SymbolPos = 0;

		while (SymbolPos < AllowedSymbols.length())
		{
			if (login[LoginPos] == AllowedSymbols[SymbolPos++])
			{
				ok = 1;
				break;
			}
		}
		if (!ok)
		{
			return 0;
		}
		LoginPos++;
	}
	return 1;

}

//"LoginCheck()" called for checking if user used allowed symbols for his password returns(True | False)
bool			PasswordCheck(string password)
{
	string		AllowedSymbols = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789!@#$%^&*()_-+={}[]|/<>,.?";
	int			PasswordPos = 0;

	while (PasswordPos < password.length())
	{
		bool		ok = 0;
		int			SymbolPos = 0;

		while (SymbolPos < AllowedSymbols.length())
		{
			if (password[PasswordPos] == AllowedSymbols[SymbolPos++])
			{
				ok = 1;
				break;
			}
		}
		if (!ok)
		{
			return 0;
		}
		PasswordPos++;
	}
	return 1;
}

//"CheckIfExists()" called for checking if user trying to login in existing account returns(True | False)
bool			CheckIfExists(LocDb *DB, int _SizeOfDb, string login)
{
	for (int i = 0; i < _SizeOfDb; i++)
	{
		if (login == DB[i].login)
		{
			return 1;
		}
	}
	return 0;
}

void Input(string &INP, string UI)
{
	cout << UI;
	getline(cin, INP);
}


//SignUp()" called for adding user to local database
void			SignUp()
{
	cout << "Register Account\n"; // just for clarification

	string		login;
	Input(login, "Input Login (A-Z, a-z, 0-9, _- ): ");
	
	LocDb*		DB = nullptr;
	int			_SizeOfDb = 0;

	GetFromFile(DB, _SizeOfDb);
	while (LoginCheck(login) != 1 || CheckIfExists(DB, _SizeOfDb, login) == 1)
	{
		cout << "\nUnallowed Symbol\tOr User Already exists\n";
		Input(login, "Input Login (A-Z, a-z, 0-9, _- ): ");
	}


	string		password;
	Input(password, "Input Password (A-Z, a-z, 0-9, all symbols) : ");

	while (PasswordCheck(password) != 1)
	{
		cout << "Incorrect Symbol In Passoword\n";
		Input(password, "Input Password (A-Z, a-z, 0-9, all symbols) : ");
	}

	hash<string>hasher;

	size_t		PasswordHash = hasher(password);


	

	/*cout << "Password hash : " << PasswordHash;*/ //debug
	
	PutInFile(login, PasswordHash);
}
//"HashCheck()" called for checking if user have inputed right password for account returns(True | False)
bool			HashCheck(string login,string password, LocDb *DB, int _SizeOfDb)
{
	for (int i = 0; i < _SizeOfDb; i++)
	{
		if (DB[i].login == login)
		{
			hash<string>hasher;
			size_t			hash1 = hasher(password);
			size_t			hash2;
			stringstream	hash(DB[i].password);

			hash >> hash2;

			/*cout << "1 : " << hash1 << "\n2 : " << hash2 << "\n";*/ //debug
			if (hash1 == hash2)
			{
				return 1;
			}
		}
	}
	return 0;
}



//"SignIn()" called for logging in users account returns(True | False)
bool			SignIn()
{
	cout << "Sign Into Account\n";  // just for clarification
	
	string		login;
	Input(login, "Input Login (A-Z, a-z, 0-9, _- ): ");

	while (LoginCheck(login) != 1)
	{
		cout << "\nIncorrect Symbol In Login (A-Z, a-z, 0-9, _-) : ";
		Input(login, "Input Login (A-Z, a-z, 0-9, _- ): ");
	}

	LocDb*		DB = nullptr;
	int			_SizeOfDb = 0;

	GetFromFile(DB, _SizeOfDb);
	if (CheckIfExists(DB, _SizeOfDb, login))
	{
		string password;
		Input(password, "Input Password (A-Z, a-z, 0-9, all symbols) : ");
		while (PasswordCheck(password) != 1)
		{
			cout << "Incorrect Symbol In Passoword : ";
			Input(password, "Input Password (A-Z, a-z, 0-9, all symbols) : ");
		}

		hash<string>hasher;
		size_t		PasswordHash = hasher(password);
		if (HashCheck(login, password, DB, _SizeOfDb))
		{
			return 1;
		}
	}

	else
	{ 
		cout << "User : " << login << " not exists\n";
	}

	return 0;
}


void			main()
{
	SignUp(); // register new account

	bool		Logged = SignIn(); // log into existing account

	cout << "Logged In : " << Logged; // show if login was succesful
}