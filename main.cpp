#include <iostream>
#include <string>
#include <stack>
#include <vector>

int PRIOR(char a)
{
    switch(a)
        {
        case '*':
            return 3;
            break;
        case '/':
            return 3;
            break;
        case '-':
            return 2;
            break;
        case '+':
            return 2;
            break;
        case '(':
            return 1;
            break;
        default:
            return 0;
        break;
    }
}


/*
bool chislo(char p)
{
    switch (p)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}*/

//10+2+5
int main() {
    setlocale(LC_ALL,"rus");
    std::stack <char> steck;
    std::stack <char> result;
    //std::vector <char> infix;
    std::string inf;
    std::cin >> inf;
    /*for(int i=0;i<sizeof(inf);i++) {
        infix.push_back(inf[i]);
    }*/
    steck.push('.');
    for(int i=0;i<inf.size();i++) {
        //std::cout << inf[i] <<"  " <<PRIOR(inf[i]) << std::endl;
        if(PRIOR(inf[i])==0) {
            //std::cout << inf[i] <<"  " <<PRIOR(inf[i]) << std::endl;
            result.push(inf[i]);
        } else {
            //std::cout << inf[i] <<"  " <<PRIOR(inf[i]) << std::endl;
            if(PRIOR(inf[i])<PRIOR(steck.top())) {
                    while(PRIOR(inf[i])<PRIOR(steck.top())) {
                        result.push(steck.top());
                        steck.pop();
                    }
                    steck.push(inf[i]);
            } else {steck.push(inf[i]);}
        }
    }
    while(steck.top()!='.') {
        result.push(steck.top());
        steck.pop();
    }
    //std::cout << "Вариант 1:";
    for(int i=0;i<inf.size();i++) {
        //std::cout<<" " << result.top();
        steck.push(result.top());
        result.pop();
    }
    std::cout <<std::endl;
    std::cout << "Обратная Польская запись:";
    for(int i=0;i<inf.size();i++) {
        if(steck.top()=='(' or steck.top()==')') {
                steck.pop();
           } else {
                std::cout<<" " << steck.top();
                steck.pop();
           }
    }

    return 0;
}
