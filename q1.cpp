#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;

template <class T>
class queue {
	class node {
	public:
		T data;
		node* next;
		node() {
			data = 0;
			next = nullptr;
		}
	};
	node* front;
	node* rear;
public:
	queue() {
		front = nullptr;
		rear = nullptr;
	}

	int size() {
		int count = 0;
		queue <T> q2;
		while (isEmpty() != true) {
			q2.enqueue(getFront());
			dequeue();
			count++;
		}
		while (q2.isEmpty() != true) {
			enqueue(q2.getFront());
			q2.dequeue();
		}
		return count;
	}

	T getFront() {
		if (front != nullptr) {
			return front->data;
		}
		else {
			cout << "queue empty" << endl;
			return 0;
		}
	}

	void enqueue(T const e) {
		node* temp = new node;
		if (temp != NULL) {
			temp->data = e;
			if (rear != nullptr) {
				rear->next = temp;
			}
			rear = temp;
			if (front == nullptr) {
				front = temp;
			}
		}
		else cout << "NO space" << endl;
	}

	void dequeue() {
		node* temp = new node;
		if (front != nullptr) {
			temp = front;
			front = front->next;
			delete temp;

		}
		if (front == nullptr) {
			rear = nullptr;
			//cout << "empty queue" << endl;
		}
	}

	bool isEmpty() {
		if (front == nullptr) {
			return true;
		}
		else return false;
	}

	void clear() {
		while (isEmpty() != true) {
			dequeue();
		}
	}

	void print() {
		queue <T> q2;
		while (isEmpty() != true) {
			q2.enqueue(getFront());
			cout << getFront() << " ";
			dequeue();
		}
		while (q2.isEmpty() != true) {
			enqueue(q2.getFront());
			q2.dequeue();
		}
		cout << endl;
	}

	void Display() {
		sf::RenderWindow window(sf::VideoMode(512, 512), "SFML", sf::Style::Close | sf::Style::Resize);
		sf::CircleShape player(100.f);
		player.setFillColor(sf::Color::Transparent);
		player.setOutlineColor(sf::Color::Yellow);
		player.setOutlineThickness(5);

		sf::Font font;
		if (!font.loadFromFile("font/G_ari_bd.TTF")) {
			// Handle font loading error.
			cout << "Error: Font not loaded." << endl;
		}
		float x = window.getSize().x / 2.0f;
		float y = window.getSize().y / 2.0f;
		if (size() != 1) {
			player.setPosition(x - player.getRadius() + 0.5, y - player.getRadius() + 2.5);
		}
		else {
			player.setPosition(x - player.getRadius() + 90, y - player.getRadius() + 7);
		}


		while (window.isOpen()) {
			sf::Event evnt;
			while (window.pollEvent(evnt)) {
				if (evnt.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.clear();
			window.draw(player);
			for (int j = 1; j <= size(); ++j) {
				sf::Text text;
				text.setString(std::to_string(getFront()));
				enqueue(getFront());
				dequeue();
				text.setFont(font);
				if (size() != 1) {
					text.setCharacterSize(20);
				}
				else text.setCharacterSize(50);

				text.setFillColor(sf::Color::White);

				// Calculate the position of the number on the circle.
				float angle = j * (2 * M_PI / size());
				float textX = x + 90.f * std::cos(angle);
				float textY = y + 90.f * std::sin(angle);

				// Adjust the position for centering.
				float xOffset = text.getLocalBounds().width / 2.0;
				float yOffset = text.getLocalBounds().height / 2.0;

				text.setPosition(textX - xOffset, textY - yOffset);
				window.draw(text);
			}

			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
				return;
			}

		}
	}

	void josephProblem(int N, int k) {
		
		int s = 1;
		cout << "Enter the starting point: ";
		cin >> s;
		int j = 1;
		cout << "Starting from: " << s << endl;
		Display();
		while (j != s) {
			enqueue(front->data);
			dequeue();
			j++;
		}
		int i = 1;
		while (size() != 1) {
			if (i != k) {
				int t = getFront();
				enqueue(t);
				dequeue();
				i++;
			}
			else {
				dequeue();
				Display();

				i = 1;

			}
		}

	}
};


int main() {
	queue <int> q1;
	int N, k;
	cout << "Enter the number of people: ";
	cin >> N;
	for (int i = 1; i <= N; i++) {
		q1.enqueue(i);
	}
	cout << "Enter the value of k: ";
	cin >> k;
	q1.josephProblem(N, k);
	cout << "SURVIVOR: ";
	q1.print();
	return 0;
}