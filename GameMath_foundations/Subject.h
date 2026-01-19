#pragma once
#include <vector>
#include <string>
#include "IObserver.h"

class Subject {
public:
	void AddObserver(IObserver* observer) {
		m_Observers.push_back(observer);
	}


	void Notify(const std::string& eventName, int parameter) {

		for (IObserver* observer : m_Observers) {
			observer->OnNotify(eventName, parameter);
		}

	}


private:
	
	std::vector<IObserver*> m_Observers;

};
