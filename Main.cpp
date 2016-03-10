#include "stdafx.h"

using namespace std;
namespace fs = boost::filesystem;

const char * SAVE_LOCATION = "Saves";
const string INVALID_OPTION = "\nInvalid Option. Try again!\n";
const int MAX_LEVEL = 10;
const int MAX_HP = 100;

map<string, const string*> options;
const string RACES[] = { "Human", "Elf", "Orc", "Argonian" };
const string PROFS[] = { "Warrior", "Ranger", "Thief", "Mage" };
const string WEP_TYPES[] = { "Sword", "Bow", "Dagger", "Staff" };
const string POT_TYPES[] = { "Health", "Berserker" };

Item * ALL_ITEMS[] = {
//Weapons:
new Weapon("NULL", "Fist", 0, 1, 2), //0 - Default Weapon.
new Weapon("Sword", "Iron Sword", 5, 3, 6), //1
new Weapon("Sword", "Steel Sword", 20, 5, 8), //2
new Weapon("Sword", "Ebonhawk Sword", 40, 10, 15), //3
new Weapon("Sword", "Dawn-Breaker", 80, 15, 25), //4
new Weapon("Bow", "Softwood Bow", 5, 3, 6), //5
new Weapon("Bow", "Elderwood Bow", 20, 5, 8), //6
new Weapon("Bow", "Hardwood Bow", 40, 10, 15), //7
new Weapon("Bow", "Hunters Wrath", 80, 15, 25), //8
new Weapon("Dagger", "Iron Dagger", 5, 3, 6), //9
new Weapon("Dagger", "Steel Dagger", 20, 5, 8), //10
new Weapon("Dagger", "Ebonhawk Dagger", 40, 10, 15), //11
new Weapon("Dagger", "Death Blade", 80, 15, 25), //12
new Weapon("Staff", "Softwood Staff", 5, 3, 6), //13
new Weapon("Staff", "Elderwood Staff", 20, 5, 8), //14
new Weapon("Staff", "Hardwood Staff", 40, 10, 15), //15
new Weapon("Staff", "Infused Staff", 80, 15, 25), //16
//Potions:
new HealthPot("Health", "Minor Health Potion", 4, 5), //17
new HealthPot("Health", "Major Health Potion", 8, 10), //18
new HealthPot("Health", "Potent Health Potion", 14, 20), //19
new ZerkPot("Berserker", "Minor Berzerker Potion", 4, 10), //20
new ZerkPot("Berserker", "Major Berzerker Potion", 8, 20), //21
new ZerkPot("Berserker", "Potent Berzerker Potion", 14, 50), //22
//Junk:
new Item("Junk", "Anvil", 5), //23
new Item("Junk", "Rusty Screw", 3), //24
new Item("Junk", "Paper Scrap", 2), //25
new Item("Junk", "Bandit Crest", 8), //26
new Item("Junk", "Ruined Book", 5), //27
new Item("Junk", "Ruby", 10), //28
};

//Enemies:
Enemy * ENEMIES[] = {
new Enemy("Angry Slime", 10, 5, 3, 6),
new Enemy("Rat", 20, 4, 3, 8),
new Enemy("Goblin", 40, 4, 6, 10),
new Enemy("Fire Imp", 45, 5, 10, 15),
new Enemy("Giant", 150, 10, 2, 3),
new Enemy("Undead Knight", 45, 10, 8,14),
new Enemy("Axe Berserker", 75, 12, 10, 15),
new Enemy("Wisp", 45, 15, 1, 50),
new Enemy("Dragon Minion", 75, 30, 8, 50),
new Enemy("Ancient Dragon", 150, 200, 10, 20),
};


int dmgMultiplier = 0;
int zerkTurnsLeft = 0;
Player p;

const string getTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %H-%M-%S", &tstruct);
	return buf;
}
int getInt(string s) {
	unsigned int num;
	cout << s;
	while (!(cin >> num)) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << INVALID_OPTION << endl;
		cout << s;
	}
	return num;
}
bool yesOrNo(string s) {
	string yes[] = {"y", "ye", "yes", "yup", "yea", "yeah"};
	string no[] = {"n", "no", "na", "nah", "nope"};
	string answer = "";
	while (true) {
		cout << s;
		cin >> answer;
		for (string item : yes) {
			if (item == answer) {
				cout << endl;
				return true;
			}
		}
		for (string item : no) {
			if (item == answer) {
				cout << endl;
				return false;
			}
		}
		cout << INVALID_OPTION << endl;
	}
}
void savePlayer() {
	if (p.getRace() == -1) {
		cout << "No character to save!\n" << endl;
		return;
	}
	string filename(p.getName() + " " + getTime());
	cout << "Saving Character as '" << filename << "'..." << endl;
	filename = "\\" + filename;
	std::ofstream ofs(SAVE_LOCATION + filename + ".DAT");
	boost::archive::binary_oarchive oa(ofs);
	oa << p;
	cout << "Save Complete!\n" << endl;
}
void loadPlayer() {
	//Get string vector of filenames:
	vector<string> files;
	fs::path dir(SAVE_LOCATION);
	fs::directory_iterator iterator(dir);
	for (; iterator != fs::directory_iterator(); ++iterator) {
			files.push_back(iterator->path().filename().string());
	}
	if (files.size() == 0) {
		cout << "No saves to load!\n" << endl;
		return;
	}

	int choice;
	while (true) {
		//Display files to user:
		cout << "============[Saves]============" << endl;
		for (unsigned int i = 0; i < files.size(); i++) {
			cout << i + 1 << ". " << files[i] << endl;
		}
		cout << "Select a save to load, or enter '0' to exit." << endl;
		choice = getInt("Your Choice: ");
		if (choice > files.size() || choice < 0) {
			cout << INVALID_OPTION << endl;
		}
		else if (choice == 0) {
			cout << endl;
			return;
		}
		else {
			break;
		}
	}
	
	string filename(files[choice-1]);
	cout << "\nLoading " << filename << "..." << endl;
	filename = "\\" + filename;
	std::ifstream ifs(SAVE_LOCATION + filename);
	boost::archive::binary_iarchive ia(ifs);
	ia >> p;
	cout << "Load Complete!\n" << endl;
}
void createPlayer() {
	int choice;
	int validChar;
	int validOption;
	int validName;
	int race;
	int prof;
	string name("");
	map<string, int> selections;
	map<string, const string*>::iterator it;

	validChar = false;
	while (!validChar) {
		for (it = options.begin(); it != options.end(); it++) {
			choice = -1;
			validOption = false;
			while (!validOption) {
				cout << "======Character Creation======" << endl;
				//Display list of options:
				cout << it->first + " Selection:" << endl;
				for (int i = 0; i < 4; i++) {
					cout << "\t" << i + 1 << ". " << it->second[i] << endl;
				}
				//Validate User Input:
				choice = -1;
				while (choice == -1) {
					cout << "\nSelect an option, or enter '0' to exit.\n" << endl;
					choice = getInt("Your Choice: ");
					cout << endl;
					if (choice == 0) {
						return;
					}
					choice -= 1;
					if (choice > sizeof(it->second) - 1 || choice < 0) {
						cout << INVALID_OPTION << endl;
						choice = -1;
					}
				}
				selections[it->first] = choice;
				validOption = yesOrNo("You chose '" + it->second[choice] + "'. Is this correct? (Y/N): ");
			}
		}
		race = selections["Race"];
		prof = selections["Prof"];
		validName = false;
		while (!validName) {
			cout << "What name will you go by?: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name);
			if (name == "0") {
				return;
			}
			validName = yesOrNo("You chose " + name + ". Is this correct? (Y/N): ");
		}
		validChar = yesOrNo("You will be known as " + name + ", the " + RACES[race] + " " + PROFS[prof] + ". Is this correct? (Y/N): ");		
	}
	p.setRace(race);
	p.setProf(prof);
	p.setName(name);
	savePlayer();
}
bool isPot(int itemID) {
	for (string type : POT_TYPES) {
		if (ALL_ITEMS[itemID]->getType() == type) {
			return true;
		}
	}
	return false;
}
void buyPots() {
	vector<int> shopItemIDs;
	int itemID = 0;
	for (Item *item : ALL_ITEMS) {
		if (isPot(itemID)) {
			shopItemIDs.push_back(itemID);
			
		}
		itemID++;
	}
	int choice;
	int count;
	while (true) {
		cout << "============[Potions]============" << endl;
		cout << "Balance: " << p.getFunds() << "g\n" << endl;
		count = 0;
		for (int itemID : shopItemIDs) {
			count++;
			cout << "\t" << count << ". ";
			ALL_ITEMS[itemID]->print();
		}
		cout << "\nSelect an potion to buy, or enter '0' to exit.\n" << endl;
		choice = getInt("Your Chocie: ");
		cout << endl;
		if (choice == 0) {
			return;
		}
		else if (choice > shopItemIDs.size() || choice < 0) {
			cout << INVALID_OPTION << endl;
		}
		else {
			itemID = shopItemIDs[choice - 1];
			if (p.hasFunds(ALL_ITEMS[itemID]->getValue())) {
				p.removeFunds(ALL_ITEMS[itemID]->getValue());
				p.addItem(itemID);
				cout << "You bought " << ALL_ITEMS[itemID]->getName() << " for " << ALL_ITEMS[itemID]->getValue() << "g!\n" << endl;
			}
			else {
				cout << "\nYou dont have enough gold!\n" << endl;

			}
		}
	}
}
void buyWeps() {
	string wepType = WEP_TYPES[p.getProf()];
	vector<int> shopItemIDs;
	int itemID = 0;
	for (Item *item : ALL_ITEMS) {
		if (item->getType() == wepType) {
			shopItemIDs.push_back(itemID);
		}
		itemID++;
	}

	int choice;
	while (true) {
		cout << "============[" << wepType << "s]============" << endl;
		cout << "Balance: " << p.getFunds() << "g\n" << endl;
		int count = 0;
		for (int itemID : shopItemIDs) {
			count++;
			cout << "\t" << count << ". ";
			ALL_ITEMS[itemID]->print();
		}
		cout << "\nSelect an item to buy, or enter '0' to exit.\n" << endl;
		choice = getInt("Your Choice: ");
		cout << endl;
		if (choice == 0) {
			return;
		}
		if (choice > shopItemIDs.size() || choice < 0) {
			cout << INVALID_OPTION << endl;
		}
		else {
			itemID = shopItemIDs[choice - 1];
			if (p.hasFunds(ALL_ITEMS[itemID]->getValue())) {
				p.removeFunds(ALL_ITEMS[itemID]->getValue());
				p.addItem(itemID);
				cout << "You bought " << ALL_ITEMS[itemID]->getName() << " for " << ALL_ITEMS[itemID]->getValue() << "g!\n" << endl;
			}
			else {
				cout << "\nYou dont have enough gold!\n" << endl;

			}
		}
	}
}
void buy() {
	string wepType = WEP_TYPES[p.getProf()];
	
	int choice;
	while (true) {
		cout << "============[Buy Items]============" << endl;
		cout << "| 1. " << wepType << "s | 2. Potions | 0. Exit |\n" << endl;
		choice = getInt("Your Choice: ");
		cout << endl;
		switch (choice) {
		case 0: return;
		case 1: buyWeps(); break;
		case 2: buyPots(); break;
		default: cout << INVALID_OPTION << endl;
		}
	}
}

void sell() {
	int count;
	int choice;
	while (true) {
		if (p.getInv().size() == 0) {
			cout << "You have no items to sell!\n" << endl;
			return;
		}
		cout << "============[Sell Items]============" << endl;
		cout << "Balance: " << p.getFunds() << "g\n" << endl;
		count = 0;
		for (int itemID : p.getInv()) {
			count++;
			cout << "\t" << count << ". ";
			ALL_ITEMS[itemID]->print();
		}
		cout << "\nSelect an item to sell, or enter '0' to exit.\n" << endl;
		choice = getInt("Your Choice: ");
		if (choice == 0) {
			break;
		}
		if (choice > p.getInv().size() || choice < 0) {
			cout << INVALID_OPTION << endl;
		}
		else {
			int itemID = p.getInv()[choice-1];
			int value = ALL_ITEMS[itemID]->getValue();
			cout << "\nYou sold " << ALL_ITEMS[itemID]->getName() << " for " << ALL_ITEMS[itemID]->getValue() << "g!\n" << endl;
			p.addFunds(value);
			p.removeItem(p.getInv()[choice-1]);
		}
		cout << endl;
	}
	
}

void merchant() {
	int choice;
	while (true) {
		cout << "============[Merchant]============" << endl;
		cout << "Merchant: How may i help you?" << endl;
		cout << "| 1. Buy | 2. Sell | 0. Exit |\n" << endl;
		choice = getInt("Your Choice: ");
		cout << endl;
		switch (choice) {
		case 0: return;
		case 1: buy(); break;
		case 2: sell(); break;
		default: cout << INVALID_OPTION << endl;
		}
	}
}

void useItem() {
	vector<int> usable;
	int choice;
	int count;
	while (true) {
		usable.clear();
		for (int itemID : p.getInv()) {
			if (isPot(itemID)) {
				usable.push_back(itemID);
			}
		}
		if (usable.size() < 1) {
			cout << "You have no items to use!\n" << endl;
			return;
		}
		cout << "============[Use Item]============" << endl;
		cout << "Health: " << p.getHp() << "/" << MAX_HP << endl;
		cout << "Dmg Increase: " << dmgMultiplier << "%\n" << endl;
		count = 0;
		for (int itemID : usable) {
			count++;
			cout << "\t" << count << ". ";
			ALL_ITEMS[itemID]->print();
		}
		cout << "\nSelect an item to use, or enter '0' to exit.\n" << endl;
		choice = getInt("Your Chocie: ");
		cout << endl;
		
		if (choice == 0) {
			return;
		}

		int itemID = usable[choice - 1];
		Item *potion = ALL_ITEMS[itemID];
		if (choice > usable.size() || choice < 0) {
			cout << INVALID_OPTION << endl;
		}
		else if (potion->getType() == "Health"){
			if (p.getHp() < MAX_HP) {
				p.addHp(potion->getPower());
				p.removeItem(itemID);
				cout << "You gained " << potion->getPower() << " hp!\n" << endl;
				if (p.getHp() > p.getMaxHp()) {
					p.resetHp();
				}

			}
			else {
				cout << "Your health is already full!\n" << endl;
			}
		}
		else if (potion->getType() == "Berserker") {
			dmgMultiplier = potion->getPower();
			zerkTurnsLeft = 3;
			cout << itemID << endl;
			p.removeItem(itemID);
		}
	}
}
bool canUse(int itemID) {
	return (ALL_ITEMS[itemID]->getType() == WEP_TYPES[p.getProf()]);
}
void equipItem() {
	vector<int> equipable;
	for (int itemID : p.getInv()) {
		if (canUse(itemID)) {
			equipable.push_back(itemID);
		}
	}
	if (equipable.size() < 1) {
		cout << "You have no items to equip!\n" << endl;
		return;
	}
	
	int choice;
	int count;
	while (true) {
		cout << "============[Equip]============\n" << endl;
		count = 0;
		for (int itemID : equipable) {
			count++;
			cout << "\t" << count << ". ";
			ALL_ITEMS[itemID]->print();
		}
		cout << "\nSelect an item to equip, or enter '0' to exit.\n" << endl;
		choice = getInt("Your Chocie: ");
		cout << endl;
		if (choice == 0) {
			return;
		}
		else if (choice > equipable.size() || choice < 0) {
			cout << INVALID_OPTION << endl;
		}
		else {
			p.uneqipItem();
			p.equipItem(equipable[choice-1]);
			cout << ALL_ITEMS[p.getWepInHand()]->getName() << " equiped!\n" << endl;
			return;
		}

	}
}

void unequipItem() {
	if (p.getWepInHand() == 0) {
		cout << "No item equiped!\n" << endl;
	}
	else {
		cout << ALL_ITEMS[p.getWepInHand()]->getName() << " unequiped!\n" << endl;
		p.uneqipItem();
	}
}

void openInv() {
	//Display Inventory:
	int count;
	int choice;
	while (true) {
		cout << "==========[Inventory]==========" << endl;
		cout << "\tHealth: " << p.getHp() << "/100" << endl;
		cout << "\tDmg Increase: " << dmgMultiplier << "%" << endl;
		cout << "\tBalance: " << p.getFunds() << "g" << endl;
		cout << "\tEquiped: " << ALL_ITEMS[p.getWepInHand()]->getName() << endl;
		cout << "Items: " << endl;
		count = 0;
		for (int itemID : p.getInv()) {
			count++;
			cout << "\t" << count << ". ";
			ALL_ITEMS[itemID]->print();
		}
		cout << "\n| 1. Equip Item | 2. Unequip Item | 3. Use Item | 0. Exit |\n" << endl;
		choice = getInt("Your Choice: ");
		cout << endl;
		switch (choice) {
		case 0: return;
		case 1: equipItem(); break;
		case 2: unequipItem(); break;
		case 3: useItem(); break;
		default: cout << INVALID_OPTION << endl;
		}
	}

	cout << endl;

}

void nextTurn() {
	int itemID = p.getWepInHand();
	Item * wep = ALL_ITEMS[itemID];
	Enemy *e = ENEMIES[p.getLevel()];
	int pDmg = wep->getPower();
	if (zerkTurnsLeft > 0) {
		pDmg *= ((dmgMultiplier/100) + 1);
		zerkTurnsLeft -= 1;
		cout << "[**] CRIT: " << p.getName() << " attacks with " << wep->getName() << " for " << pDmg << " damage!\n" << endl;
	}
	else {
		dmgMultiplier = 0;
		cout << "[>>] " << p.getName() << " attacks with " << wep->getName() << " for " << pDmg << " damage!\n" << endl;
	}
	e->removeHp(pDmg);

	int eDmg = e->getPower();
	cout << "[<<] " << e->getName() << " attacks " << p.getName() << " for " << eDmg << " damage!" << endl;
	p.removeHp(eDmg);
	cout << endl;
}

void fight() {
	int choice;
	if (p.getLevel() == MAX_LEVEL) {
		cout << "[!] You have cleared the dungeon of all foes. Congratulations!\n" << endl;
		return;
	}
	Enemy *e = ENEMIES[p.getLevel()];
	e->resetHp();
	cout << "\n[!] '" << e->getName() << "' challenges you to a fight!\n" << endl;
	while (true) {
		cout << "================[Your Turn]================" << endl;
		cout <<  "| " << e->getName() << "'s HP: " << e->getHp() << "/" << e->getMaxHp() <<  "| Your HP: " << p.getHp() << "/" << MAX_HP << " |" << endl;
		cout << "| 1. Attack | 2. Inventory | 0. Run Away! |\n" << endl;
		choice = getInt("Your Choice: ");
		cout << endl;
		switch (choice) {
		case 0: p.resetHp(); e->resetHp(); cout << "You flee in terror!\n " << endl; return;
		case 1: nextTurn(); break;
		case 2: openInv(); break;
		}
		if (e->getHp() <= 0) {
			cout << e->getName() << " has been defeated!" << endl;
			p.addLevel();
			p.addFunds(e->getReward());
			//Generate Random Item:
			random_device seed;
			mt19937 rand(seed());
			uniform_int_distribution<> range(23, 28);
			int itemID = range(rand);
			cout << e->getName() << " dropped '" << ALL_ITEMS[itemID]->getName() << "'!\n" << endl;
			p.addItem(itemID);
			p.resetHp();
			return;
		}
		if (p.getHp() <= 0) {
			cout << "You have been slain!\n" << endl;
			p.resetHp();
			return;
		}
	}
}

void lobby() {
	if (p.getRace() == -1) {
		cout << "No character loaded!\n" << endl;
		return;
	}
	int choice;
	while (true){
		cout << "=====================[Lobby]=====================" << endl;
		cout << "| Profession: " << PROFS[p.getProf()] << " | Level: " << p.getLevel() << "/" << MAX_LEVEL << " | Gold: " << p.getFunds() << "g |" << endl;
		cout << "| 1. Enter Dungeon | 2. Open Inventory | 3. Visit Merchant | 0. Exit |\n" << endl;
		choice = getInt("Your Choice: ");
		cout << endl;

		switch (choice) {
		case 0: return;
		case 1: fight(); break;
		case 2: openInv(); break;
		case 3: merchant(); break;
		default: cout << INVALID_OPTION << endl;
		}
	}
}


void displayMenu() {
	cout << "=======[Text Rpg v1.0]=======\n\t1. Create Character\n\t2. Load Character\n\t3. Save Character\n\t4. Enter Lobby\n\t5. Quit\n" << endl;
}

int main()
{
	_mkdir(SAVE_LOCATION);
	options["Prof"] = PROFS;
	options["Race"] = RACES;
	int choice;
	while (true) {
		choice = 0;
		displayMenu();
		choice = getInt("Your Choice: ");
		cout << endl;
		switch (choice) {
		case 1: createPlayer(); break;
		case 2: loadPlayer(); break;
		case 3: savePlayer(); break;
		case 4: lobby(); break;
		case 5: return 0;
		case 6:
			//TESTING FUNCTIONS:
			p.addFunds(100);
			cout << "POWER: " << ALL_ITEMS[p.getWepInHand()]->getPower() << endl;
			break;
		default:
			cout << INVALID_OPTION << endl;
		}
	}
}