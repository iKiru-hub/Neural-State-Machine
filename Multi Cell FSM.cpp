#include <iostream>
#include <vector>

class Cell2 {
	char id = 0;

	bool my_x = false;
	bool my_y = false;
	bool my_z = false;
	
	bool flag_y = false;
	bool flag_z = false;
	bool I_flagged = false;
	int flags = 0;
	
	int position = 0;
	
	bool end = false;

public:
	Cell2(char u) {
		id = u;
		std::cout << "++ cell " << u << " has born! ++\n" << std::endl;
		std::cin.get();
	}
	void getX(int x) {
		if (x == 1) {
			my_x = true;
			std::cout << "--> " << id << " got an X\n" << std::endl;
			std::cin.get();

			if (!flag_y) flag_y = true;
			else if (!flag_z) flag_z = true;
		}
	}
	bool flaggin() { 
		if (flag_y and !flag_z and flags < 1 ) {
			std::cout << id << " flags Y\n" << std::endl;
			std::cin.get();
			I_flagged = true;
			flags++;
			return flag_y;
		}
		else if (flag_z and flags < 2) {
			std::cout << id << " flags Z\n" << std::endl;
			std::cin.get();
			I_flagged = true;
			flags++;
			return flag_z;
		}
		else {
			I_flagged = false;
			return false;
		}
	}
	void getY(bool one_got_x) {
		if (one_got_x and !I_flagged) {
			if (!my_y) {
				my_y = true;
				std::cout << "\n" << id << " received the Y" << std::endl;
				std::cin.get();
			}
			else if (!my_z) {
				my_z = true;
				std::cout << "\n" << id << " received the Z" << std::endl;
				std::cin.get();
			}
		}
	}
	void updating() {
		set_pos();
		final();
	}
	bool ending() { return end; }

private:
	void set_pos() {
		if (my_x and position==0) {
			if (!my_y and !my_z) position = 1;
			else if (my_y and !my_z) position = 2;
			else if (my_y and my_z) position = 3;
		}
	}
	void final() {
		if (my_x and my_y and my_z) {
			std::cout << "\n> " << id << " says: my final position is:  > " << position << " <" << std::endl;
			std::cin.get();
			end = true;
		}
	}
};




int main() {
	std::cout << "\n** MULTI CELL FSM **\n" << std::endl;
	std::cout << "just press enter" << std::endl;
	std::cin.get();

	Cell2 lefty{ 'L' };
	Cell2 righty{ 'R' };
	Cell2 centry{ 'C' };

	std::vector <int> lv = { 0, 1, 0, 0, 0, 0, 0 };
	std::vector <int> rv = { 0, 0, 0, 0, 1, 0, 0 };
	std::vector <int> cv = { 0, 0, 1, 0, 0, 0, 0 };

	bool one_got_smt = false;

	for (int i = 0; i < lv.size(); i++) {
		std::cout << "\n\n###### time " << i << std::endl;
		std::cout << "just press enter" << std::endl;
		std::cin.get();

		lefty.getX(lv[i]);
		righty.getX(rv[i]);
		centry.getX(cv[i]);

		one_got_smt = lefty.flaggin() or righty.flaggin() or centry.flaggin();
		if(one_got_smt == 0) std::cout << " nobody spiked  ---- " << std::endl;
		else std::cout << " ---> somebody spiked  <---- " << std::endl;

		lefty.getY(one_got_smt);
		righty.getY(one_got_smt);
		centry.getY(one_got_smt);

		lefty.updating();
		righty.updating();
		centry.updating();

		if (lefty.ending() and righty.ending() and centry.ending()) {
			std::cout << "\n++ ending ++" << std::endl;
			break;
		}

		one_got_smt = false;
	};
}  
