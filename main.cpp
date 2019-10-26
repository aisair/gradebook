#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

void getPeople();
void swap(int& first1, int& first2, string& last1, string& last2, string& lname1, string& lname2);
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

string names[100];
string lnames[100];
int scores[100];
int numpeople;
float deviation[100];
float stddevtion;
float zscore[100];

int main(){
    int mode;
    float mean, gmean, median;
    string temp;

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
    string temp, temp1;
    numpeople = 0;
    while(stop == 0){
        int restart = 1;
        while(restart == 1){
            restart = 0;

            cout << "Please enter name of person " << person << " (enter END to stop) : ";
            cin >> temp >> temp1;
            if(temp == "END"){
                stop = 1;
                restart = 0;
            }
            else{
                names[person] = temp;
                lnames[person] = temp1;

                cout << "Please enter score of person " << person << ": ";
                cin >> scores[person];

                if(scores[person] < 0){
                    cout << "The score for " << names[person] << ' ' << lnames[person] << " is " << scores[person] << " which cannot be less than zero.";
                    restart = 1;
                }
                else{
                    cout << "The persons name is " << names[person] << ' ' << lnames[person] << " and they have a score of " << scores[person] << '.' << endl;
                }
                numpeople++;
            }
        }
        person++;
    }
}

void sortArray(){
    cout << "Sort initialized." << endl;
    int num = 0;
    int done = 0;
    cout << "Starting up..." << endl << "Sorting..." << endl;
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
    cout << "Sort done!" << endl << endl;
}

void swap(int& first1, int& first2, string& last1, string& last2, string& lname1, string& lname2){
    int firstTemp = first1;
    string lastTemp = last1;
    string lnameTemp = lname1;
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
        cout << endl << numleft << ' ' << numright << ' ' << output << endl;
        return output;
    }
    else{
        output = scores[(numpeople / 2) + 1];
        return output;
    }
}

void print(float mean, int mode, float gmean, float median){
    cout << endl << "Globals:" << endl << "Mean = " << mean << endl << "Median = " << median << endl << "Mode = " << mode << endl << "Geometric Mean = " << gmean << endl;
    cout << "Standard Deviation = " << stddevtion << endl;

    cout << endl << setw(7) << "Name" << setw(14) << "Score" << setw(11) << "Deviation" << setw(10) << "Z-Scores" << endl;
    for(int i = 1; i <= numpeople; i++){
        cout << setw(7) << names[i] << ' ' << setw(7) << lnames[i] << setw(7) << scores[i] << setw(11) << deviation[i] << setw(10) << zscore[i] << endl;
    }
}

float round(float n, int place){
    return round(n * place) / place;
}