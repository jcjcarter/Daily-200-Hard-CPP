// Daily 200 Hard CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Box {

public:
	int width, height, depth;

	Box(int width, int heigth, int depth) {
		this->width = width;
		this->height = heigth;
		this->depth = depth;
	}

	Box() : Box(0, 0, 0) {}

	int getVolume() const {
		return width * height * depth;
	}

	bool doesItFit(const Box& box) {
		return this->width >= box.width && this->height >= box.height && this->depth >= box.depth;
	}

	std::vector<Box *> addToBox(const Box& box) {
		std::vector<Box *> newBoxes;

		//Front
		if (this->width > box.width) {
			newBoxes.push_back(new Box(this->width - box.width, box.height, this->depth));
		}

		//Side
		if (this->depth > box.depth) {
			newBoxes.push_back(new Box(box.width, box.height, this->depth - box.depth));
		}

		//Top
		if (this->height > box.height) {
			newBoxes.push_back(new Box(this->width, this->height - box.height, this->depth));
		}

		return newBoxes;
	}
};

std::istream& operator>> (std::istream& is, Box& box) {
	is >> box.width >> box.height >> box.depth;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Box& box)
{
	os << box.width << " " << box.height << " " << box.depth;
	return os;
}

void divideBox(Box& box, std::vector<Box *>* stockBoxes, std::vector<Box *>* usedBoxes) {
	std::vector<Box *>::iterator stockItterater = stockBoxes->begin();

	while (stockItterater != stockBoxes->end() && !box.doesItFit(**stockItterater)) {
		stockItterater++;
	}

	if (stockItterater != stockBoxes->end()) {
		Box *b = *stockItterater;
		usedBoxes->push_back(b);
		stockBoxes->erase(stockItterater);

		for (auto newBox : box.addToBox(*b)) {
			divideBox(*newBox, stockBoxes, usedBoxes);
		}
	}
}

int main(int argc, const char * argv[]) {
	Box boxToFill;
	std::cin >> boxToFill;

	int numberOffBoxes;
	std::cin >> numberOffBoxes;

	std::vector<Box *> boxes;
	std::vector<Box *> usedBoxes;

	for (int i = 0; i < numberOffBoxes; i++) {
		Box *b = new Box();
		std::cin >> *b;
		boxes.push_back(b);
	}

	std::sort(boxes.begin(), boxes.end(),
		[](Box *a, Box *b) -> bool { return a->getVolume() > b->getVolume(); });


	divideBox(boxToFill, &boxes, &usedBoxes);

	std::cout << "Filled " << boxToFill << " with:" << std::endl;

	for (auto box : usedBoxes) {
		std::cout << *box << std::endl;
	}

	return 0;
}