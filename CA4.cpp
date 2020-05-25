// CA4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Jing Sheng Moey
// SD2A 

#include <iostream>
#include <utility> 
#include <string>
#include <list> 
#include <iterator> 
#include <vector>
#include <stdexcept>
#include <fstream> 
#include <sstream>
#include <iomanip>   
#include <stdlib.h> 
#include <ctime>
#include <map> 
#include <algorithm>
using namespace std;

class Bug
{
private:int m_id;
       pair<int, int> m_position;
       int m_direction; //1 = North, 2 = East, 3 = South, 4 = West
       int m_size;
       bool m_alive;
       list<pair<int, int>> m_path;
       int m_eatenBy;
public:
    Bug(const int id = 0, int firstPos = 0, int secondPos = 0, int direction = 0, int size = 0, bool alive = true)
        :m_id{ id }, m_position{ firstPos, secondPos }, m_direction{ direction }, m_size{ size }, m_alive{alive}
    {
        this->addPath(firstPos, secondPos);
    }
    Bug(const int id = 0, int firstPos = 0, int secondPos = 0, int direction = 0, int size = 0)
        :m_id{ id }, m_position{ firstPos, secondPos }, m_direction{ direction }, m_size{ size }, m_alive{ true }
    {
        this->addPath(firstPos, secondPos);
    }

    //getter
    int getId() { return m_id; }
    pair<int, int> getPos() { return m_position; }
    int getDirection() { return m_direction; }
    int getSize() { return m_size; }
    bool getAlive(){ return m_alive; }
    list<pair<int, int>> getPath() { return m_path; }
    int getEatenBy() { return m_eatenBy; }

    //setter
    void setId(int id) { this->m_id = id; }
    void setPos(int x, int y) { this->m_position.first = x; this->m_position.second = y; }
    void setDirection(int direction) { this->m_direction = direction; }
    void setSize(int size) { this->m_size = size; }
    void setAlive(bool alive) { this->m_alive = alive; }
    void addPath(int x,int y) {this->m_path.push_back(make_pair(x, y));}
    void setEatenBy(int eatenBy) { this->m_eatenBy = eatenBy; }

    //functions 
    virtual void move() {}
    ~Bug();
    bool isWayBlocked(int pos) 
    {
        if (pos > 9 || pos < 0)
        {
            return true;
        }
        return false;
    }
    void changeDirection(int currentDirection)
    {
        //long t = time(0);
        //cout << "t = " << t << endl;
        //srand(t); // use time number as the algorithm 
        int newDir = 1 + (rand() % 4);
        while (newDir == currentDirection) // getting new direction 
        {
            newDir = 1 + (rand() % 4);
        }
        this->setDirection(newDir);
        this->move();
    }
   
};
Bug::~Bug(){}

class Crawler :public Bug
{
public:
    Crawler(const int id = 0, int firstPos = 0, int secondPos = 0, int direction = 0, int size = 0, bool alive = true)
        :Bug{ id, firstPos, secondPos, direction, size, alive }
    {
    }
    virtual void move();
    ~Crawler();
};
Crawler::~Crawler() {}
void Crawler::move() // implementation of move 
{	
    if (this->getAlive())
    {
        int currentDirection = this->getDirection();
        pair<int, int> pos = this->getPos();
        int newPos;
        if (currentDirection == 1) //1=North, 2=East, 3=South, 4=West
        {
            newPos = pos.second - 1;
            if (isWayBlocked(newPos))
            {
                this->changeDirection(currentDirection);
            }
            else
            {
                this->setPos(pos.first, newPos);
                this->addPath(pos.first, newPos);
            }
        }
        else if (currentDirection == 2)
        {
            newPos = pos.first + 1;
            if (isWayBlocked(newPos))
            {
                this->changeDirection(currentDirection);
            }
            else
            {
                this->setPos(newPos, pos.second);
                this->addPath(newPos, pos.second);
            }
        }
        else if (currentDirection == 3)
        {
            newPos = pos.second + 1;
            if (isWayBlocked(newPos))
            {
                this->changeDirection(currentDirection);
            }
            else
            {
                this->setPos(pos.first, newPos);
                this->addPath(pos.first, newPos);
            }
        }
        else
        {
            newPos = pos.first - 1;
            if (isWayBlocked(newPos))
            {
                this->changeDirection(currentDirection);
            }
            else
            {
                this->setPos(newPos, pos.second);
                this->addPath(newPos, pos.second);
            }
        }
    }
}

class Hopper :public Bug
{
private:int m_hopLength;
public:
    Hopper(const int id = 0, int firstPos = 0, int secondPos = 0, int direction = 0, int size = 0, bool alive = true,
        int hopLength = 0)
        :Bug{ id, firstPos, secondPos, direction, size, alive },
        m_hopLength{ hopLength }
    {
    }
    Hopper(const int id = 0, int firstPos = 0, int secondPos = 0, int direction = 0, int size = 0,
        int hopLength = 0)
        :Bug{ id, firstPos, secondPos, direction, size, true },
        m_hopLength{ hopLength }
    {
    }
    int getHopLength() { return m_hopLength; }
    virtual void move();
    ~Hopper();
};
Hopper::~Hopper() {}
void Hopper::move() // implementation of move 
{	
    if (this->getAlive())
    {
        int currentDirection = this->getDirection();
        pair<int, int> pos = this->getPos();
        int newPos;
        int hopLength = this->getHopLength();
        if (currentDirection == 1) //1=North, 2=East, 3=South, 4=West
        {
            newPos = pos.second - hopLength;
            if (isWayBlocked(newPos))
            {
                if (pos.second != 0)
                {
                    this->setPos(pos.first, 0);
                    this->addPath(pos.first, 0);
                }
                else
                {
                    this->changeDirection(currentDirection);
                }

            }
            else
            {
                this->setPos(pos.first, newPos);
                this->addPath(pos.first, newPos);
            }
        }
        else if (currentDirection == 2)
        {
            newPos = pos.first + hopLength;
            if (isWayBlocked(newPos))
            {
                if (pos.first != 9)
                {
                    this->setPos(9, pos.second);
                    this->addPath(9, pos.second);
                }
                else
                {
                    this->changeDirection(currentDirection);
                }
            }
            else
            {
                this->setPos(newPos, pos.second);
                this->addPath(newPos, pos.second);
            }
        }
        else if (currentDirection == 3)
        {
            newPos = pos.second + hopLength;
            if (isWayBlocked(newPos))
            {
                if (pos.second != 9)
                {
                    this->setPos(pos.first, 9);
                    this->addPath(pos.first, 9);
                }
                else
                {
                    this->changeDirection(currentDirection);
                }
            }
            else
            {
                this->setPos(pos.first, newPos);
                this->addPath(pos.first, newPos);
            }
        }
        else
        {
            newPos = pos.first - hopLength;
            if (isWayBlocked(newPos))
            {
                if (pos.first != 0)
                {
                    this->setPos(0, pos.second);
                    this->addPath(0, pos.second);
                }
                else
                {
                    this->changeDirection(currentDirection);
                }
            }
            else
            {
                this->setPos(newPos, pos.second);
                this->addPath(newPos, pos.second);
            }
        }
    }    
}



//static variables
static vector<Bug*> bugs; 
static map<pair<int, int>, vector<Bug*>> cells;
static map<pair<int, int>, vector<Bug*>> ::iterator itr; // create an iterator 
static bool initialized = false;

// Utilities get Int 
int getValidInt(int smallest)
{
    string _;
    int returnNumber;
    cin >> returnNumber;
    getline(cin, _);
    while (cin.fail() || returnNumber < smallest)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Numbers only available from " << smallest << ", Please Enter again." << endl;
        cout << ">";
        cin >> returnNumber;
    }
    return returnNumber;
}

// Utilities get Int 
int getValidInt(int smallest, int largest)
{
    int returnNumber;
    cin >> returnNumber;
    while (cin.fail() || returnNumber < smallest || returnNumber > largest)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Numbers only available from " << smallest << " ~ " << largest << ", Please Enter again." << endl;
        cout << ">";
        cin >> returnNumber;
    }
    return returnNumber;
}

//functions 
// parse line from the text file and add bugs into the game 
void parseLineAddBug(const string& str)
{
    try
    {
        stringstream strStream(str); //create string stream from the string
        string bugType;
        string sBugId;
        string sX;
        string sY;
        string sDirection;
        string sSize;

        
        getline(strStream, bugType, ';');
        getline(strStream, sBugId, ';');
        int bugId = stoi(sBugId);
        getline(strStream, sX, ';');
        int x = stoi(sX);
        getline(strStream, sY, ';');
        int y = stoi(sY);
        getline(strStream, sDirection, ';');
        int direction = stoi(sDirection);
        getline(strStream, sSize, ';');
        int size = stoi(sSize);


        if(bugType.compare("H") == 0)
        {
            string sHopLength;
            getline(strStream, sHopLength, ';');
            int hopLength = stoi(sHopLength);
            /*Hopper h{bugId, x, y, direction, size, hopLength};
            cout << h.getId() << endl;*/
            bugs.push_back(new Hopper{ bugId, x, y, direction, size, hopLength });
        }
        else
        {
            bugs.push_back(new Crawler{ bugId, x, y, direction, size });
            //Crawler c{ bugId, x, y, direction, size };
            //cout << c.getId() << endl;
            //bugs.push_back(&c);
        }
        cout << "Insert successfully." << endl;
    }
    catch (std::invalid_argument const& e)
    {
        cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const& e)
    {
        cout << "Integer overflow: std::out_of_range thrown" << '\n';
    }
}

// read the file
void InputFileStream() {
    string line;
    string firstLine;
    ifstream inStream("bugs.txt"); // open file as input file stream

    if (inStream.good())  // if file opened successfully, and not empty
    {
        cout << "Reding from text file." << endl;
        while (getline(inStream, line))   // read a line until false returned , getline() from <string> library
        {
            parseLineAddBug(line);
        }
        inStream.close();
    }
    else
    {
        cout << "Reding from back-up Memory." << endl;

    }
}

// output the data 
void OutputFileStream()
{
    cout << "Creating and writing to file: out.txt" << endl;

    ofstream outStream("out.txt");  // write mode (overwrites existing data)
    if (outStream.good())
    {
        /*outSteam <<*/
        for (Bug* b : bugs)
        {
            if (b->getAlive()) // only output bugs that are alive 
            {
                if (typeid(*b) == typeid(Crawler))
                    outStream << "C;";
                else
                    outStream << "H;";

                outStream << b->getId() << ";" << b->getPos().first << ";" << b->getPos().second << ";" << b->getDirection() << ";" << b->getSize() << ";";
                if (typeid(*b) == typeid(Hopper))
                {
                    Hopper* h = dynamic_cast<Hopper*>(b);
                    outStream << h->getHopLength();
                }
                outStream << endl;
            }
        }
        outStream.close(); //  close file 
        cout << "File written.\n" << endl;
    }
    else
        cout << "Unable to open file";
}

// bug size comnparator 
bool sizeComparatorDecending(Bug* b1, Bug* b2) // Name comparator
{
    return b1->getSize() > b2->getSize();
}

// initialize empty cells map 
void initializeCellsMap()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            vector<Bug*> b;
            cells.insert(make_pair(make_pair(i, j), b));
        }
    }
}

// fill all bugs into the cells map
void fillBugsIntoCells()
{
    for (Bug* b : bugs)
    {
        if (b->getAlive())
        {
            pair<int, int> pos = b->getPos();
            cells[make_pair(pos.first, pos.second)].push_back(b);
        }
    }
}

//display all bugs 
void displayAllBugs(vector<Bug*> tempBugs)
{
    if (initialized)
    {
        cout << "ID" << setw(10) << "X" << setw(10) << "Y" << setw(15) << "Direction" << setw(10) << "Size" << setw(10) << "Status" << setw(10) << "Type" << setw(15) << "Hop Length" << endl;
        for (Bug* b : tempBugs)
        {
            cout << b->getId() << setw(9);
            cout << b->getPos().first << setw(10);
            cout << b->getPos().second << setw(10);
            cout << b->getDirection() << setw(14);
            cout << b->getSize() << setw(10);
            if (b->getAlive())
                cout << "Alive" << setw(10);
            else
                cout << "Dead" << setw(10);

            if (typeid(*b) == typeid(Crawler))
            {
                cout << "C";
            }
            else
            {
                Hopper* h = dynamic_cast<Hopper*>(b); // dynamic casting 
                cout << "H" << setw(10);
                cout << h->getHopLength();
            }
            cout << endl;
        }
    }
    else
        cout << "No bug found." << endl;
}

//get bug by id, return the position of the bug by id 
int getBugById(int id)
{
    int pos = -1;
    for (int i = 0; i < bugs.size(); i++)
    {
        if (bugs.at(i)->getId() == id)
        {
            return i;
        }
    }
    return pos;
}

//find bug by id and display the details of the bug 
void findBugById()
{
    if (initialized)
    {
        cout << "Enter Bug Id" << endl;
        int bugId = getValidInt(0);
        int pos = getBugById(bugId);
        if (pos == -1)
        {
            cout << "No Bug Found." << endl;
        }
        else
        {
            Bug* b = bugs.at(pos);
            vector<Bug*> thisBug;
            thisBug.push_back(b);
            displayAllBugs(thisBug);
        }
    }
    else
        cout << "No bug found" << endl;
}

//fight and eat the smaller bug in the same cell
void fightAndEat() // ing 
{
    for (itr = cells.begin(); itr != cells.end(); itr++) // use an iterator to loop through 
    {
        vector<Bug*> tempBugs = (itr->second);
        //find biggest
        if (tempBugs.size() >= 2)
        {
            sort(tempBugs.begin(), tempBugs.end(), &sizeComparatorDecending);
            int largestBugId = tempBugs.at(0)->getId();
            int largestBugPos = getBugById(largestBugId);
            int largestSize = tempBugs.at(0)->getSize();
            bool hasSame = false;
            for (int i = 1; i < tempBugs.size(); i++)
            {
                if (largestSize == tempBugs.at(i)->getSize())
                    hasSame = true;
                else if (largestSize > tempBugs.at(i)->getSize() && hasSame == false)
                {
                    tempBugs.at(0)->setSize(tempBugs.at(0)->getSize() + tempBugs.at(i)->getSize());

                    // set alive to false 
                    int dieBugPos = getBugById(tempBugs.at(i)->getId());
                    bugs.at(dieBugPos)->setAlive(false);
                    bugs.at(dieBugPos)->setEatenBy(largestBugId);

                    //delete the bugs in temp bugs vector in the cells 
                    tempBugs.erase(tempBugs.begin() + i);
                    i--;
                }
            }
            if (!hasSame)
            {
                //set the real bug's size
                bugs.at(largestBugPos)->setSize(tempBugs.at(0)->getSize());
                //set new vector
                itr->second = tempBugs;
            }
            
        }
    }
}

//tap the board to move all the bugs 
void tapTheBoard()
{
    if (initialized)
    {
        for (Bug* b : bugs)
        {
            b->move();
        }
        cells.clear();
        initializeCellsMap();
        fillBugsIntoCells();
        fightAndEat();
        displayAllBugs(bugs);
    }
    else
        cout << "No bug found" << endl;
}

//display bug's life history 
void displayLifeHistory()
{
    if (initialized)
    {
        for (Bug* b : bugs)
        {
            list<pair<int, int>> paths = b->getPath();
            cout << b->getId() << " " << typeid(*b).name() << " Path :";
            for (pair<int, int> p : paths)
            {
                cout << "(" << p.first << "," << p.second << ")";
            }
            if (b->getAlive() == true)
                cout << "Alive!";
            else
                cout << "Eaten by " << b->getEatenBy();
            cout << endl;
        }
    }
    else
        cout << "No bug found" << endl;
}

//display bugs in all cells 
void displayAllCells()
{
    if (initialized)
    {
        for (itr = cells.begin(); itr != cells.end(); itr++) // use an iterator to loop through 
        {
            cout << "(" << (itr->first).first << "," << (itr->first).second << "): ";
            vector<Bug*> bugs = (itr->second);
            if (bugs.empty())
            {
                cout << "Empty!" << endl;
            }
            else
            {
                for (Bug* b : bugs)
                {
                    if (typeid(b) == typeid(Crawler))
                    {
                        cout << "Crawler " << b->getId();
                    }
                    else
                    {
                        cout << "Hopper " << b->getId();
                    }
                }
                cout << endl;
            }

        }
    }
    else
        cout << "No bug found" << endl;
}

//main menu 
void mainMenu()
{
    cout << endl << "Welcome to Bug game." << endl;
    cout << "1. Initialize the Bug Board" << endl;
    cout << "2. Display All bugs" << endl;
    cout << "3. Find a Bug" << endl;
    cout << "4. Tap the bugs board" << endl;
    cout << "5. Display All path history" << endl;
    cout << "6. Display All Cells" << endl;
    cout << "0. Quit" << endl;
    cout << "Please enter an option" << endl;
}

//Entrance to run the application 
void run()
{
    srand(time(0)); // secret rand with time 
    mainMenu();
    bool running = true;
    int option = getValidInt(0, 6);
    while (running)
    {
        if (option == 0)
        {
            running = false;
        }
        else if (option == 1)
        {
            InputFileStream();
            initializeCellsMap();
            fillBugsIntoCells();
            initialized = true;
        }
        else if (option == 2)
        {
            displayAllBugs(bugs);
        }
        else if (option == 3)
        {
            findBugById();
        }
        else if (option == 4)
        {
            tapTheBoard();
        }
        else if (option == 5)
        {
            displayLifeHistory();
        }
        else if (option == 6)
        {
            displayAllCells();
        }
        if (running)
        {
            mainMenu();
            option = getValidInt(0, 6);
        }
    }
    if (initialized)
        OutputFileStream();
    else
        cout << "Nothing has been output." << endl;
    cout << "GoodBye";
}


int main()
{
    run();
}

