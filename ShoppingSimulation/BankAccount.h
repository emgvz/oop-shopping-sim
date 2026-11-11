#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H


class BankAccount
{
public:
    enum Type
    {
        chequing,
        savings,
    };
    
    BankAccount(Type accountType, double balance);
    
    double getBalance() const;
    void setBalance(double newBalance);
    
    void printBalance() const;
    
    Type getAccountType() const { return m_accountType; }
    
private:
    Type m_accountType {};
    double m_balance {};
};


#endif