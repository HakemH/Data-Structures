/*
 Hakem Habahbeh UIN: 669327508
 This Spam Filter project is flexible program, that is used to check individual emails 
 and filter email lists.The email filtering process goes through a complex algorithim 
 of which relies on loadingspamlists in order to compare to. These said spamlists are
 also able to be displayed. An output file with the name of the user's choice can be 
 made by utilizing the filter function.
 
 */



#include <iostream>
#include <fstream>
#include <string>
#include "ourvector.h"
using namespace std;

/*
 the load function takes in the spamlist and puts it in a spam vector
 counts the lines in the file
 */

void load(string filename, ourvector<string>& spam){
    spam.clear();//clears the spam vector just in case there is unecessary junk 
    ifstream  infile;
    infile.open(filename);
    int entry = 0;
    string temp;
    if (!infile.is_open()) {
      cout << "**Error, unable to open '" << filename << "'"<< endl << endl;
      return;
   }
    else
        infile >> temp;
        while(!infile.eof()){
            ++entry;
            spam.push_back(temp); //reads the file and puts the values in a temp vector
            infile >> temp;
        }
        if(infile.fail()){
        	 cout <<"Loading '" << filename << "'" << endl;  
        }
        cout << "# of spam entries: " << entry << endl << endl;
        return;
}

/*
 The display function utilizes a for loop which iterates
 through the entire vector and prints the values stored inside
 */
void display(ourvector<string>& vectro){
    
    for(int i = 0; i < vectro.size(); i++){
        cout<< vectro[i] << endl;
    }
    cout << endl;
    return;
}
/*
 This Binary search function conducts a binarySearch checking only for the usernames that are specifcally given
 it does not compare the * usernames 
 */
 bool binarySearch(string& email, ourvector<string>& spam){
     //parses an the email input
    int at = email.find("@");
    string username = email.substr(0, at);  
    string domain = email.substr(at+1, email.size());
    int high = spam.size()-1;
    int low = 0, mid = 0;

     while(low <= high){
        mid = (high + low)/ 2;
        string midElement = spam[mid];// finding the middle value in the inputed spamlist
        int thiscolon = midElement.find(":");
        string fileuser = midElement.substr(thiscolon + 1, midElement.size());//fileuser gets the input and stores only
        string filedomain = midElement.substr(0, thiscolon);// filedomain stores the domain for it tobe used later
           
        if(domain < filedomain){
            high = mid -1;
        }
        else if(domain > filedomain ){
              low = mid + 1;
        }
        else if(domain == filedomain){
            if((username < fileuser)){
                high = mid -1;
            }
            else if((username > fileuser)){
                low = mid + 1;
            }
            else{
                return true;
            }
        }
    }

     return false;
 }
/*
 This check funnction conducts a binary search but it looks for specifcally the "*" 
 username in order to label it as spam. Instead of having 2 binary searches done in check. 
 I created a binarySearch that looks for the rest of the usernames that are considered spam.
 
 */
bool check(string& email, ourvector<string>& spam){
    
    int at = email.find("@");
    string username = email.substr(0, at);//setting a new string values and getting rid of the "@" AKA parsing the email input
    string starname = "*";//a username for specifcally the * users that all the emails form those domains are spam
    string domain = email.substr(at+1, email.size());//gets the domain alone 
 
    int high = spam.size()-1;
    int low = 0, mid = 0;
    if(binarySearch(email, spam)){// calls the binarySearch function in order to check if the input falls in the spamlist this is not including * usernames
        return true;
    }//this while loop is a binary Search in order to check if the input falls in the spamlist this only including * usernames
    while(low <= high){
        mid = (high + low)/ 2;
        string midElement = spam[mid];// finding the middle value in the inputed spamlist 
        int thiscolon = midElement.find(":");//looks for ":"
        string fileuser = midElement.substr(thiscolon + 1, midElement.size());//fileuser gets the input and stores only the username which is after ":"
        string filedomain = midElement.substr(0, thiscolon); // filedomain stores the domain for it tobe used later
           
        if(domain < filedomain){
            high = mid -1;
        }
        else if(domain > filedomain ){
              low = mid + 1;
        }
        else if(domain == filedomain){
            if((starname < fileuser)){
                high = mid -1;
            }else if((starname > fileuser)){
                low = mid + 1;
            }
            else{
                return true;
            }
        }
    }
    
    return false;
}
/*
 Filter function takes in 2 inputs from user the email list the user wants to filter
 and the name the user wants the output file to be 
 
 */
void filter(string filename ,string ufileout, ourvector<string>& spam ){
      ifstream  infile;
      ofstream outFS;
      string sentence, email;
      int runs = 0, num;
      infile.open(filename);
      int emailprocessed = 0;
      if (!infile.is_open()) {
          cout << "**Error, unable to open '" << filename << "'"<< endl << endl;
          return;
      }
      else
          infile >> num;
          infile >> email;
          getline(infile, sentence);
          outFS.open(ufileout);
    
      while(!infile.eof()){// this while loop writes the entire lines of the non spam emails
          if(!check(email, spam)){//checks if they return to be spam or not
              outFS << num << " " << email << sentence << endl;    
              ++runs;// counter for how many emails were not spam 
          }
          infile >> num;
          infile >> email;
          getline(infile, sentence);
          ++emailprocessed;// counter for how many emails were in the file
      }
    //necessary closes for the files opened/created
    infile.close();
    outFS.close();
    cout << "# emails processed: " << emailprocessed<< endl;
    cout << "# non-spam emails: " << runs << endl << endl;
  }

int main(){
    string email, first, second, third, fourth, fifth, dead = "#";
    ourvector<string> spam;
    
    cout << "** Welcome to spam filtering app **" << endl << endl; 
  
    cout << "Enter command or # to exit> "; 
    
    cin>>first;//takes in the first word/phrase user inputs 

    while(first != dead){// while loop to keep checking first string to continue the code or end it 
        if(first == "load"){
            cin>> second;
            load(second, spam);//calls load
            
            
        }
        else if(first == "display"){
            display(spam);//displays the loaded list
          
        }
        else if(first == "check"){
            cin>> second;
            bool checkout = check(second, spam);//this bool is used to check if a specific email is spam or not 
            if(checkout){//by calling the check function
                cout<< second << " is spam" << endl<< endl;
            }
            else{
              cout<< second << " is not spam" << endl<< endl;
            }
        }
        else if(first == "filter"){
            cin >> second;
            cin >> third;
            filter(second, third, spam);
        }
        else{
        cout << "**invalid command" << endl<< endl;
        }
        cout << "Enter command or # to exit> ";
        cin>> first;
    }
    
    return 0; 
}