#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<iomanip>

class Room {
private:
	int m_RoomNumber = -1;
	std::string m_RoomStatus = "N/A";
	int m_NumberOfBeds = -1;
	int m_OccupiedBeds = -1;
	std::string m_ExtraFeatures = "N/A";
	double m_RoomPrice = -1;
	std::string m_RoomOccupants = "N/A";
	std::string m_CurrentOcupation = "N/A";
	bool m_Activities[50];
	int m_NumberOfActivities = -1;
public:
	Room();
	Room(const std::string&);

	
	// mutators
	void ChangeStatusOccupied() { m_RoomStatus = "Occupied"; }
	void ClearRoom();
	void FillUpRoom(std::vector<std::string>&,std::string);

	// selectors
	int GetRoomNumber()const { return m_RoomNumber; };
	std::string GetRoomStatus()const { return m_RoomStatus; }

	// dont know
	bool HasActivity(const int)const;
	void DisplayRoom(std::string)const;
	void ChangeRoomInfo();
	

	// for file output

	// класът се казва Room и получавам следната грешка
	// искам да не пиша селектор за всяко поле
	// а просто с приятелска функция да получа достъп до 
	// член функциите на класа. Plz help
	friend std::ofstream& operator<<(std::ofstream&,Room&);

	// printers
	void PrintActivities(std::vector<std::string>&)const;

};

bool CorrectDate(std::string);