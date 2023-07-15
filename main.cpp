#include <iostream>
#include <iomanip>

struct Person {
    std::string first_name;
    std::string last_name;
    int score;
    float deviation;
    float zscore;

    Person(std::string first, std::string last, int score) : first_name(first),
        last_name(last), score(score), deviation(0.0f), zscore(0.0f) {}
};

void getPeople();
void swap(int& first1, int& first2, std::string& last1, std::string& last2,
    std::string& lname1, std::string& lname2);
void sortArray();
float calcMean();
int calcMode();
float calcGMean();
void calcDeviations(int avg);
void calcStdDeviation();
void calcZScore();
float calcMedian();
void print(float mean, int mode, float gmean, float median);
float round(float n, int place);

std::string names[100];
std::string lnames[100];
int scores[100];
int numpeople;
float deviation[100];
float stddevtion;
float zscore[100];
std::vector<Person> students;

int main(){
    int mode;
    float mean, gmean, median;
    std::string temp;

    getPeople();
    sortArray();
    mean = calcMean();
    mode = calcMode();
    gmean = calcGMean();
    calcDeviations(mean);
    calcStdDeviation();
    calcZScore();
    median = calcMedian();
    print(mean, mode, gmean, median);

    return 0;
}

void getPeople(){
    int stop = 0, person = 1;
    std::string temp, temp1;
    numpeople = 0;
    while(stop == 0){
        int restart = 1;
        while(restart == 1){
            restart = 0;

            std::cout << "Please enter name of person " << person << " (enter END to stop) : ";
            std::cin >> temp >> temp1;
            if(temp == "END"){
                stop = 1;
                restart = 0;
            }
            else{
                names[person] = temp;
                lnames[person] = temp1;

                std::cout << "Please enter score of person " << person << ": ";
                std::cin >> scores[person];

                if(scores[person] < 0){
                    std::cout << "The score for " << names[person] << ' ' << lnames[person] << " is " << scores[person] << " which cannot be less than zero.";
                    restart = 1;
                }
                else{
                    std::cout << "The persons name is " << names[person] << ' ' << lnames[person] << " and they have a score of " << scores[person] << '.' << std::endl;
                }
                numpeople++;
            }
        }
        person++;
    }
}

void sortArray(){
    std::cout << "Sort initialized." << std::endl;
    int num = 0;
    int done = 0;
    std::cout << "Starting up..." << std::endl << "Sorting..." << std::endl;
    while(done == 0){
        done = 1;
        num = 0;
        while(num < numpeople){
            if(scores[num] > scores[num + 1]){
                done = 0;
                swap(scores[num], scores[num + 1], names[num], names[num + 1], lnames[num], lnames[num + 1]);
            }
            num++;
        }
    }
    std::cout << "Sort done!" << std::endl << std::endl;
}

void swap(int& first1, int& first2, std::string& last1, std::string& last2, std::string& lname1, std::string& lname2){
    int firstTemp = first1;
    std::string lastTemp = last1;
    std::string lnameTemp = lname1;
    first1 = first2;
    last1 = last2;
    first2 = firstTemp;
    last2 = lastTemp;
    lname1 = lname2;
    lname2 = lnameTemp;
}

float calcMean(){
    float sum = 0;
    float scoreAverage;

    for(int i = 1; i <= numpeople; i++){
        sum += scores[i];
    }

    scoreAverage = sum / numpeople;

    return scoreAverage;
}

int calcMode(){
    int numcheck = scores[2];
    int mode = numcheck;
    int counti = 1;
    int countMode = 1;

    for (int i = 1; i < numpeople; i++){
        if (scores[i] == numcheck){
            counti++;
        }
        else{
            if (counti > countMode){
                countMode = counti;
                mode = numcheck;
            }
            counti = 1;
            numcheck = scores[i + 1];
        }
    }
    return mode;
}

float calcGMean(){
    unsigned long long product = 1;
    float scoreGAverage, temp;

    for(int i = 1; i <= numpeople; i++){
        product = product * scores[i];
    }

    temp = 1 / (float)numpeople;
    scoreGAverage = pow(product, temp);

    return scoreGAverage;
}

void calcDeviations(int avg){
    for(int i = 1; i <= numpeople; i++){
        deviation[i] = scores[i] - avg;
        //deviation[i] = round(deviation[i], 100);
    }
}

void calcStdDeviation(){
    float devAbsolute[100];
    for(int i = 1; i <= numpeople; i++){
        devAbsolute[i] = abs(deviation[i]);
    }

    float sum = 0;
    float devAverage;

    for(int i = 1; i <= numpeople; i++){
        sum += devAbsolute[i];
    }

    devAverage = sum / numpeople;

    stddevtion = devAverage;
}

void calcZScore(){
    for(int i = 1; i <= numpeople; i++){
        zscore[i] = deviation[i] / stddevtion;
        zscore[i] = round(zscore[i], 100);
    }
}

float calcMedian(){
    int output;
    if(numpeople % 2 == 0){
        int numleft = scores[(numpeople / 2) - 1];
        int numright = scores[(numpeople / 2) + 1];
        output = (numleft + numright) / 2;
        std::cout << std::endl << numleft << ' ' << numright << ' ' << output << std::endl;
        return output;
    }
    else{
        output = scores[(numpeople / 2) + 1];
        return output;
    }
}

void print(float mean, int mode, float gmean, float median){
    std::cout << std::endl << "Globals:" << std::endl << "Mean = " << mean << std::endl << "Median = " << median << std::endl << "Mode = " << mode << std::endl << "Geometric Mean = " << gmean << std::endl;
    std::cout << "Standard Deviation = " << stddevtion << std::endl;

    std::cout << std::endl << std::setw(7) << "Name" << std::setw(14) << "Score" << std::setw(11) << "Deviation" << std::setw(10) << "Z-Scores" << std::endl;
    for(int i = 1; i <= numpeople; i++){
        std::cout << std::setw(7) << names[i] << ' ' << std::setw(7) << lnames[i] << std::setw(7) << scores[i] << std::setw(11) << deviation[i] << std::setw(10) << zscore[i] << std::endl;
    }
}

float round(float n, int place){
    return round(n * place) / place;
}