#ifndef JJGIRLS_H
#define JJGIRLS_H

#include <string>
//using namespace std;

class jjgirl{
public:
    jjgirl();
    jjgirl(const std::string jjgirlName);
    ~jjgirl();
    void SetJJGirlName(const std::string jjgirlName);
    int GetPageNumber();
private:
    std::string jjgirl_name;

};

jjgirl::jjgirl(const std::string jjgirlName):jjgirl_name(jjgirlName){

}

void jjgirl::SetJJGirlName(const std::string jjgirlName){
    this->jjgirl_name = jjgirlName;
}



#endif // JJGIRLS_H
