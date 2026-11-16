#pragma once

#include <string>
#include <string_view>

class Product
{
	// enum type school, etc
public:
	Product() = default;

	enum Type
	{
		Electronics,
		Gaming,
		School,
		Food,
		Clothing,
		Medical
	};

	enum Status
	{
		InStock,
		OutOfStock,
/*		Pending,*/
	};

	Product(Type productType,
		std::string_view productName,
		double productPrice,
		int productQuantity,
		Status productStatus);

private:
	int m_pID{};
	static inline int s_idIdentifier{ 1 };
	std::string m_pName{"???"};
	Type m_type{};
	double m_price{0.0};
	int m_quantity{ 0 };
	Status m_status{};

public:
	// setters

	void updateStatus(Status status) { m_status = status; }
	void updateQuantity(int qty) { m_quantity = qty; }

	// getters

	int getPID() const { return m_pID; }
	std::string_view getPName() const { return m_pName; }
	Type getPType() const { return m_type; }
	double getPrice() const { return m_price; }
	int getQuantity() const { return m_quantity; }
	Status getPStatus() const { return m_status; }

	void printProducts() const;
};

inline Product::Product(Type pType,
	std::string_view pName,
	double pPrice,
	int pQuantity,
	Status pStatus) :

	m_pID(s_idIdentifier++),
	m_pName(pName),
	m_type(pType),
	m_price(pPrice),
	m_quantity{ pQuantity },
	m_status{ pStatus }

{}