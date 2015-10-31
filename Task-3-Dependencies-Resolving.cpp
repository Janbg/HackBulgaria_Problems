#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<vector>




int main()
{
	using namespace std;


	//@@@@@@@@@$$$$$$$$$#########=========---------File: dependencies.json---------=========#########$$$$$$$$$@@@@@@@@@//

	ifstream file_dep("dependencies.json", ios::in);  // Pravim potok s faila dependencies
	if (!file_dep.is_open())   
	{
		cout << "File cannot be opened!\n";
		return 1;
	}


	bool keepReading = true;
	string read_string;
	vector<string> names_dep; // vector of names of dependencies
	

	do
	{
		getline(file_dep, read_string, '"');

		if (file_dep)    // proverka za korektnos
		{
			if (! read_string.compare("projectName")) // Izpishva imeto na proekta
			{
				getline(file_dep, read_string);  // cheta vsichko sled ProjectName do kraq na reda
				size_t pos_quote = read_string.find('"'); // find position of the first quote
				string temp_name = read_string.substr(pos_quote);
				temp_name.erase(temp_name.end() - 1 );  // premava izlishnata comma / zapetaq
				cout << "\t\t\t Project Name: " << temp_name << endl;
			}
			else
			if (!read_string.compare("dependencies"))  // Prochita zadaljeniqta 
			{
				getline(file_dep, read_string, '"');  // premahvame dependencies

				bool flag = true;   // flag za vzimane samo na dumite, za6toto imat period
				while ( read_string.find("]") )
				{
					getline(file_dep, read_string, '"');
					if (flag)
					{
						cout << "===---WHILE-->  " << read_string << endl; // DELETE posle
						names_dep.push_back(read_string);  // slagame imenata ot dependencies vav vector

						flag = false;
					}
					else
						flag = true;
				}

			}
			

		}
		else
		{
			if (file_dep.eof())
			{
				cout << "End of file!\n";  // DELETE posle
				keepReading = false;
			}
			else
			{
				cout << "Fail!";
				file_dep.clear();   // predi da napravim ignore  - sastoqnieto na potoka trqbva da e clear
				file_dep.ignore();  // ako ne mu podadem chislo po default e da ignorirame samo 1-viq simvol
			}
		}
	} while (keepReading);

	file_dep.clear();
	file_dep.close();

	//#################################################################################################################//



	//@@@@@@@@@$$$$$$$$$#########=========---------File: all_packages.json---------=========#########$$$$$$$$$@@@@@@@@@//


	ifstream file_packages("all_packages.json", ios::in);  // Pravim potok s faila all_packages
	if (!file_packages.is_open())
	{
		cout << "File cannot be opened!\n";
		return 1;
	}


	// Very Important! -> with "./FOLDER" enter in the directory in any computer !!!  

	ofstream outfile("./installed_modules/" + names_dep.back() + ".txt", ios::out | ios::_Noreplace);  //  No replace the file

	
	outfile.close();   // !!! Must Close the File !!! 


	cout << "r$#@!#$@$#@$#@!$!!#$@#$\n";
	vector<string> help;
	help.push_back("firs");
	help.push_back("second");
	help.push_back("third");

	help.erase(help.begin());

	cout << "size= " << help.size() << endl;

	help.erase(help.begin());
	
	cout << "size= "<< help.size() << endl;
	



	keepReading = true;
	vector<string> names_packages;   // vector of names of all_packages


	do
	{
		getline(file_packages, read_string, '"');

		if (file_packages)
		{
			if ( (names_dep.size() > 0) && !read_string.compare(names_dep.front()))  // Prochita dependencees dokato vav vectora "names_dep" ne ostane ni6to
			{
				names_dep.erase(names_dep.begin()); // premahva 1-viq ime v vectora names_dep (v nashiq sluchai imeto: backbone)


				bool flag = false;   // flag za vzimane samo na dumite, za6toto imat period
				while (read_string.find("]"))
				{
					getline(file_packages, read_string, '"');
					if (flag)
					{
						cout << "===---WHILE-->  " << read_string << endl; // DELETE posle
						names_packages.push_back(read_string);  // slagame imenata ot dependencies vav vector "names_packages"

						flag = false;
					}
					else
						flag = true;
				}

			}

		}
		else
		{
			if (file_packages.eof())
			{
				cout << "End of file!\n";
				keepReading = false;
			}
			else
			{
				cout << "Fail!"; 
				file_packages.clear();  // predi da napravim ignore  - sastoqnieto na potoka trqbva da e clear
				file_packages.ignore(); // ako ne mu podadem chislo po default e da ignorirame samo 1-viq simvol
			}
		}
	} while (keepReading);


	file_packages.clear();
	file_packages.close();


	cout << "\n\n END !!!\n";
	return 0;
}