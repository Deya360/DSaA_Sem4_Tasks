#include <QCoreApplication>
#include <QElapsedTimer>
#include <iostream>
#include <windows.h>

#include <QTime>
#include <deque>

const int N = 16; //Number of elements

//Element value upper and lower bound
const int valLB = 1;
const int valUB = N*1.5625; //16:25 ratio


class Result {
    int k;
    int cmp1 = 0;   //SortFirst
    int cmp2 = 0;   //SearchFirst
    std::vector<int> minThree;

public:
    Result(int k) {
        this->k=k;
    }

    int getK() const {return k;}

    int getSortFirst() const {return cmp1;}
    void setSortFirst(int comparisonCount) {cmp1=comparisonCount;}

    int getSearchFirst() const {return cmp2;}
    void setSearchFirst(int comparisonCount) {cmp2=comparisonCount;}

    std::string getMinThree() const {
        std::string returnString;
        for(auto v:minThree) returnString.append(std::to_string(v) + " ");
        return returnString.substr(0,returnString.size()-1);
    }
    void setMinThree(const std::vector<int> &value) {minThree = value;}

    std::string betterResult() {
        return (cmp1 > cmp2)? "Search" : "Sort";
    }

};

void printInColor(QString msg, unsigned short color = 7, bool cyrillic = false, bool endline = true) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

    if (cyrillic) {
        SetConsoleCP(866);
        SetConsoleOutputCP(866);
        setlocale(LC_CTYPE, "rus");
    }

    std::wcout << msg.toStdWString();
    if (endline) std::cout << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void printVec(std::vector<int> vec) {
    for (auto v: vec) std::cout << v << ' ';
    std::cout << "\n\n";
}

std::vector<int> generateRandVec(int minValRange, int maxValRange, int size) {
    std::random_device r;
    std::mt19937 eng{static_cast<long unsigned int>(time(nullptr))};;
    std::uniform_int_distribution<int> vecSize(minValRange, maxValRange);

    std::vector<int> returnVect;
    for (int i = 0; i < size; i++) {
        returnVect.push_back(vecSize(eng));
    }
    return returnVect;
}


int search(std::vector<int> vec, int element) {    //Linear with Sentinel Search Algorithm
    unsigned int N = vec.size();
    int last = vec.at(N-1);
    vec.at(N-1) = element;

    unsigned int i = 0;
    while(vec.at(i)!=element) i++;

    vec.at(N-1) = last;
    if((i < N-1) || (element == vec.at(N-1))) return i;
    return -1;
}


int sortSelection(std::vector<int> &vec) {
    int cmpCount = 0;
    int i, key, j;
    for (i = 1; i < vec.size(); i++) {
        key = vec.at(i);
        j = i - 1;

        while (j >= 0 && vec.at(j) > key) {
            vec.at(j + 1) = vec.at(j);
            j = j - 1;
            cmpCount++;
        }
        vec.at(j + 1) = key;
        cmpCount++;
    }
    return cmpCount;
}

int sortInsertion(std::vector<int> &vec) {
    int cmpCount = 0;
    int i, j, min_idx;

    for (i = 0; i < vec.size()-1; i++) {
        min_idx = i;
        for (j = i+1; j < vec.size(); j++)
          if (vec.at(j) < vec.at(min_idx))
            min_idx = j;

        std::swap(vec.at(min_idx),vec.at(i));
        cmpCount++;
    }
    return cmpCount;
}

int sortCocktail(std::vector<int> &vec) {
    bool swapped = true;
    int start = 0;
    int end = vec.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (vec.at(i) > vec.at(i + 1)) {
                std::swap(vec.at(i), vec.at(i + 1));
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (vec.at(i) > vec.at(i + 1)) {
                std::swap(vec.at(i), vec.at(i + 1));
                swapped = true;
            }
        }
        ++start;
    }
}


std::vector<int> sortFirstApproach(std::vector<int> vec, int k, int &cmp) {
    std::vector<int> returnVec;
    cmp = sortSelection(vec);
    returnVec.assign(vec.begin(),vec.begin()+(k+1));
    return returnVec;
}

std::vector<int> searchFirstApproach(std::vector<int> vec, int k, int &cmp) {
    std::vector<int> returnVec;
    std::vector<int> q;
    q.push_back(valUB+1);

    for (int i = 0; i < vec.size(); i++) {
        for (int j=0; j < k; j++) {
            cmp++;
            if(vec.at(i) < q.at(j)) {
                q.insert(q.begin()+j,vec.at(i));
                break;
            }
        }
    }
    returnVec.assign(q.begin(),q.begin()+(k+1));
    return returnVec;
}

void printApproachResult(Result *r) {
    std::string line = "K = " + std::to_string(r->getK()) + " - " + r->betterResult();
    printInColor(QString::fromStdString(line),15,true,false);
    std::cout << "\n Sort: " << r->getSortFirst()
              << "\n Search: " << r->getSearchFirst()
              << "\n (" << r->getMinThree() << ")"
              << "\n\n";
}

void compareApproaches(std::vector<int> &vec) {
    Result *prvRes = new Result(-1);
    int changeLimit = 2;
    int k = 2;
    while (changeLimit!=0 && k<=vec.size()) {
        Result *r = new Result(k);

        //SortFirst
        int cmpCount1 = 0;
        r->setMinThree(sortFirstApproach(vec, k, cmpCount1));
        r->setSortFirst(cmpCount1);

        //SearchFirst
        int cmpCount2 = 0;
        searchFirstApproach(vec, k, cmpCount2);
        r->setSearchFirst(cmpCount2);

        if (r->betterResult() != prvRes->betterResult()) {
            if (prvRes->getK() != -1)
                printApproachResult(prvRes);
            printApproachResult(r);
            changeLimit--;
        }
        prvRes = r;
        k++;
    }
}


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //Create a random vector to work with
    std::vector<int> baseVec = generateRandVec(valLB, valUB, N);

    printInColor("Начальный случайно сгенерированный массив для сортировки:",11,true);
    printVec(baseVec);

    //Task 1
    int cmp1A1, cmp1A2 = 0;
    std::vector<int> vec = baseVec;
    printInColor("\nУпражнение 1:",11,true);
    printInColor("Алгоритм сортировки с помощью прямого выбора:",15,true);
    cmp1A1 = sortSelection(vec);
    printVec(vec);

    vec = baseVec;
    printInColor("Алгоритм сортировки с помощью прямого включения:",15,true);
    cmp1A2 = sortInsertion(vec);
    printVec(vec);

    printInColor("Сравнить эффективность (по числу перестановок):",15,true);
    printInColor("прямой выбор:\t\t" + QString::number(cmp1A1),7,true);
    printInColor("прямое включения:\t" + QString::number(cmp1A2),7,true);


    //Task 2
    int cmp2A1, cmp2A2, cmp2A3 = 0;
    printInColor("\n\nУпражнение 2:",11,true);
    printInColor("Алгоритм сортировки с помощью прямого выбора:",15,true);
    QElapsedTimer timer2A1;
    timer2A1.start();
    sortSelection(vec);
    cmp2A1 = timer2A1.nsecsElapsed();
    printVec(vec);

    printInColor("Алгоритм сортировки с помощью прямого включения:",15,true);
    vec = baseVec;
    QElapsedTimer timer2A2;
    timer2A2.start();
    sortInsertion(vec);
    cmp2A2 = timer2A2.nsecsElapsed();
    printVec(vec);

    printInColor("Алгоритм шейкерной сортировки:",15,true);
    vec = baseVec;
    QElapsedTimer timer2A3;
    timer2A3.start();
    sortCocktail(vec);
    cmp2A3 = timer2A3.nsecsElapsed();
    printVec(vec);

    printInColor("Сравнить эффективность (по времени выполнения в наносекундах):",15,true);
    printInColor("прямой выбор:\t\t" + QString::number(cmp2A1),7,true);
    printInColor("прямое включения:\t" + QString::number(cmp2A2),7,true);
    printInColor("шейкерная сортировка:\t" + QString::number(cmp2A3),7,true);


    //Tasks 3-5
    printInColor("\n\nУпражнение 3:",11,true);
    printInColor("Шейкерная сортировка",15,true);

    printInColor("\n\nУпражнение 4:",11,true);
    printInColor("Сортировка: пузырьковая, включением, выбором",15,true);

    printInColor("\n\nУпражнение 5:",11,true);    //Bogosort
    printInColor("Алгоритм Bogosort:\n"
                 "Среднее время работы алгоритма: O(n*n!)\n  "
                 "это примерно:\n"
                 "\t0,59с для 12 элементов,\n"
                 "\t8,4с для 13 элементов,\n"
                 "\t2,1 мин для 14 элементов,\n"
                 "\t33,6 мин для 15 элементов, и.т.д.",15,true);


    //Task 6
    printInColor("\n\nУпражнение 6:",11,true);
    vec = baseVec;
    printInColor("При N = " + QString::number(N) + ":\n",15,true);
    compareApproaches(vec);

    return a.exec();
}










