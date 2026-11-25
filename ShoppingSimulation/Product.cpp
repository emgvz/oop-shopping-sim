#include "Product.h"
#include <iostream>
#include <iomanip>
#include <format>

std::string_view convertTypeToStr(Product::Type type)
{
	switch (type)
	{
	case Product::Electronics:
		return "Electronics";

	case Product::Gaming:
		return "Gaming";

	case Product::School:
		return "School";
	
	case Product::Food:
		return "Food";

	case Product::Clothing:
		return "Clothing";

	case Product::Medical:
		return "Medical";
	}
}

std::string_view convertAvailabilityToStr(Product::Status status)
{
	switch (status)
	{
	case Product::InStock:
		return "In Stock";

	case Product::OutOfStock:
		return "Out Of Stock";
	}
}

void Product::printProducts() const
{	
	std::cout << std::left << std::setw(10) << getPID();
	std::cout << std::setw(20) << getPName();
	std::cout << std::setw(15) << convertTypeToStr(getPType());
	std::cout << std::setw(15) << std::format("${}",getPrice());
	std::cout << std::right << std::setw(15) << getQuantity();
	std::cout << std::right << std::setw(15) << convertAvailabilityToStr(getPStatus()) << '\n';
}

void Product::printProductsCust() const
{
	double totalCost{ getPrice() * getQuantity() };

	std::cout << std::left << std::setw(10) << getPID();
	std::cout << std::setw(20) << getPName();
	std::cout << std::setw(15) << convertTypeToStr(getPType());
	std::cout << std::setw(15) << std::format("${}", getPrice());
	std::cout << std::right << std::setw(15) << getQuantity();
	std::cout << std::right << std::setw(15) << std::format("${}", totalCost) << '\n';
}