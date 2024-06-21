#include <iostream>
#include <memory>
#include <string>
#include <vector>


class Ticket {
public:
    void setType(const std::string& type) {
        this->type = type;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void addFeature(const std::string& feature) {
        features.push_back(feature);
    }

    void showTicket() const {
        std::cout << "Ticket Type: " << type << "\n";
        std::cout << "Price: $" << price << "\n";
        std::cout << "Features:\n";
        for (const auto& feature : features) {
            std::cout << " - " << feature << "\n";
        }
        std::cout << std::endl;
    }

private:
    std::string type;
    double price;
    std::vector<std::string> features;
};


class TicketBuilder {
public:
    virtual ~TicketBuilder() = default;
    virtual void buildType() = 0;
    virtual void buildPrice() = 0;
    virtual void buildFeatures() = 0;
    std::unique_ptr<Ticket> getTicket() {
        return std::move(ticket);
    }

protected:
    std::unique_ptr<Ticket> ticket;
};


class RegularTicketBuilder : public TicketBuilder {
public:
    RegularTicketBuilder() {
        ticket = std::make_unique<Ticket>();
    }

    void buildType() override {
        ticket->setType("Regular Ticket");
    }

    void buildPrice() override {
        ticket->setPrice(50.0);
    }

    void buildFeatures() override {
        ticket->addFeature("Standard Seat");
        ticket->addFeature("Access to Regular Parking");
    }
};


class VIPTicketBuilder : public TicketBuilder {
public:
    VIPTicketBuilder() {
        ticket = std::make_unique<Ticket>();
    }

    void buildType() override {
        ticket->setType("VIP Ticket");
    }

    void buildPrice() override {
        ticket->setPrice(200.0);
    }

    void buildFeatures() override {
        ticket->addFeature("VIP Seat");
        ticket->addFeature("Access to VIP Parking");
        ticket->addFeature("Access to VIP Lounge");
        ticket->addFeature("Free Drinks");
    }
};


class TicketDirector {
public:
    void setBuilder(TicketBuilder* builder) {
        this->builder = builder;
    }

    void constructTicket() {
        builder->buildType();
        builder->buildPrice();
        builder->buildFeatures();
    }

private:
    TicketBuilder* builder;
};


int main() {
    TicketDirector director;

    RegularTicketBuilder regularBuilder;
    VIPTicketBuilder vipBuilder;

    director.setBuilder(&regularBuilder);
    director.constructTicket();
    std::unique_ptr<Ticket> regularTicket = regularBuilder.getTicket();
    regularTicket->showTicket();

    director.setBuilder(&vipBuilder);
    director.constructTicket();
    std::unique_ptr<Ticket> vipTicket = vipBuilder.getTicket();
    vipTicket->showTicket();

    return 0;
}