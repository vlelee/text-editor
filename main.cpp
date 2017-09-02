#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct line {
    list<string> words;
};

//each vector list contains a linked list of sentences or lines
vector<line> lines;
vector<line> commands;

//to_int function converts string to int
int to_int(string str){
   int num;
   istringstream convert(str);
   convert >> num;
   return num;
}

//display function outputs the lines to the screen
void display(){
    for(unsigned i = 0; i < lines.size(); i++){
        for(std::list<string>::iterator it=lines.at(i).words.begin(); it != lines.at(i).words.end(); ++it){
            cout << *it << " ";
        }
        cout << endl;
    }
}

//insert word function looks for a search word given a line number and insert a word after the search word
void insert_word(int line_num, string search_word, string ins_word){
    unsigned index = line_num - 1;
    if(index <= lines.size()){
        if(search_word.length() < 1){
            lines.at(index).words.push_back(ins_word);
        }
        else{
            std::list<string>::iterator it = std::find(lines.at(index).words.begin(), lines.at(index).words.end(), search_word);
            it++;
            lines.at(index).words.insert(it, ins_word);
        }
    }
}

//delete word function looks for the search word given a line number and deletes it
void delete_word(int line_num, string search_word){
    unsigned index = line_num - 1;

    if(index <= lines.size()){
        std::list<string>::iterator it = std::find(lines.at(index).words.begin(), lines.at(index).words.end(), search_word);
        lines.at(index).words.erase(it);
    }
}

//delete line function takes a line number and deletes it
void delete_line(int line_num){
    unsigned index = line_num - 1;
    if(index <= lines.size()){
        lines.erase(lines.begin() + index);
    }
}

//insert line function takes a line number and inserts it
void insert_line(int line_num){
    line temp;
    unsigned index = line_num - 1;
    if(index <= lines.size()){
        lines.insert(lines.begin() + index, temp);
    }
}

//execute command reads the commands from the commands list and executes the function corresponding to command type
void execute_command(){
    for(unsigned i = 0; i < commands.size(); i++){
        if(!commands.at(i).words.empty()){
            int csize = commands.at(i).words.size();

            string comm_type = commands.at(i).words.front();
            commands.at(i).words.pop_front();

            int num = to_int(commands.at(i).words.front());
            commands.at(i).words.pop_front();

            if(comm_type == "insertword"){
                string search_word = "";
                if(csize > 3){
                    search_word = commands.at(i).words.front();
                    commands.at(i).words.pop_front();
                }

                string ins_word = commands.at(i).words.front();
                commands.at(i).words.pop_front();

                insert_word(num, search_word, ins_word);
            }
            else if(comm_type == "deleteword"){
                string search_word = commands.at(i).words.front();
                commands.at(i).words.pop_front();

                delete_word(num, search_word);
            }
            else if(comm_type == "deleteline"){
                delete_line(num);
            }
            else if(comm_type == "insertline"){
                insert_line(num);
            }
            else{
            }
        }
    }
}

//parse_line function takes a sentence, adds each word to the words list. Then the words list is added to the lines list.
void parse_line(string sentence){
    string word;
    line temp;
    stringstream row(sentence);

    while(row >> word){
        temp.words.push_back(word);
    }

    if(temp.words.size() < 1){
        temp.words.push_back(" ");
    }

    lines.push_back(temp);
}

//parse_command takes a line from the command file, then adds each word separated by symbols into a words list. The words list is added to the commands list.
void parse_command(string commandline){
    line temp;
    int csize = commandline.length();
    char str[csize];
    strcpy(str, commandline.c_str());

    char * pch;
    pch = strtok(str, "=:/");

    while(pch != NULL){
        temp.words.push_back(string(pch));
        pch = strtok(NULL, "=:/");
    }

    commands.push_back(temp);
    execute_command();
}

//getInput function reads the input text file and parses line by line
void getInput(){
    string sentence;
    ifstream reader;
    reader.open("input.txt");

    if(reader.is_open()){
        while(getline(reader, sentence)){
            parse_line(sentence);
        }
    }

    reader.close();
}

//getCommand function reads the command text file and parses line by line
void getCommand(){
    string sentence;
    ifstream reader;
    reader.open("command.txt");

    if(reader.is_open()){
        while(getline(reader, sentence)){
            parse_command(sentence);
        }
    }

    reader.close();
}

int main()
{
    getInput();
    getCommand();
    display();
    return 0;
}
