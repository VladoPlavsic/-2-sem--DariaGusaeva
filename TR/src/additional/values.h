#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Values
{
	std::string m_MiddleName;
	std::string m_Name;
	std::string m_LastName;
	std::string m_Date;
	std::string m_Death;
	std::string m_Place;

	bool m_Printed = false;

	Values() {}
	Values(Values* values)
	{
		m_MiddleName = values->m_MiddleName;
		m_Name = values->m_Name;
		m_LastName = values->m_LastName;
		m_Date = values->m_Date;
		if (!values->m_Death.empty())
			m_Death = values->m_Death;
		if (!values->m_Place.empty())
			m_Place = values->m_Place;
	}
};