#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<vector>


inline bool is_file_exist(const std::string& fileName)
{
	std::ifstream infile("./installed_modules/" + fileName);
	bool flag = infile.good();
	
	infile.clear();  
	infile.close();

	return flag;
}

inline void install_file(const std::string& temp_name)
{
	std::ofstream outfile("./installed_modules/" + temp_name, std::ios::out | std::ios::_Noreplace);
	outfile.clear();
	outfile.close();  
}

inline void print_project_name(std::istream& file_dep, std::string& read_string)
{
	getline(file_dep, read_string);								// read after "ProjectName"  to the end of line
	size_t pos_quote = read_string.find('"');				   // find position of the first quote
	std::string temp_name = read_string.substr(pos_quote);
	temp_name.erase(temp_name.end() - 1 );					 // remove unnecessary comma 
	std::cout << "\t\t\t Project Name: " << temp_name << "\n\n";
}

inline void put_all_libraries_of_dependencies_in_vector(std::istream& file_dep, std::string& read_string, std::vector<std::string>& names_dep)
{
	getline(file_dep, read_string, '"');	 // Read after dependencies

	bool flag = true;						// flag to get the Names, because exist period between them
	while (read_string.find("]"))
	{
		getline(file_dep, read_string, '"');
		if (flag)
		{
			names_dep.insert(names_dep.begin(), read_string);  // save the names from "dependencies", backwards in vector, 
											   				  // so we can access them through  read_string(back);
			flag = false;
		}
		else
			flag = true;
	}
}

inline void check_for_already_read_line_and_skip_it(std::istream& file_packages, std::string& read_string, std::vector<std::string>& read_names, bool& name_is_read_before)
{
	name_is_read_before = false;										// reset flag

	for (int i = 0; i < read_names.size() && !name_is_read_before; ++i)   
	{
		if (!read_names[i].compare(read_string))				 	// If a name has already read before
		{														   // with this "if" we reach the end of the line
			name_is_read_before = true;			

			while (read_string.find("]") && read_string.find(": [],\n  ") && read_string.find(": [],\n  ") && read_string.find(": []\n}"))
			{
				getline(file_packages, read_string, '"');
			}

		}
	}

}

inline void save_names_from_dependencies_in_vector_names_dep(std::istream& file_packages, std::string& read_string, std::vector<std::string>& names_dep, bool& flag, short& count_of_libraries, short& index)
{
	getline(file_packages, read_string, '"');  // Read after the current "temp_name"

	flag = true;							  // flag to get the Names, because exist period between them
	count_of_libraries = 0;
	index = -1;
	while (read_string.find("]") && read_string.find(": [],\n  ") && read_string.find(": [],\n  ") && read_string.find(": []\n}"))
	{
		getline(file_packages, read_string, '"');
		if (flag)
		{
			++count_of_libraries;
			++index;
			names_dep.insert(names_dep.end() - index, read_string);   // save the names from "dependencies" in the vector "names_dep"
			flag = false;
		}
		else
			flag = true;
	}
}

inline void install_libraries_from(std::string& temp_name)
{
	if (!is_file_exist(temp_name))
	{
		std::cout << "Installing " << temp_name << "." << std::endl;
		install_file(temp_name);
	}
	else{
		std::cout << temp_name << " is already installed." << std::endl;
	}
}

void inline print_details_of_installation(const std::string& temp_name, std::vector<std::string>& names_dep, short& count_of_libraries)
{
	switch (count_of_libraries)
	{
	case 0: break;
	case 1: std::cout << "In order to install " << temp_name << ", we need " << names_dep.back() << "." << std::endl;
		break;
	case 2: std::cout << "In order to install " << temp_name << ", we need " << names_dep[names_dep.size() - 1] << " and " << names_dep[names_dep.size() - 2] << "." << std::endl;
		break;
	default:
	{
			   std::cout << "In order to install " << temp_name << ", we need";
			   for (int i = 1; i <= count_of_libraries; ++i)
			   {
				   std::cout << ", " << names_dep[names_dep.size() - i];
			   }
			   std::cout << ".\n";
	}
	}
}



int main()
{
	
	using namespace std;

	//@@@@@@@@@$$$$$$$$$#########=========---------File: dependencies.json---------=========#########$$$$$$$$$@@@@@@@@@//

	ifstream file_dep("dependencies.json", ios::in);  // Make input stream to file dependencies
	if (!file_dep.is_open())   
	{
		cout << "File cannot be opened!\n";
		return 1;
	}


	bool keepReading = true;
	bool flag = true;
	string read_string;
	vector<string> names_dep;    // vector of all names from dependencies.json
	

	do
	{
		getline(file_dep, read_string, '"');

		if (file_dep)    // check for correctness
		{
			if (! read_string.compare("projectName")) 
			{
				print_project_name(file_dep, read_string);  // Print the name of project
			}
			else
			{
				if (! read_string.compare("dependencies"))  // Read dependencies
				{
					put_all_libraries_of_dependencies_in_vector(file_dep, read_string, names_dep);
				}
			}
		}
		else
		{
			if (file_dep.eof())
			{
				//cout << "End of file!\n";
				keepReading = false;
			}
			else
			{
				//cout << "Fail!";   
				file_dep.clear();   // status is good to be clear before ignore
				file_dep.ignore();  // ignore current character
			}
		}
	} while (keepReading);

	file_dep.clear();
	file_dep.close();

	//#################################################################################################################//




	//@@@@@@@@@$$$$$$$$$#########=========---------File: all_packages.json---------=========#########$$$$$$$$$@@@@@@@@@//


	ifstream file_packages("all_packages.json", ios::in);  // Make input stream to file all_packages
	if (!file_packages.is_open())
	{
		cout << "File cannot be opened!\n";
		return 1;
	}


	// Very Important! -> with "./FOLDER" enter in directory in any computer !!!  
	// Example: 
	//---> ofstream outfile("./installed_modules/" + names_dep.back() + ".txt", ios::out | ios::_Noreplace);  //  No replace the file
	//---> outfile.close();   // !!! Must Close the File !!! 


	//================================================================================================================
	// = ----> How to use the vector of strings "names_dep"															 =
	// =																											 =
	// = names_dep.insert(names_dep.end() - i, "NAME_LIBRARY");		 // ---> insert element in vector "names_dep"	 =
	// = names_dep.pop_back();					                    // ---> pop back element (from the right)		 =
	// = names_dep.back();						                   // ---> Access the element of the vector			 =
	// =																											 =
	// = i --> index ; with each new insert (in the same library), the index is increasing ( ++ i )					 =
	// =   --> when change library, the index start value is 0														 =
	//================================================================================================================

	keepReading = true;
	short index = -1;
	bool read_From_The_Beginning = false;
	short count_of_libraries = 0;

	string temp_name;
	vector<string> read_names;   // vector with already read names of libraries
	bool name_is_read_before = false;

	// !!! Important !!! use only "names_dep"  to save all names of libraries

	do
	{
		if (read_From_The_Beginning)
		{
			file_packages.clear();
			file_packages.seekg(0, ios::beg);  // return pointer to beginning of file
			read_From_The_Beginning = false; 
		}
		else
		{
			getline(file_packages, read_string, '"');


			if (file_packages && names_dep.size())  // check  correctness  +  "names_dep" is not empty 
			{

				check_for_already_read_line_and_skip_it (file_packages, read_string, read_names, name_is_read_before);
			

				if (!read_string.compare(names_dep.back()) &&  !name_is_read_before)  // Read dependencees while the vector "names_dep" is not empty
				{
					temp_name = names_dep.back();      // look better to read + use it in switch
					
					install_libraries_from(temp_name);
					
					read_names.push_back(temp_name);  // save the current name, to after skipt the current line
					names_dep.pop_back();			 // delete last name in the vector "names_dep"

					save_names_from_dependencies_in_vector_names_dep(file_packages, read_string, names_dep, flag, count_of_libraries, index);

					print_details_of_installation(temp_name, names_dep, count_of_libraries);
					
					//for (int i = 0; i < names_dep.size(); ++i) // SEE what is inside the vector  "names_packages"   
					//{
					//	cout << "Names_dep [" << i << "]= " << names_dep[i] << endl;
					//}

					read_From_The_Beginning = true; 
				}

			}
			else
			{
				if (file_packages.eof())
				{
					//cout << "End of file!\n";
					keepReading = false;
				}
				else
				{
					//cout << "Fail!";
					file_packages.clear();    // status is good to be clear before ignore
					file_packages.ignore();   // ignore current character
				}
			}
		}
		
	} while (keepReading);


	file_packages.clear();
	file_packages.close();


	cout << "All done.\n\n\n";
	return 0;
}