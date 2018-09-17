#include "string_manip.hpp"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::cin;
using std::stringstream;

vector<string> explode(const string& str, char delimiter){
    vector<string> tokens;
    stringstream token_stream(str);
    string temp_str;

    while(std::getline(token_stream, temp_str, delimiter))
        tokens.push_back(temp_str);

    return tokens;
}

vector<string> explode(const string& str, const string& delimiters){
    vector<string> tokens;

    unsigned long sub_str_begin_pos = str.find_first_not_of(delimiters,
                                                            0);
    unsigned long sub_str_end_pos = str.find_first_of(delimiters,
                                                      sub_str_begin_pos);

    while(string::npos != sub_str_begin_pos || string::npos !=\
            sub_str_end_pos){

        tokens.push_back(str.substr(sub_str_begin_pos,
                                    sub_str_end_pos - sub_str_begin_pos));

        sub_str_begin_pos = str.find_first_not_of(delimiters,
                                                  sub_str_end_pos);
        sub_str_end_pos = str.find_first_of(delimiters,
                                            sub_str_begin_pos);
    }

    return tokens;
}

vector<string> explode_substring(const string& str,
                                 const string& delimiter_substr){
    vector<string> tokens;

    unsigned long start = 0;
    unsigned long substr_pos = str.find(delimiter_substr, 0);

    while(substr_pos != string::npos){

        string sub = str.substr(start, substr_pos - start);

        if (!sub.empty())
            tokens.push_back(sub);

        start = substr_pos + delimiter_substr.size();
        substr_pos = str.find(delimiter_substr, start);
    }
    string sub = str.substr(start);
    if (!sub.empty())
        tokens.push_back(sub);

    return tokens;
}

string trim_whitespaces(string str){
    string output;

    unsigned long start = 0;
    unsigned long end = str.size() - 1;

    while (str[start] == ' ') start++;
    while (str[end] == ' ') end--;

    return str.substr(start, end - start + 1);
}
