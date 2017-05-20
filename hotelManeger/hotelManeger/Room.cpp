#include "Room.h"

Room::Room() {
	for (int i = 0; i < 50; ++i)
	{
		m_Activities[i] = false;
	}
}

Room::Room(const std::string& ToConvert)
{
	if (ToConvert == "") std::cout << "EmptyString";
	else {
		for (int i = 0; i < 50; ++i)
		{
			m_Activities[i] = false;
		}
		int i = 0;
		std::string tempString = "";
		std::string::size_type sz;			//alias of size_type
		while (ToConvert[i] != ';')			// going through the string
		{									 // and separating the Room class parts
			tempString += ToConvert[i];		// the different parts are seperated by ;
			++i;
		}
		m_RoomNumber = std::stoi(tempString, &sz); // converting string to int
		++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		m_RoomStatus = tempString;
		++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		m_NumberOfBeds = std::stoi(tempString, &sz); // converting string to int
		++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		m_OccupiedBeds = std::stoi(tempString, &sz); // converting string to int
		++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		m_ExtraFeatures = tempString; ++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		m_RoomPrice = std::stod(tempString, &sz); // converting string to double
		++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		m_RoomOccupants = tempString;
		++i;
		tempString = "";
		while (ToConvert[i] != ';')
		{
			tempString += ToConvert[i];
			++i;
		}
		if (tempString == "") m_CurrentOcupation = "N/A";
		else m_CurrentOcupation = tempString;
		++i;
		tempString = "";
		int _NumberOfActivities = 0;
		while (i < ToConvert.size())
		{
			tempString += ToConvert[i];
			if (ToConvert[i] == ',') ++_NumberOfActivities;
			++i;
		}
		m_NumberOfActivities = _NumberOfActivities;
		std::string numberString = "";
		for (int j = 0, i = 0; i < m_NumberOfActivities; ++j)
		{
			if (tempString[j] == ',')
			{
				int activity = std::stoi(numberString, &sz);
				m_Activities[activity-1] = true;
				++i;
				++j;
				numberString = "";
			}
			numberString += tempString[j];
		}
	}
}

void Room::ClearRoom()
{
	m_RoomStatus = "Vacant";
	m_OccupiedBeds = -1;
	m_RoomOccupants = "N\A";
	m_CurrentOcupation = "N\A";
	for (int j = 0; j < 50; ++j)
	{
		m_Activities[j] = false;
	}
	m_NumberOfActivities = 0;
}

void Room::FillUpRoom(std::vector<std::string>& VectorOfActivities,std::string _Status)
{
	m_RoomStatus = _Status;
	do
	{
		std::cout << "Input Number Of Occupied beds:";
		std::cin >> m_OccupiedBeds;
		if (m_OccupiedBeds >= 1 && m_OccupiedBeds <= m_NumberOfBeds)
		{
			break;
		}
		std::cout << "Wrong input. \n";
	} while (true);
	 std::cin.get();
	std::cout << "Input Occupants Name:"; std::getline(std::cin, m_RoomOccupants);
	std::string tempString;
	do
	{
		std::cout << "Occupation Date from(format DD.MM.YYYY): ";
		getline(std::cin, tempString);
	} while (!CorrectDate(tempString));
	m_CurrentOcupation = tempString;
	do
	{
		std::cout << "Leave Date(format DD.MM.YYYY): ";
		getline(std::cin, tempString);
	} while (!CorrectDate(tempString));
	m_CurrentOcupation += "-" + tempString;
	if (VectorOfActivities.size() != 0)
	{
		std::cout << "Choose activities from the folowing list: \n";
		for (int i = 0; i < VectorOfActivities.size(); ++i) std::cout << i+1 << ". " << VectorOfActivities[i] << "\n";
		std::cout << "Input number of chosen activities: ";
		std::cin >> m_NumberOfActivities;
		int activityNumber;
		for (int i = 0; i < m_NumberOfActivities; ++i)
		{
			std::cin >> activityNumber;
			m_Activities[activityNumber - 1] = true;
		}
	}
}

bool Room::HasActivity(const int ActivityNumber) const
{
	if (m_Activities[ActivityNumber - 1] == true) return true;
	return false;
}

void Room::DisplayRoom(std::string AccessType) const
{
	std::cout << std::setw(5) << "#" << std::setw(10) << "Status" << std::setw(8) << "Beds";
	if (AccessType == "Administrator")  std::cout << std::setw(13) << "Taken Beds";
	std::cout<<std::setw(13) << "Ocuppants";
	std::cout << std::setw(22) << "Extra Features" << std::setw(9) << "Price  ";
	std::cout << "\n";
	std::cout << std::setw(5) << m_RoomNumber << std::setw(10) << m_RoomStatus
		<< std::setw(8) << m_NumberOfBeds;
	if (AccessType == "Administrator") std::cout << std::setw(13) << m_OccupiedBeds;
	std::cout<< std::setw(13) << m_RoomOccupants;
	std::cout << std::setw(22) << m_ExtraFeatures
		<< std::setw(7) << m_RoomPrice;
	if (AccessType == "Administrator") {
		std::cout <<"\n\n" <<std::setw(22) << "Current Ocupation\n";
		std::cout << std::setw(21) << m_CurrentOcupation;
	}
	std::cout << "\n";
}

void Room::ChangeRoomInfo()
{
	std::cout << "Change room number from " << m_RoomNumber << " to ";
	std::cin >> m_RoomNumber;
	std::cout << "Change beds from " << m_NumberOfBeds << " to ";
	std::cin >> m_NumberOfBeds;
	std::cout << "Input new extra features:";
	std::cin.get();
	getline(std::cin,m_ExtraFeatures);
	std::cout << "Change room price from " << m_RoomPrice << " to ";
	std::cin >> m_RoomPrice;
}

std::ofstream& operator<<(std::ofstream& os,Room& _Room)
{

	os << (std::string)(
		std::to_string(_Room.m_RoomNumber) +
		";" + _Room.m_RoomStatus +
		";" + std::to_string(_Room.m_NumberOfBeds) +
		";" + std::to_string(_Room.m_OccupiedBeds) +
		";" + _Room.m_ExtraFeatures +
		";" + std::to_string(_Room.m_RoomPrice) +
		";" + _Room.m_RoomOccupants +
		";" + _Room.m_CurrentOcupation +";");
	for (int i = 0; i < 50; ++i)
	{
		if (_Room.m_Activities[i] == true)
		{
			os << std::to_string(i+1) + ",";
		}
	}
	return os;
}

void Room::PrintActivities(std::vector<std::string>& VectorOfActivities)const
{
	for (int i = 0; i < VectorOfActivities.size() ; ++i)
	{
		if (m_Activities[i] == true) std::cout << i+1 << ". " << VectorOfActivities[i]<<"\n";
	}
}


bool CorrectDate(std::string date)
{
	int day = 10 * (date[0] - '0') + date[1] - '0';
	int month = 10 * (date[3] - '0') + date[4] - '0'; //std::cout << date[2] << date[3] << date[5] << date[6] << date[7] << date[8];
	int year = 1000 * (date[6] - '0') + 100 * (date[7] - '0') + 10 * (date[8] - '0') + date[9] - '0';
	switch (month)
	{
	case 1: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 3: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
	}
	case 5: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 7: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 8: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 10: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 12: {
		if (day > 31 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 4: {
		if (day > 30 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 6: {
		if (day > 30 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 9: {
		if (day > 30 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 11: {
		if (day > 30 || day < 1) {
			std::cout << "Input Correct Information!!!\n";
			return false;
		}
		break;
	}
	case 2: {
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		{
			if (day > 29 || day < 1) {
				std::cout << "Input Correct Information!!!\n";
				return false;
			}
		}
		else {
			if (day > 28 || day < 1) {
				std::cout << "Input Correct Information!!!\n";
				return false;
			}
		}
		break;
	}
	default: {
		std::cout << "Input Correct Information!!!\n";
		return false;;
	}
	}
	return true;
}