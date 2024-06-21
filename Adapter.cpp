#include <iostream>
#include <string>


class PaymentSystem {
public:
    virtual void pay(const std::string& ticketType, double amount) = 0;
};


class LegacyPaymentSystem {
public:
    void makePayment(const std::string& details) {
        std::cout << "Processing payment through Legacy System: " << details << std::endl;
    }
};


class PaymentAdapter : public PaymentSystem {
public:
    PaymentAdapter(LegacyPaymentSystem& legacySystem) : legacySystem(legacySystem) {}

    void pay(const std::string& ticketType, double amount) override {
        std::string details = "Ticket Type: " + ticketType + ", Amount: $" + std::to_string(amount);
        legacySystem.makePayment(details);
    }

private:
    LegacyPaymentSystem& legacySystem;
};

class Ticket {
public:
    Ticket(const std::string& type, double price, PaymentSystem& paymentSystem)
        : type(type), price(price), paymentSystem(paymentSystem) {}

    void purchase() {
        std::cout << "Purchasing " << type << " for $" << price << std::endl;
        paymentSystem.pay(type, price);
    }

private:
    std::string type;
    double price;
    PaymentSystem& paymentSystem;
};

int main() {
    LegacyPaymentSystem legacySystem;
    PaymentAdapter adapter(legacySystem);

    Ticket regularTicket("Regular Ticket", 50.0, adapter);
    Ticket vipTicket("VIP Ticket", 200.0, adapter);

    regularTicket.purchase();
    vipTicket.purchase();

    return 0;
}