#include <iostream>
#include <string>
#include <memory>


class Mediator {
public:
    virtual void notify(const std::string& sender, const std::string& event) = 0;
};


class TicketBookingSystem {
public:
    TicketBookingSystem(Mediator& mediator) : mediator(mediator) {}

    void bookTicket(const std::string& ticketType) {
        std::cout << "Booking " << ticketType << "..." << std::endl;
        mediator.notify("TicketBookingSystem", "TicketBooked");
    }

private:
    Mediator& mediator;
};


class PaymentSystem {
public:
    PaymentSystem(Mediator& mediator) : mediator(mediator) {}

    void processPayment(const std::string& ticketType, double amount) {
        std::cout << "Processing payment for " << ticketType << " of amount $" << amount << "..." << std::endl;
        mediator.notify("PaymentSystem", "PaymentProcessed");
    }

private:
    Mediator& mediator;
};


class NotificationSystem {
public:
    void sendNotification(const std::string& message) {
        std::cout << "Sending notification: " << message << std::endl;
    }
};


class TicketMediator : public Mediator {
public:
    void setBookingSystem(std::shared_ptr<TicketBookingSystem> bookingSystem) {
        this->bookingSystem = bookingSystem;
    }

    void setPaymentSystem(std::shared_ptr<PaymentSystem> paymentSystem) {
        this->paymentSystem = paymentSystem;
    }

    void setNotificationSystem(std::shared_ptr<NotificationSystem> notificationSystem) {
        this->notificationSystem = notificationSystem;
    }

    void notify(const std::string& sender, const std::string& event) override {
        if (event == "TicketBooked") {
            paymentSystem->processPayment("Regular Ticket", 50.0);
        }
        else if (event == "PaymentProcessed") {
            notificationSystem->sendNotification("Your ticket has been successfully booked and paid for.");
        }
    }

private:
    std::shared_ptr<TicketBookingSystem> bookingSystem;
    std::shared_ptr<PaymentSystem> paymentSystem;
    std::shared_ptr<NotificationSystem> notificationSystem;
};


int main() {
    auto mediator = std::make_shared<TicketMediator>();
    auto bookingSystem = std::make_shared<TicketBookingSystem>(*mediator);
    auto paymentSystem = std::make_shared<PaymentSystem>(*mediator);
    auto notificationSystem = std::make_shared<NotificationSystem>();

    mediator->setBookingSystem(bookingSystem);
    mediator->setPaymentSystem(paymentSystem);
    mediator->setNotificationSystem(notificationSystem);

    bookingSystem->bookTicket("Regular Ticket");

    return 0;
}