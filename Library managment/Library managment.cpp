#include <iostream>
#include <string>
#include <vector>

class Book {
public:
	Book(const std::string& title, const std::string& author)
		: title(title), author(author) {}
	
	void display() const {
		std::cout << "Title: " << title
			<< ", Author: " << author << std::endl;
	}
private:
	std::string title;
	std::string author;
};

class IBookRepository
{
public:
	virtual void save(const Book& book) = 0;

	virtual ~IBookRepository() = default;
};

class INotificationService {
public:
	virtual void sendNotification(const Book& book) = 0;

	virtual ~INotificationService() = default;
};

class DatabaseBookRepository : public IBookRepository {
public:
	void save(const Book& book) override {
		std::cout << "Saving book to database..." << std::endl;
	}
};

class EmailNotificationService : public INotificationService {
public: 
	void sendNotification(const Book& book) override {
		std::cout << "Sending email notification about the new book..." << std::endl;
	}
};

class Library{
public:
	explicit Library(IBookRepository& bookRepository, INotificationService& notificationService)
		: bookRepository(bookRepository), notificationService(notificationService) {
	}

	void addBook(const Book& book) {
		books.push_back(book);
		bookRepository.save(book);
		notificationService.sendNotification(book);
	}

	void displayBooks() {
		for (const auto& book:books) {
			book.display();
		}
	}

private:
	IBookRepository& bookRepository;
	INotificationService& notificationService;
	
	std::vector<Book> books;
};

int main() {
	DatabaseBookRepository database;
	EmailNotificationService email;

	Library library(database, email);

	Book book1("The Catcher in the Rye", "J.D. Salinger");
	Book book2("To Kill a Mockingbird", "Harper Lee");

	library.addBook(book1);
	library.addBook(book2);

	library.displayBooks();
	
	return 0;
}