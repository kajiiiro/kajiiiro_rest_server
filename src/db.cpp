#include "db.h"

namespace kajiiiro
{

Db::Db() : mpKeyValue(new std::map< std::string, std::tuple<std::string, int, double> >())
{

}

Db::~Db()
{
	delete mpKeyValue;
}

void Db::addValue(const std::string &strKey, const std::string &strValue)
{
	this->addValue(strKey, strValue, int(0), double(0.0));
}

void Db::addValue(const std::string &strKey, const int &iValue)
{
	this->addValue(strKey, std::string(""), iValue, double(0.0));
}

void Db::addValue(const std::string &strKey, const double &dValue)
{
	this->addValue(strKey, std::string(""), int(0), dValue);
}

bool Db::getValue(const std::string &strKey, std::string &strValue) const
{
	auto it = mpKeyValue->find(strKey);
	if (it == mpKeyValue->end())
		return false;
	strValue = std::get<0>(it->second);
	return true;
}
bool Db::getValue(const std::string &strKey, int &iValue) const
{
	auto it = mpKeyValue->find(strKey);
	if (it == mpKeyValue->end())
		return false;
	iValue = std::get<1>(it->second);
	return true;
}
bool Db::getValue(const std::string &strKey, double &dValue) const
{
	auto it = mpKeyValue->find(strKey);
	if (it == mpKeyValue->end())
		return false;
	dValue = std::get<2>(it->second);
	return true;
}

void Db::addValue(const std::string &strKey
			, const std::string &strValue
			, const int &iValue
			, const double &dValue)
{
	mpKeyValue->insert(std::pair< std::string, std::tuple<std::string, int, double> >(
						strKey,
						std::make_tuple(strValue, iValue, dValue)
	));
}

}; // namespace
