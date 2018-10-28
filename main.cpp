#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include <list>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class Ball {
private:
	double vx_;
	double vy_;
	double Fx_ = 1000;
	double Fy_ = 1000;
	double dt = 0.01;
	double m_ = 0.1;

public:
	double x_;
	double y_;
	int r_;

	Ball() {
		x_ = 20;
		y_ = 20;
		r_ = 10;
		vx_ = 10;
		vy_ = 10;
	}

	Ball(double x, double y, int r = 10, double vx = 10 , double vy = 10) {
		x_ = x;
		y_ = y;
		r_ = r;
		vx_ = vx;
		vy_ = vy;
	}

	void draw() {
		circle(x_, y_, r_);
	}

	void move() {
		x_ = x_ + dt * vx_;
		y_ = y_ + dt * vy_;
	}

	void accelerateX() {
		if (x_ <= r_ / 2) {
			vx_ = vx_ + dt * Fx_ / m_;
		}
		else {
			vx_ = vx_ - dt * Fx_ / m_;
		}
	}

	void accelerateY() {
		if(y_ <= r_ / 2){
			vy_ = vy_ + dt * Fy_ / m_;
		}
		else {
			vy_ = vy_ - dt * Fy_ / m_;
		}
	}

	friend void sciana(Ball &ball, double size);
	friend double predkosc(Ball &ball);
};

void sciana(Ball &ball, double size) {
	if (ball.y_ <=ball.r_/2 || ball.y_ >= size-ball.r_/2) {
		//ball.accelerate();
	}
}
double predkosc(Ball &ball) {
	return sqrt(ball.vx_*ball.vx_ + ball.vy_*ball.vy_);
}


void main()
{
	srand(time(NULL));

	double size = 600;
	int r = 10;
	double v;

	typedef std::list<Ball> Kulki;
	Kulki kulki;

	for (int i = 0; i < 10; i++) {
		double x = rand() % ((int)size - r) + r / 2;
		double y = rand() % ((int)size - r) + r / 2;
		double vx = 10 * (rand() % 10) + 50;
		double vy = 10 * (rand() % 10) + 50;
		kulki.push_back(Ball(x, y, r, vx, vy));
	}

	graphics(size, size);

	while (animate(60)) {
		clear();

		line(0, 0, 0, size);
		line(0, 0, size, 0);
		line(0, size, size, size);
		line(size, 0, size, size);

		for (Kulki::iterator k = kulki.begin(); k != kulki.end(); k++) {
			
			k->move();
			k->draw();

			if ((k->y_) <= (k->r_ / 2) || (k->y_) >= (size - k->r_ / 2)) {
				k->accelerateY();
			}

			if ((k->x_) <= (k->r_ / 2) || (k->x_) >= (size - k->r_ / 2)) {
				k->accelerateX();
			}

			v = predkosc(*k);

			cout << "\t  " << v;
		}
		cout << endl;
	}
	wait();
}