#pragma once
#include <string>

class IObserver {
public:
	virtual ~IObserver(){}

	virtual void OnNotify(const std::string& eventName,int parameter) = 0;

};

