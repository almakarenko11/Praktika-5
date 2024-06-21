#include <iostream>
#include <memory>
#include <string>


class Ticket {
public:
    virtual ~Ticket() = default;
    virtual std::string getType() const = 0;
    virtual double getPrice() const = 0;
};

class Parking {
public:
    virtual ~Parking() = default;
    virtual std::string getDescription() const = 0;
};

class LoungeAccess {
public:
    virtual ~LoungeAccess() = default;
    virtual std::string getDescription() const = 0;
};


class RegularTicket : public Ticket {
public:
    std::string getType() const override {
        return "Regular Ticket";
    }

    double getPrice() const override {
        return 50.0;
    }
};

class VIPTicket : public Ticket {
public:
    std::string getType() const override {
        return "VIP Ticket";
    }

    double getPrice() const override {
        return 200.0;
    }
};

class RegularParking : public Parking {
public:
    std::string getDescription() const override {
        return "Regular Parking";
    }
};

class VIPParking : public Parking {
public:
    std::string getDescription() const override {
        return "VIP Parking";
    }
};

class RegularLoungeAccess : public LoungeAccess {
public:
    std::string getDescription() const override {
        return "Regular Lounge Access";
    }
};

class VIPLoungeAccess : public LoungeAccess {
public:
    std::string getDescription() const override {
        return "VIP Lounge Access";
    }
};



class TicketFactory {
public:
    virtual ~TicketFactory() = default;
    virtual std::unique_ptr<Ticket> createTicket() const = 0;
    virtual std::unique_ptr<Parking> createParking() const = 0;
    virtual std::unique_ptr<LoungeAccess> createLoungeAccess() const = 0;
};



class RegularTicketFactory : public TicketFactory {
public:
    std::unique_ptr<Ticket> createTicket() const override {
        return std::make_unique<RegularTicket>();
    }

    std::unique_ptr<Parking> createParking() const override {
        return std::make_unique<RegularParking>();
    }

    std::unique_ptr<LoungeAccess> createLoungeAccess() const override {
        return std::make_unique<RegularLoungeAccess>();
    }
};

class VIPTicketFactory : public TicketFactory {
public:
    std::unique_ptr<Ticket> createTicket() const override {
        return std::make_unique<VIPTicket>();
    }

    std::unique_ptr<Parking> createParking() const override {
        return std::make_unique<VIPParking>();
    }

    std::unique_ptr<LoungeAccess> createLoungeAccess() const override {
        return std::make_unique<VIPLoungeAccess>();
    }
};



void printTicketDetails(const TicketFactory& factory) {
    auto ticket = factory.createTicket();
    auto parking = factory.createParking();
    auto loungeAccess = factory.createLoungeAccess();

    std::cout << "Ticket Type: " << ticket->getType() << ", Price: $" << ticket->getPrice() << std::endl;
    std::cout << "Parking: " << parking->getDescription() << std::endl;
    std::cout << "Lounge Access: " << loungeAccess->getDescription() << std::endl;
}



int main() {
    std::cout << "Regular Ticket Details:" << std::endl;
    RegularTicketFactory regularFactory;
    printTicketDetails(regularFactory);

    std::cout << "\nVIP Ticket Details:" << std::endl;
    VIPTicketFactory vipFactory;
    printTicketDetails(vipFactory);

    return 0;
}