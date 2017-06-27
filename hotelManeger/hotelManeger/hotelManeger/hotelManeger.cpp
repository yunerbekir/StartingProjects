// hotelManeger.cpp : Defines the entry point for the console application.
//
// room activities
#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<iomanip>
#include<vector>

#include"Room.h"



void DatabaseCheck();
void UserInterface();
void AdministratorUI();
void WriteDatabaseUI();
void ShowDatabaseUI();
void DeleteDatabaseUI();
void DispayActivitiesUI();
void DisplayRoomActivities();
void DisplayActivityRooms();

void NewRoomsInput();
void NewActivitiesInput();
Room SingeRoomInput();
bool CorrectDate(std::string);
bool IsContainedInArr(const int,std::string);

void PrintRooms(std::string);
bool RoomOfStatus(std::string);
void PrintActivities();
void DeleteRoom();
void ChangeRoomInfo();
void FillUpRoom();
void ClearRoom();
void ReserveRoom();
void CompleteReservation();
void CancelReservation();


void LoadRoomsToMemmory();
void LoadActivitiesToMemmory();
std::string RoomToString(Room);

void SaveRoomsToFile();
void SortRoomsByNumber();

void AdministratorStackOverflowPreventer();


std::vector<Room> VectorOfRooms;
std::vector<std::string> VectorOfActivities;


int main()
{
	DatabaseCheck();
	LoadRoomsToMemmory();
	LoadActivitiesToMemmory();
	UserInterface();
}



void DatabaseCheck()
{
	std::fstream file;
	// the room information is in this file     
	file.open("hotelRoomsInfo.txt", std::ios::in);
	if (!file) // if that file doesn't exist
	{
		file.close();
		file.open("hotelRoomsInfo.txt", std::ios::out); // we create it
	}
	file.close();
	// the activities list is in this file
	file.open("activities.txt", std::ios::in);
	if (!file) // if that file doesn't exist
	{
		file.close();
		file.open("activities.txt", std::ios::out); // we create it
	}
	file.close();
}

// this is the UI, it has Sub-menus.
// to access the administrator UI type 123456
void UserInterface()
{
	system("cls");
	std::cout << "\t\t\t\tMain Menu\n\n";
	std::cout << "1. Show Vacant rooms.\n";
	std::cout << "2. Fill Up Room.\n";
	std::cout << "3. Clear Out Room.\n";
	std::cout << "4. Reserve Room.\n";
	std::cout << "5. Complete Reservation.\n";
	std::cout << "6. Cancel Reservation.\n";
	std::cout << "7. Show Activities.\n";
	std::cout << "0. To exit.\n";
	int userChoice;
	std::cout << "Input choice number: ";
	std::cin >> userChoice;
	switch (userChoice)
	{
	case 123456:
	{
		AdministratorUI();
		break;
		system("cls");
		UserInterface();
	}
	case 0:
	{
		exit(EXIT_SUCCESS);
		break;
	}
	case 1:
	{
		
		system("cls");
		std::cout << "\t\t\t\tVacant Rooms\n\n";
		if (RoomOfStatus("Vacant") == false) std::cout << "Sorry There Are No Free Rooms At The Moment.";
		else PrintRooms("Vacant");
		std::cin.get();
		std::cin.get();
		UserInterface();
		break;
	}
	case 2:
	{
		system("cls");
		FillUpRoom();
		std::cin.get();
		std::cin.get();
		UserInterface();
		break;
	}
	case 3:
	{
		system("cls");
		ClearRoom();
		std::cin.get();
		UserInterface();
		break;
	}
	case 4:
	{
		system("cls");
		ReserveRoom();
		std::cin.get(); std::cin.get();
		UserInterface();
		break;
	}
	case 5:
	{
		system("cls");
		CompleteReservation();
		std::cin.get(); std::cin.get();
		UserInterface();
		break;
	}
	case 6:
	{
		system("cls");
		CancelReservation();
		std::cin.get(); std::cin.get();
		UserInterface();
		break;
	}
	case 7:
	{
		system("cls");
		std::cout << "\t\t\t\tActivity List\n\n";
		if (VectorOfActivities.size() == 0) std::cout << "There are no activities currtently available.";
		PrintActivities();
		std::cin.get(); std::cin.get();
		UserInterface();
		break;
	}
	default:
	{
		UserInterface();
	}
	}

}

void AdministratorUI()
{
	system("cls");
	int administratorChoice;
	std::cout << "\t\t\t\tAdministrator Menu\n\n";
	std::cout << "1. Update Database.\n";
	std::cout << "2. Show Database.\n";
	std::cout << "3. Delete An Element From The Database.\n";
	std::cout << "4. Change Room Information.\n";
	std::cout << "5. Display Activities.\n";
	std::cout << "6. Delete Database.\n";
	std::cout << "0. Return To Previous Menu.\n";
	std::cout << "Input operation choice:";
	std::cin >> administratorChoice;
	switch (administratorChoice)
	{
	case 0:
	{
		UserInterface();
	}
	case 1:
	{
		system("cls");
		WriteDatabaseUI();
		std::cin.get(); std::cin.get();
		AdministratorUI();
		break;
	}
	case 2:
	{
		system("cls");
		ShowDatabaseUI();
		std::cin.get(); std::cin.get();
		AdministratorUI();
		break;
	}
	case 3:
	{
		system("cls");
		DeleteRoom();
		std::cin.get(); std::cin.get();
		AdministratorUI();
		break;
	}
	case 4:
	{
		system("cls");
		ChangeRoomInfo();
		std::cin.get(); std::cin.get();
		AdministratorUI();
		break;
	}
	case 5:
	{
		system("cls");
		DispayActivitiesUI();
		std::cin.get(); std::cin.get();
		AdministratorUI();
		break;
	}
	case 6:
	{
		system("cls");
		DeleteDatabaseUI();
		std::cin.get(); std::cin.get();
		AdministratorUI();
		break;
	}
	default:
		system("cls");
		AdministratorUI();
		break;
	}
}

void WriteDatabaseUI()
{
	system("cls");
	std::cout << "\t\t\t\tUpdate Databases\n\n";
	std::cout << "1. Add Rooms.\n";
	std::cout << "2. Add Activities.\n";
	std::cout << "0. Return To Previous Menu.\n";
	std::cout << "State your choice: ";
	int choice; std::cin >> choice;
	switch (choice)
	{
	case 0:
	{
		system("cls");
		AdministratorUI();
		break;
	}
	case 1:
	{
		system("cls");
		std::cout << "\t\t\t\tNew Room Input\n\n";
		NewRoomsInput();
		std::cin.get(); std::cin.get();
		WriteDatabaseUI();
		break;
	}
	case 2:
	{
		system("cls");
		std::cout << "\t\t\t\tNew Activities Input\n\n";
		NewActivitiesInput();
		std::cin.get();
		WriteDatabaseUI();
		break;
	}
	}
}

void ShowDatabaseUI()
{
	system("cls");
	std::cout << "\t\t\t\tShow Database Menu\n\n";
	std::cout << "1. Display Rooms.\n";
	std::cout << "2. Display Activities.\n";
	std::cout << "0. To return to prvious menu.\n";
	std::cout << "State your choice: ";
	int choice; std::cin >> choice;
	switch (choice)
	{
	case 0:
	{
		system("cls");
		AdministratorUI();
		break;
	}
	case 1:
	{
		system("cls");
		std::cout << "\t\t\t\tList Of Rooms\n\n";
		PrintRooms("Administrator");
		std::cin.get();
		std::cin.get();
		ShowDatabaseUI();
		break;
	}
	case 2:
	{
		system("cls");
		std::cout << "\t\t\t\tList Of Activities\n\n";
		PrintActivities();
		std::cin.get(); std::cin.get();
		ShowDatabaseUI();
		break;
	}
	default:
		break;
	}
}

void DeleteDatabaseUI()
{
	system("cls");
	std::cout << "\t\t\t\tDelete Database Menu\n\n";
	std::cout << "1. Delete Rooms Database.\n";
	std::cout << "2. Delete Activities Database.\n";
	std::cout << "0. To return to previous menu.\n";
	std::cout << "State your choice: ";
	int choice; std::cin >> choice;
	switch (choice)
	{
	case 0:
	{
		system("cls");
		AdministratorUI();
		break;
	}
	case 1:
	{
		std::cout << "Are you sure you want to delete the Database? (y/n)";
		char symbol; std::cin >> symbol;
		if (symbol == 'y')
		{
			remove("hotelRoomsInfo.txt");
			VectorOfRooms.clear();
		}
		break;
	}
	case 2:
	{
		std::cout << "Are you sure you want to delete the Database? (y/n)";
		char symbol; std::cin >> symbol;
		if (symbol == 'y')
		{
			remove("activities.txt");
			VectorOfActivities.clear();
		}
		break;
	}
	default:
		break;
	}
	system("cls");
	DatabaseCheck();
	AdministratorUI();
}

void DispayActivitiesUI()
{
	system("cls");
	std::cout << "\t\t\t\tDisplay Activities Menu\n\n";
	std::cout << "1. Display Activities For a Room.\n";
	std::cout << "2. Display Rooms For an Activity.\n";
	std::cout << "0. To return to previous menu.\n";
	std::cout << "State your choice: ";
	int choice; std::cin >> choice;
	switch (choice)
	{
	case 0:
	{
		system("cls");
		AdministratorUI();
		break;
	}
	case 1:
	{
		system("cls");
		std::cout << "\t\t\t\tDisplay Activities Of a Room\n\n";
		DisplayRoomActivities();
		std::cin.get(); std::cin.get();
		DispayActivitiesUI();
		break;
	}
	case 2:
	{
		system("cls");
		std::cout << "\t\t\t\tDisplay All Rooms With the Same Activity\n\n";
		DisplayActivityRooms();
		std::cin.get(); std::cin.get();
		DispayActivitiesUI();
		break;
	}
	default:
		break;
	}
}

// displays the activities of a given room
void DisplayRoomActivities()
{

	if (!RoomOfStatus("Occupied")) std::cout << "There are no occupied rooms\n";
	else
	{
		system("cls");
		PrintRooms("Occupied");
		std::cout << "The Activities Of Witch Room Would You Like To See: ";
		int RoomNumber;
		do
		{
			std::cin >> RoomNumber;
			if (IsContainedInArr(RoomNumber, "Occupied"))
			{
				break;
			}
			std::cout << "Wrong input.\n";
		} while (true);
		std::cout << "The Activities Of Room " << RoomNumber << " are: \n";
		for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() == RoomNumber)
			{
				VectorOfRooms[i].PrintActivities(VectorOfActivities);
				break;
			}
		}
	}
}

// displays the rooms with the specified activity
void DisplayActivityRooms()
{
	PrintActivities();
	std::cout << "Input Activity Number: ";
	unsigned int ActivityNumber; 
	do
	{
		std::cin >> ActivityNumber;
		if (ActivityNumber>0&&ActivityNumber<=VectorOfActivities.size())
		{
			break;
		}
		std::cout << "Wrong input.\n";
	} while (true);
	unsigned int i = 0;
	bool IsPrinted = false;
	for (; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].HasActivity(ActivityNumber))
		{
			std::cout << "The Rooms With The Chosen Activity are: ";
			IsPrinted = true;
			break;
		}
	}
	for (; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].HasActivity(ActivityNumber))
		{
			std::cout << VectorOfRooms[i].GetRoomNumber() << "   ";
		}
	}
	if (!IsPrinted) std::cout << "No rooms with the chosen activity exist.";
	std::cout << "\n";
}

void NewRoomsInput()
{
	std::cout << "How many rooms would you like to add:";
	unsigned int numberOfRooms;
	std::cin >> numberOfRooms;
	Room singleRoomInfo;
	for (unsigned int i = 0; i < numberOfRooms; ++i)
	{
		std::cout << "\n\n";
		singleRoomInfo = SingeRoomInput();
		VectorOfRooms.push_back(singleRoomInfo);
	}
	SortRoomsByNumber();
	SaveRoomsToFile();
}

Room SingeRoomInput()
{
	std::string TempRoom;
	int RoomNumber;
	std::cout << "Input room number:";
	do
	{
		std::cin >> RoomNumber;
		if (!IsContainedInArr(RoomNumber, "IgnoreRoomStatus"))
		{
			break;
		}
		std::cout << "Room is already in DataBase!\n";
	} while (true);
	TempRoom = std::to_string(RoomNumber) + ";";
	std::cout << "Input room status:";
	std::string TempInput;
	std::cin.get(); getline(std::cin, TempInput);
	TempRoom += TempInput + ";";
	std::cout << "Input number of beds in the room:";
	std::cin >> TempInput; TempRoom += TempInput + ";";
	TempRoom += "-1;";
	std::cout << "Input extra features of the room (separate with a comma):";
	std::cin.get(); getline(std::cin, TempInput);
	TempRoom += TempInput + ";";
	std::cout << "Input price:";
	std::cin >> TempInput;
	TempRoom += TempInput + ";;;";
	return Room(TempRoom);
}

void NewActivitiesInput()
{

	std::cout << "How many activities would you like to add: ";
	unsigned int newActivities; std::cin >> newActivities;
	std::cin.get();
	std::string tempString;
	std::ofstream file;
	file.open("activities.txt", std::ios::app);
	for (unsigned int i = 1; i <= newActivities; i++)
	{
		std::cout << "Input activity: ";
		getline(std::cin, tempString);
		VectorOfActivities.push_back(tempString);
		file <<tempString<<"\n";
	}
	file.close();
}




bool IsContainedInArr(const int _RoomNumber,std::string _RoomStatus)
{

	for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].GetRoomNumber() == _RoomNumber)
		{
			if (VectorOfRooms[i].GetRoomStatus() == _RoomStatus|| _RoomStatus=="IgnoreRoomStatus")
			{
				return true;
			}
			return false;
		}
	}
	return false;
}






bool RoomOfStatus(std::string Status)
{
	for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].GetRoomStatus() == Status) return true;
	}
	return false;
}

void PrintActivities() {
	for (unsigned int i = 0; i < VectorOfActivities.size(); ++i)
	{
		std::cout << i + 1 << ". " << VectorOfActivities[i]<<"\n";
	}
}

void DeleteRoom()
{
	if (VectorOfRooms.size() == 0)
	{
		std::cout << "There are no rooms to remove!\n";
		std::cin.get();
		return;
	}
	PrintRooms("Administrator");
	std::cout << "Input the number of the room, that you want to remove:";
	int roomNumber;
	do
	{
		std::cin >> roomNumber;
		if (IsContainedInArr(roomNumber, "IgnoreRoomStatus"))
		{
			break;
		}
		std::cout << "Wrong input!\n";
	} while (true);
	for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].GetRoomNumber() == roomNumber)
		{
			VectorOfRooms.erase(VectorOfRooms.begin()+i);
		}
	}
	std::cout << "Do you wish to delete other rooms? (y/n):";
	char Choice; std::cin >> Choice;
	if (Choice == 'y') DeleteRoom();
	else SaveRoomsToFile();
}

void ChangeRoomInfo()
{
	PrintRooms("Administrator");
	int roomNumber;
	std::cout << "Which Room Information Would You Like To Edit (-1 to cancel):";
	do
	{
		std::cin >> roomNumber;
		if (IsContainedInArr(roomNumber, "IgnoreRoomStatus")||roomNumber == -1)
		{
			break;
		}
		std::cout << "Wrong input!\n";
	} while (true);
	for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].GetRoomNumber() == roomNumber)
		{
			VectorOfRooms[i].ChangeRoomInfo();
		}
	}
	std::cout << "Do you wish to change information of other rooms? (y/n):";
	char Choice; std::cin >> Choice;
	if (Choice == 'y') ChangeRoomInfo();
	else SaveRoomsToFile();
}

void FillUpRoom()
{
	std::cout << "\t\t\t\tFill Up Room\n\n";
	if (RoomOfStatus("Vacant"))
	{
		PrintRooms("Vacant");
		std::cout << "Input Room Number:";
		int number;
		do
		{
			std::cin >> number;
			if (IsContainedInArr(number, "Vacant"))
			{
				break;
			}
			std::cout << "Wrong input!\n";
		} while (true);
		for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() == number)
			{
				VectorOfRooms[i].FillUpRoom(VectorOfActivities, "Occupied");
				break;
			}
		}

		SaveRoomsToFile();
		std::cout << "12341221412412421";
		std::cin.get();
	}
	else std::cout << "Sorry There Are No Free Rooms At The Moment.";
}


void LoadRoomsToMemmory()
{

	std::ifstream file;
	std::string tempString;
	file.open("hotelRoomsInfo.txt", std::ios::in);
	while (!file.eof())
	{
		getline(file, tempString);
		if(tempString !="")VectorOfRooms.push_back(Room(tempString));
	}
	file.close();
}

void LoadActivitiesToMemmory()
{
	std::ifstream file;
	file.open("activities.txt", std::ios::in);
	std::string numberString, tempString;
	while (!file.eof())
	{
		getline(file, tempString);
		if(tempString!="")VectorOfActivities.push_back(tempString);
	}
}
void ClearRoom()
{
	std::cout << "\t\t\t\tClear Out Room\n\n";
	if (RoomOfStatus("Occupied"))
	{	PrintRooms("Occupied");
		int number;
		do
		{
			std::cout << "Input Room Number (-1 to cancel):";
			std::cin >> number;
			if (IsContainedInArr(number, "Occupied")||number==-1)
			{
				break;
			}
			std::cout << "Wrong input.\n";
		} while (true);
		for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() == number)
			{
				VectorOfRooms[i].ClearRoom();
				break;
			}
		}
		std::cout << "Room " << number << " has been cleared successfuly.";
		SaveRoomsToFile();
	}
	else std::cout << "There Are No Occpuied Rooms At The Moment.";
}

void ReserveRoom()
{
	std::cout << "\t\t\t\tReserve Room\n\n";
	if (RoomOfStatus("Vacant"))
	{
		PrintRooms("Vacant");
		std::cout << "Input Room Number:";
		int number;
		do
		{
			std::cin >> number;
			if (IsContainedInArr(number, "Vacant"))
			{
				break;
			}
			std::cout << "Wrong input.\n";
		} while (true);
		for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() == number)
			{
				VectorOfRooms[i].FillUpRoom(VectorOfActivities, "Reserved");
				break;
			}
		}
		SaveRoomsToFile();
	}
	else std::cout << "Sorry There Are No Free Rooms At The Moment.";

}

void CompleteReservation()
{
	std::cout << "\t\t\t\tComplete Reservation\n\n";
	if (RoomOfStatus("Reserved"))
	{
		PrintRooms("Reserved");
		std::cout << "Input Room Number:";
		int number;
		do
		{
			std::cin >> number;
			if (IsContainedInArr(number, "Reserved"))
			{
				break;
			}
			std::cout << "Wrong input.\n";
		} while (true);
		for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() == number)
			{
				VectorOfRooms[i].ChangeStatusOccupied();
				break;
			}
		}
		SaveRoomsToFile();
	}
	else std::cout << "Sorry There Are No Reserved Rooms At The Moment.";

}

void CancelReservation()
{
	std::cout << "\t\t\t\tCancel Reservation\n\n";
	if (RoomOfStatus("Reserved"))
	{
		PrintRooms("Reserved");
		std::cout << "Input Room Number:";
		int number;
		do
		{
			std::cin >> number;
			if (IsContainedInArr(number, "Reserved"))
			{
				break;
			}
			std::cout << "Wrong input.\n";
		} while (true);
		for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() == number)
			{
				VectorOfRooms[i].ClearRoom();
				break;
			}
		}
		SaveRoomsToFile();
	}
	else std::cout << "There Are No Reserved Rooms At The Moment.";
}

void FillUpReservedRoom(int roomNumber)
{
	for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].GetRoomNumber() == roomNumber)
		{
			VectorOfRooms[i].ChangeStatusOccupied();
		}
	}
}




void SaveRoomsToFile()
{
	std::ofstream file;
	file.open("hotelRoomsInfo.txt", std::ios::out);
	for (unsigned int i = 0; i < VectorOfRooms.size(); ++i)
	{
		file <<VectorOfRooms[i]<<"\n";
	}
	file.close();
}

void SortRoomsByNumber()
{
	Room TempRoom;
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (unsigned int i = 0; i < VectorOfRooms.size()-1; ++i)
		{
			if (VectorOfRooms[i].GetRoomNumber() >= VectorOfRooms[i + 1].GetRoomNumber())
			{
				TempRoom = VectorOfRooms[i];
				VectorOfRooms[i] = VectorOfRooms[i + 1];
				VectorOfRooms[i + 1] = TempRoom;
				flag = true;
			}
		}
	}
}

void PrintRooms(std::string _Status)
{
	for (int i = 0; i < VectorOfRooms.size(); ++i)
	{
		if (VectorOfRooms[i].GetRoomStatus() == _Status|| _Status== "Administrator")
		{
			VectorOfRooms[i].DisplayRoom(_Status);
			std::cout << "\n";
		}
	}
}


void AdministratorStackOverflowPreventer()
{
	AdministratorUI();
}
