#include <boost/any.hpp>
#include <iostream>
#include <stack>
#include <exception>

using stack = std::stack<boost::any>;

int divide(int x, int y) {
    if(y == 0)
        throw std::invalid_argument("Division by zero!");
    return x / y;
}

void otvet(const stack& a) {
    stack s = a;
    stack o;
    while(!s.empty())
    {
        const auto el = s.top();
        s.pop();
        
        int b,c,f;
        
        if( el.type() == typeid(int) ) {
            o.emplace(boost::any_cast<int>(el));
        
        } else if (el.type() == typeid(char)) {
            switch (boost::any_cast<char>(el))
                {
                case '+':
                    b = boost::any_cast<int>(o.top());
                    o.pop();
                    c = boost::any_cast<int>(o.top());
                    o.pop();
                    f = b + c;
                    o.emplace(f);
                    break;
                case '-':
                    b = boost::any_cast<int>(o.top());
                    o.pop();
                    c = boost::any_cast<int>(o.top());
                    o.pop();
                    f = b - c;
                    o.emplace(f);
                    break;
                case '*':
                    b = boost::any_cast<int>(o.top());
                    o.pop();
                    c = boost::any_cast<int>(o.top());
                    o.pop();
                    f = b * c;
                    o.emplace(f);
                    break;
                case '/':
                    c = boost::any_cast<int>(o.top());
                    o.pop();
                    b = boost::any_cast<int>(o.top());
                    o.pop();
                    try {
                        f = divide(b,c);
                    } catch(const std::invalid_argument &err) {
                        std::cout << std::endl;
                        std::cout << "Invalid argument:" << err.what() << std::endl;
                    }
                    o.emplace(f);
                    break;
                default:
                    std::cout << "Unknown";
                    break;
                }
        
        }
            
            
    }
    std::cout << std::endl;
    std::cout << boost::any_cast<int>(o.top());

}


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
    mystack.emplace('/');
    //mystack.emplace('(');
    mystack.emplace(0);
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
    otvet(mystack2);
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

