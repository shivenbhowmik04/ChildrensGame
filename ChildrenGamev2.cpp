#include "ChildrenGamev2.h"
#include <cmath>
#include <iostream>

//class definitions for childrendata
ChildrenData::ChildrenData(double x, double y) {
	this->x = x;
	this->y = y;
	next = nullptr;
}


ChildrenData::~ChildrenData() {

}

void ChildrenData::setX(double xVal) { x = xVal; }
void ChildrenData::setY(double yVal) { y = yVal; }

double ChildrenData::getXValue() { return x; }
double ChildrenData::getYValue() { return y; }


double ChildrenData::distance() {
	return std::sqrt(std::pow(this->getXValue(), 2) + std::pow(this->getYValue(), 2));
}

void ChildrenData::setNext(ChildrenData* nextNode) { next = nextNode; }
ChildrenData* ChildrenData::getNext() { return next; }


//class definitions for linked list
Game::Game() {
	head = nullptr;
}

Game::~Game() {
	while (head != nullptr) {
		ChildrenData* temp = head->getNext();
		delete head;
		head = temp;
	}
}

void Game::addChild(double x, double y){
	ChildrenData* newChild = new ChildrenData(x, y);
	newChild->setNext(nullptr);
	if (head == nullptr) {
		head = newChild;
	}
	else{
		ChildrenData* iterator = head;
		while (iterator->getNext() != nullptr) {
			iterator = iterator->getNext();
		}
		iterator->setNext(newChild);
	}
}

void Game::removeChild(ChildrenData* child) {//removes a child from the list based on the memory address
	
	ChildrenData* current = head;
	ChildrenData* previous = nullptr;

	while (current != nullptr){
		if (current == child) {
			if (previous != nullptr) {
				previous->setNext(current->getNext());
			}
			if (current == head && current->getNext() == nullptr) {
				head = nullptr;
			}
			else if(current == head){
				head = head->getNext();
			}
				delete child;
				break;
			
		}
		previous = current;
		current = current->getNext();
	}
}

void Game::time(double t){
	ChildrenData* current = head;
	ChildrenData* temp = nullptr;

	while (current != nullptr) {
		double x = current->getXValue();
		double y = current->getYValue();
		if (t < 0 && std::sqrt(std::pow(x, 2) + std::pow(y, 2)) < 1.0) {//add std::pow to (y, 2) here
			temp = current->getNext();
			this->removeChild(current);
			current = temp;
		}

		else if (t >= 0) {
			double dx = t * cos(atan2(y, x));
			double dy = t * sin(atan2(y, x));
			current->setX(current->getXValue() - dx); //changed from head->getXValue() to current->getXValue
			current->setY(current->getYValue() - dy); //changed from head->getYValue() to current->getYValue

			if ((current->getXValue() <= 0 || current->getYValue() <= 0)) {//this conditional may be the issue 
				temp = current->getNext();
				this->removeChild(current);
				current = temp;
			}
			else {
				current = current->getNext();
			}
		}
		else {
			current = current->getNext();
		}
	}
	std::cout << "number of children still playing: " << this->numChildren() << std::endl;
}

int Game::numChildren(){
	int count = 0;
	ChildrenData* current = head;

	while (current != nullptr) {
		count++;
		current = current->getNext();
	}
	return count;
}


bool Game::input(){
	std::string command;
	std::cin >> command;
	
	if (command == "SPAWN") {
		double x, y;
		std::cin >> x >> y;
		if (x > 0 && y > 0) {
			this->addChild(x, y);
			std::cout << "success" << std::endl;
		}
		else {
			std::cout << "failure" << std::endl;
		}
	}

	else if (command == "TIME") {
		double t{};
		std::cin >> t;
		this->time(t);
	}

	else if (command == "NUM") {
		std::cout << "Number of children still playing: " << this->numChildren() << std::endl;
	}

	else if (command == "PRT") {
		double D;
		std::cin >> D;

		ChildrenData* current = head;
		bool isChildFound = false;

		while (current != nullptr) {
			if (current->distance() < D) {
				std::cout << current->getXValue() << " " << current->getYValue() << " ";
				//std::cout << std::endl;
				isChildFound = true;
			}
			current = current->getNext();
		}
		//std::cout << std::endl;
		if (!isChildFound) { 
			std::cout << "no children within distance";
		}
		std::cout << std::endl;
	}

	else if (command == "OVER") {
		if (this->numChildren() == 0) {
			//std::cout << std::endl;
			std::cout << "the wolf wins" << std::endl;
			return false;
		}
		else {
			//std::cout << std::endl;
			std::cout << "the players win" << std::endl;
			return false;
		}
	}
	return true;
}