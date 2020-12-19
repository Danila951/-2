#include <boost/any.hpp>
#include <iostream>
#include <stack>


using stack = std::stack<boost::any>;

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
        /*case '(':
            return 1;
            break;*/
        default:
            return 0;
        break;
    }
}

void view(const stack&);

int main()
{
    int size=0;
    stack mystack;
    stack mystack2;
    stack result;
    
    mystack.emplace(10);
    mystack.emplace('*');
    //mystack.emplace('(');
    mystack.emplace(5);
    mystack.emplace('+');
    mystack.emplace(4);
    //mystack.emplace(')');
    
    
    while(!mystack.empty())
    {
        mystack2.emplace(mystack.top());
        mystack.pop();
        size++;
    }
    
    
    mystack.emplace('.');
    for(int i=0;i<size;i++) {
        const auto el = mystack2.top();
        mystack2.pop();

        if( el.type() == typeid(int) ) {
            result.emplace(boost::any_cast<int>(el));
        
        } else if (el.type() == typeid(char)) {
            if(PRIOR(boost::any_cast<char>(el)) < PRIOR(boost::any_cast<char>(mystack.top()))) {
                    while(PRIOR(boost::any_cast<char>(el))<PRIOR(boost::any_cast<char>(mystack.top()))) {
                        result.emplace(mystack.top());
                        mystack.pop();
                    }
                    mystack.emplace(boost::any_cast<char>(el));
            } else {mystack.emplace(boost::any_cast<char>(el));}
        }
    }
    while(boost::any_cast<char>(mystack.top())!='.') {
        result.emplace(mystack.top());
        mystack.pop();
    }
    
    while(!result.empty())
    {
        mystack2.emplace(result.top());
        result.pop();
    }
    
    view(mystack2);
}

void view(const stack& src)
{
    stack s = src;
    while(!s.empty())
    {
        const auto el = s.top();
        s.pop();

        if( el.type() == typeid(int) )
            std::cout << boost::any_cast<int>(el)<<" ";
        else if (el.type() == typeid(char))
            std::cout << boost::any_cast<char>(el)<<" ";
    }

}

